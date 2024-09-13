
def parseAtom(condition: str, objectToNum: list):
    cCode = ""
    temp = condition.split("Atom ")
    temp = temp[1].split("(")
    predicate = temp[0]
    if str(predicate) == "=":
        predicate = "equals"
    variables = temp[1][:-1]
    predicate = predicate.replace("-", "_")
    cCode += f"state[getIndex_{predicate}("
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

def nextCondition(con, current: str, obNum: list):
    cCode = ""
    if "[" in current:
        current = current[:-1]
        temp = current.split("[", 1)
        conType = temp[0]
        if con is None:
            con = temp[1]
        if conType == "Conjunction":
            cCode += f"({parseConjunction(con, obNum)})"
        elif conType == "Disjunction":
            cCode += f"({parseDisjunction(con, obNum)})"
        elif conType == "NegatedAtom":
            cCode += f"(({parseNegation(con, obNum)}))"
        else:
            raise ValueError(f"Condition type: {conType} not supported")
    else:
        # remove brackets
        con = con[1:]
        con = con[:-1]
        cCode += parseAtom(con, obNum)
    return cCode

def parseConjunction(condition: str, obNum: list):
    cCode = ""
    seperatedCon = seperateBrackets(condition, "{}")
    for con in seperatedCon:
        temp = con[1:]
        current = temp[:-1]
        cCode += nextCondition(con, current, obNum)
        cCode += " && "
    cCode = cCode[:-4]
    return cCode

def parseDisjunction(condition: str, obNum: list):
    cCode = ""
    seperatedCon = seperateBrackets(condition, "{}")
    for con in seperatedCon:
        temp = con[1:]
        current = temp[:-1]
        cCode += nextCondition(con, current, obNum)
        cCode += " || "
    cCode = cCode[:-4]
    return cCode

def parseNegation(condition: str, obNum: list):
    cCode = ""
    seperatedCon = seperateBrackets(condition, "{}")
    cCode += "not ("
    for con in seperatedCon:
        temp = con[1:]
        current = temp[:-1]
        cCode += nextCondition(con, current, obNum)
    cCode += ")"
    return cCode

def parseCondition(condition: str, obNum: list):
    cCode = ""
    if "[" in condition:
        cCode += nextCondition(None, condition, obNum)
    else:
        cCode += parseAtom(condition, obNum)
    return cCode