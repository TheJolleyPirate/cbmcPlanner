objectToNum = list()

def __separateBrackets(inputString: str, bracketType="{}"):
    """
    Separates the input string into segments based on the specified bracket type.
    """
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
            raise ValueError("More closing brackets than opening in one of the conditions")

    if numOpen > 0:
        raise ValueError("More opening brackets than closing in one of the conditions")

    return separated

def __parseAtom(condition: str):
    """
    Parses an atomic condition and returns the corresponding C code representation.
    """
    cCode = ""
    temp = condition.split("Atom ")
    temp = temp[1].split("(")
    predicate = temp[0]

    if predicate == "=":
        predicate = "equals"

    variables = temp[1][:-1]
    predicate = predicate.replace("-", "_")
    cCode += f"state[getIndex_{predicate}("

    variables = variables.split(", ")
    if len(variables) > 1 or variables[0] != "":
        for var in variables:
            # Determine actual variable representation
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

def __parseConjunction(condition: str):
    """
    Parses a conjunction condition and returns the corresponding C code representation.
    """
    cCode = ""
    separatedCon = __separateBrackets(condition)

    for con in separatedCon:
        temp = con[1:]
        current = temp[:-1]
        cCode += __nextCondition(con, current)
        cCode += " && "

    # Remove the last ' && '
    cCode = cCode[:-4]
    return cCode

def __parseDisjunction(condition: str):
    """
    Parses a disjunction condition and returns the corresponding C code representation.
    """
    cCode = ""
    separatedCon = __separateBrackets(condition)

    for con in separatedCon:
        temp = con[1:]
        current = temp[:-1]
        cCode += __nextCondition(con, current)
        cCode += " || "
    # Remove the last ' || '
    cCode = cCode[:-4]
    return cCode

def __parseNegation(condition: str):
    """
    Parses a negation condition and returns the corresponding C code representation.
    """
    cCode = ""
    separatedCon = __separateBrackets(condition)
    cCode += "not ("

    for con in separatedCon:
        temp = con[1:]
        current = temp[:-1]
        cCode += __nextCondition(con, current)

    cCode += ")"
    return cCode

def __nextCondition(con, current: str):
    """
    Determines the type of the next condition and processes it accordingly.
    """
    cCode = ""
    if "[" in current:
        current = current[:-1]
        temp = current.split("[", 1)
        conType = temp[0]

        if con is None:
            con = temp[1]

        if conType == "Conjunction":
            cCode += f"({__parseConjunction(con)})"
        elif conType == "Disjunction":
            cCode += f"({__parseDisjunction(con)})"
        elif conType == "NegatedAtom":
            cCode += f"(({__parseNegation(con)}))"
        else:
            raise ValueError(f"Condition type: {conType} not supported")
    else:
        # Remove brackets and parse atom
        con = con[1:][:-1]
        cCode += __parseAtom(con)

    return cCode

def parseCondition(condition: str, obList: list):
    """
    Parses the overall condition and returns the corresponding C code representation.
    """
    cCode = ""
    global objectToNum
    objectToNum = obList
    if "[" in condition:
        cCode += __nextCondition(None, condition)
    else:
        cCode += __parseAtom(condition)

    return cCode
