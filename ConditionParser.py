def parseAtom(condition: str, objectToNum: list):
    cCode = ""
    temp = condition.split("Atom ")
    temp = temp[1].split("(")
    predicate = temp[0]
    if str(predicate) == "=":
        predicate = "equals"
    variables = temp[1][:-1]
    predicate = predicate.replace("-", "_")
    cCode += "state[getIndex_" + predicate + "("
    variables = variables.split(", ")
    if len(variables) > 1 or variables[0] != "":
        for var in variables:
            if "?" in var:
                varActual = var[1:]
            else:
                varActual = ""
                for i in range(len(objectToNum)):
                    if var == objectToNum[i]:
                        varActual = str(i)
            varActual = varActual.replace("-", "_")
            cCode += varActual + ", "
        cCode += "0)]"
    else:
        cCode += "0)]"
    return cCode

def seperateBrackets(inputString: str, bracketType="{}"):
    separated = list()
    numOpen = 0
    currentStr = ""
    openBracket = bracketType[0]
    closeBracket = bracketType[1]
    for c in inputString:
        if c == openBracket:
            numOpen += 1
        elif c == closeBracket:
            numOpen -= 1
        currentStr += c
        if numOpen == 0:
            separated.append(currentStr)
            currentStr = ""
        elif numOpen < 0:
            raise ValueError("more closing brackets then opening in one of the conditions")
    if numOpen > 0:
        raise ValueError("more opening brackets then closing in one of the conditions")
    return separated

def parseConjunction(condition: str, obNum: list):
    cCode = ""
    seperatedCon = seperateBrackets(condition, "{}")
    for con in seperatedCon:
        temp = con[1:]
        condition = temp[:-1]
        if "[" in condition:
            condition = condition[:-1]
            temp = condition.split("[", 1)
            conType = temp[0]
            #conContents = temp[1]
            if conType == "Conjunction":
                cCode += "(" + parseConjunction(con, obNum) + ")"
            elif conType == "Disjunction":
                cCode += "(" + parseDisjunction(con, obNum) + ")"
            else:
                raise ValueError("Condition type: " + conType + " not supported")
        else:
            #remove brackets
            con = con[1:]
            con = con[:-1]
            cCode += parseAtom(con, obNum)
        cCode += " && "
    cCode = cCode[:-4]
    return cCode

def parseDisjunction(condition: str, obNum: list):
    cCode = ""
    seperatedCon = seperateBrackets(condition, "{}")
    for con in seperatedCon:
        temp = con[1:]
        condition = temp[:-1]
        if "[" in condition:
            condition = condition[:-1]
            temp = condition.split("[", 1)
            conType = temp[0]
            #conContents = temp[1]
            if conType == "Conjunction":
                cCode += "(" + parseConjunction(con, obNum) + ")"
            elif conType == "Disjunction":
                cCode += "(" + parseDisjunction(con, obNum) + ")"
            else:
                raise ValueError("Condition type: " + conType + " not supported")
        else:
            #remove brackets
            con = con[1:]
            con = con[:-1]
            cCode += parseAtom(con, obNum)
        cCode += " || "
    cCode = cCode[:-4]
    return cCode

def parseCondition(condition: str, obNum: list):
    cCode = ""
    if "[" in condition:
        #remove closing bracket
        condition = condition[:-1]
        temp = condition.split("[", 1)
        conType = temp[0]
        conContents = temp[1]
        if conType == "Conjunction":
            # Parse conjunction condition
            cCode += parseConjunction(conContents, obNum)
        elif conType == "Disjunction":
            # Parse disjunction condition
            cCode += parseDisjunction(conContents, obNum)
        else:
            # other condition types not supported
            raise ValueError("Condition type: " + conType + " not supported")
    else:
        # Parse atomic condition
        cCode += parseAtom(condition, obNum)
    return cCode