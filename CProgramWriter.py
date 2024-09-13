import argparse
from pathlib import Path
from ConditionParser import parseCondition
from ParsePDDL import parse
from externalTools.fastDownwardParser.pddl.tasks import Task
from externalTools.fastDownwardParser.pddl.pddl_types import Type

typeToNum = list()
objectToNum = list()
typeObjectNum = list()
numObjects = 0
predicates = list()
maxParameters = 0
actionParameters = list()


def intro(problem: Task, stateSize):
    # This function writes the preamble of the c code and sets up the global variables
    # Writing some information for the solver
    preStatecCode = "//PREAMBLE\n"
    preStatecCode += "//action translation:\n"
    for act in problem.actions:
        name = act.name
        newName = name.replace("-", "_")
        preStatecCode += f"//{newName}=={name}\n"
    preStatecCode += "//END OF PREAMBLE\n"
    # Included libraries
    preStatecCode += "#include<stdio.h>\n"
    preStatecCode += "#include <stdlib.h>\n"
    # CBMC indeterminate function
    # noinspection SpellCheckingInspection
    preStatecCode += "int nondet_Int();\n"
    preStatecCode += "//problem definition\n"
    # Setting up the state
    preStatecCode += "//state\n"
    cCode = "//reserve state[0] to always be false\n"
    cCode += "int nextIndex = 1;\n"
    cCode += "//objects\n"
    # Getting the types
    types = list()
    objects = list()
    global typeToNum
    global typeObjectNum
    for var in problem.types:
        typeObjectNum.append(0)
        typeToNum.append(str(var))
        types.append(var)
        newVar = str(var).replace("-", "_")
        objects.append(f"int {newVar}[] = {{")
    objectNum = -1
    global objectToNum
    for var in problem.objects:
        objectNum += 1
        obj = str(var).split(": ")
        objectToNum.append(obj[0])
        # The first type is all objects
        typeObjectNum[0] += 1
        if str(objects[0]).split("{")[1] == "":
            objects[0] += str(objectNum)
        else:
            objects[0] += f", {objectNum}"
        # Adding to other types
        for i in range(1, len(types)):
            if obj[1] == str(types[i]):
                typeObjectNum[i] += 1
                if str(objects[i]).split("{")[1] == "":
                    objects[i] += str(objectNum)
                else:
                    objects[i] += f", {objectNum}"
                if Type(types[i]).basetype_name is not None:
                    currentTypeName = Type(types[i]).basetype_name
                    while True:
                        num = -1
                        for j in range(len(typeToNum)):
                            if typeToNum[j] == str(currentTypeName):
                                num = j
                                break
                        typeObjectNum[num] += 1
                        if str(objects[num]).split("{")[1] == "":
                            objects[num] += str(objectNum)
                        else:
                            objects[num] += f", {objectNum}"
                        if Type(types[num]).basetype_name is not None:
                            currentTypeName = Type(types[num]).basetype_name
                        else:
                            break
    cCode += "//object translation:\n"
    cCode += "//objectNames = {"
    f = True
    for obj in objectToNum:
        if f:
            f = False
        else:
            cCode += ", "
        cCode += obj
    cCode += "};\n"
    for obj in objects:
        temp = obj
        temp += "};\n"
        cCode += temp
    global numObjects
    numObjects = objectNum + 1
    cCode += "//predicates\n"
    global predicates
    maxStateSize = 0
    for var in problem.predicates:
        # Get the predicate as a string
        temp = str(var)
        # Remove the closing bracket
        temp = temp[:-1]
        # Split around the starting bracket
        temp = temp.split("(")
        name = temp[0]
        # Replace = with words
        if name == "=":
            name = "equals"
        # Replace - with _temp
        name = name.replace("-", "_")
        predicateElements = temp[1].split(", ")
        predicateTypes = list()
        tempString = ""
        elementSizes = list()
        # Making sure to only make variable an array if predicate has variable(s)
        if len(predicateElements) > 1 or predicateElements[0] != "":
            for i in range(len(predicateElements)):
                current = predicateElements[i].split(": ")[1]
                predicateTypes.append(current)
                tempString += f"[{objectNum + 1}]"
                # Getting the size of each element
                for j in range(len(typeToNum)):
                    if typeToNum[j] == current:
                        elementSizes.append(typeObjectNum[j])
                        break
        tempNum = 1
        if stateSize <= 1:
            for ele in elementSizes:
                tempNum *= ele
            maxStateSize += tempNum
        predicates.append((name, predicateTypes))
        cCode += f"int {name}{tempString};\n"
    # State[0] is reserved to be always false
    if stateSize <= 1:
        stateSize = int(maxStateSize * stateSize)
        preStatecCode += f"int n = {stateSize + 1};\n"
        preStatecCode += f"char state[{stateSize + 1}];\n"
    else:
        preStatecCode += f"int n = {stateSize + 1};\n"
        preStatecCode += f"char state[{stateSize + 1}];\n"
    cCode = preStatecCode + cCode
    return cCode, stateSize


def indexFunctions():
    # This writes the functions which assign places in the state function to different predicates as needed
    cCode = "\n//get index functions\n"
    global predicates
    for pred in predicates:
        name = str(pred[0])
        cCode += f"int getIndex_{name}("
        indexString = ""
        for i in range(len(pred[1])):
            cCode += f"int x{i}, "
            indexString += f"[x{i}]"
        cCode += "int set){\n"
        cCode += "\tint index;\n"
        cCode += f"\tif({name}{indexString} < 0){{\n"
        cCode += "\t\tif(set){\n"
        cCode += "\t\t\tif(nextIndex >= n) {\n"
        cCode += "\t\t\t\texit(-1);\n"
        cCode += "\t\t\t}\n"
        cCode += "\t\t\tindex = nextIndex;\n"
        cCode += "\t\t\tnextIndex += 1;\n"
        cCode += f"\t\t\t{name}{indexString} = index;\n"
        cCode += "\t\t}\n"
        cCode += "\t\telse{\n"
        cCode += "\t\t\tindex = 0;\n"
        cCode += "\t\t}\n"
        cCode += "\t}\n"
        cCode += "\telse{\n"
        cCode += f"\t\tindex = {name}{indexString};\n"
        cCode += "\t}\n"
        cCode += "\treturn index;\n"
        cCode += "}\n"
    return cCode


def actions(problem: Task):
    # This writes the action functions
    cCode = "\n//actions functions\n"
    probActions = problem.actions
    global objectToNum
    global typeToNum
    global maxParameters
    global actionParameters
    for act in probActions:
        name = act.name
        name = name.replace("-", "_")
        cCode += f"void {name}("
        # Adding action parameters
        numParams = 0
        params = list()
        for param in act.parameters:
            numParams += 1
            temp = str(param).split(": ")
            currentVar = temp[0]
            currentVar = currentVar[1:]
            currentVar = currentVar.replace("-", "_")
            cCode += f"int {currentVar}, "
            paramType = temp[1]
            if paramType == "":
                paramType = "object"
            params.append(paramType)
        actionParameters.append((name, params))
        if numParams > maxParameters:
            maxParameters = numParams
        cCode = cCode[:-2]
        cCode += "){\n"
        # Adding action preconditions
        conditions = act.precondition.dumpToString()
        cCode += f"\tif({parseCondition(conditions, objectToNum)}){{\n"
        # Adding action effects
        negativeEffects = ""
        positiveEffects = ""
        for eff in act.effects:
            temp = str(eff.literal)
            temp = temp.split("Atom ")
            isNegated = temp[0]
            remainder = temp[1]
            temp = remainder.split("(")
            predicate = temp[0]
            if predicate == "=":
                predicate = "equals"
            predicate = predicate.replace("-", "_")
            temp = temp[1][:-1]
            variables = temp.split(", ")
            effectString = f"\t\tstate[getIndex_{predicate}("
            if len(variables) > 1 or variables[0] != "":
                for var in variables:
                    temp = var[1:]
                    temp = temp.replace("-", "_")
                    effectString += f"{temp}, "
            effectString += "1)] = "
            if isNegated == "Negated":
                effectString += "0;\n"
                negativeEffects += effectString
            else:
                effectString += "1;\n"
                positiveEffects += effectString
        cCode += negativeEffects
        cCode += positiveEffects
        cCode += "\t}\n"
        cCode += "\telse{\n"
        cCode += "\t\texit(-1);\n"
        cCode += "\t}\n"
        cCode += "\treturn;\n"
        cCode += "}\n"
    return cCode


def predicateSetterRecursion(name, indicesLeft, tabs, subscript=0):
    # This helps the main loop by using recursion
    global numObjects
    cCode = ""
    if indicesLeft > 0:
        cCode += f"{tabs}for(int i{subscript} = 0; i{subscript} < {numObjects}; i{subscript}++){{\n"
        cCode += predicateSetterRecursion(name, indicesLeft - 1, tabs + "\t", subscript + 1)
        cCode += f"{tabs}}}\n"
    else:
        temp = ""
        for i in range(subscript):
            temp += f"[i{i}]"
        cCode += f"{tabs}{name}{temp} = -1;\n"
    return cCode


def boundsSetterRecursion(name, params, indicesLeft, tabs, subscript=0, oldInput=""):
    # This sets the bounds for the object variables
    global typeToNum
    global typeObjectNum
    cCode = ""
    if indicesLeft > 0:
        current = -1
        for i in range(len(typeToNum)):
            if params[subscript] == typeToNum[i]:
                current = i
                break
        objectSize = typeObjectNum[current]
        cCode += f"{tabs}index{subscript} = nondet_Int();\n"
        cCode += f"{tabs}if(index{subscript} >= 0 && index{subscript} < {objectSize}){{\n"
        param = str(params[subscript]).replace("-", "_")
        newInput = oldInput + f"{param}[index{subscript}], "
        cCode += boundsSetterRecursion(name, params, indicesLeft - 1, tabs + "\t", subscript + 1, newInput)
        cCode += f"{tabs}}}\n"
    else:
        if len(oldInput) > 0:
            temp = oldInput[:-2]
        else:
            temp = ""
        cCode += f"{tabs}{name}({temp});\n"
    return cCode


def mainLoop(problem: Task):
    cCode = "//main loop\n"
    cCode += "int main(){\n"
    global predicates
    global numObjects
    # Initilising predicates to -1
    for pred in predicates:
        name = pred[0]
        numIndices = len(pred[1])
        cCode += f"\t//setting {name} to -1\n"
        cCode += predicateSetterRecursion(name, numIndices, "\t")
    # Setting initial state
    global objectToNum
    for init in problem.init:
        if "Atom" not in str(init):
            raise ValueError(f"found something unexpected: {init}")
        temp = str(init).split("Atom ")[1]
        temp = temp.split("(")
        predicate = temp[0]
        if predicate == "=":
            predicate = "equals"
        predicate = predicate.replace("-", "_")
        temp = temp[1]
        temp = temp[:-1]
        variables = temp.split(", ")
        cCode += f"\tstate[getIndex_{predicate}("
        if len(variables) > 1 or variables[0] != "":
            for var in variables:
                trueVar = None
                for i in range(len(objectToNum)):
                    if var == objectToNum[i]:
                        trueVar = i
                        break
                cCode += f"{trueVar}, "
        cCode += "1)] = 1;\n"
    cCode += "\t//decision variables\n"
    cCode += "\tint actionDecision;\n"
    global maxParameters
    for i in range(maxParameters):
        cCode += f"\tint index{i};\n"
    cCode += "\t//main loop\n"
    cCode += "\twhile(1 == 1){\n"
    cCode += "\t\t//choose action\n"
    cCode += "\t\tactionDecision = nondet_Int();\n"
    cCode += "\t\tswitch(actionDecision){\n"
    caseNum = 0
    global actionParameters
    for act in problem.actions:
        caseNum += 1
        cCode += f"\t\tcase {caseNum}:\n "
        name = act.name
        name = name.replace("-", "_")
        params = []
        for acp in actionParameters:
            if name == acp[0]:
                params = acp[1]
                break
        cCode += boundsSetterRecursion(name, params, len(params), "\t\t\t")
        cCode += "\t\t\tbreak;\n"
    cCode += "\t\t}\n"
    cCode += "\t\t//check if goal state reached\n"
    condition = problem.goal.dumpToString()
    cCode += f"\t\tif({parseCondition(condition, objectToNum)}){{\n"
    cCode += "\t\t\t__CPROVER_assert(1 == 0, \"GOAL CHECKER: FAIL MEANS PLAN FOUND\");\n"
    cCode += "\t\t}\n"
    cCode += "\t}\n"
    cCode += "}\n"
    return cCode


def writeProgram(problem: Task, outputFolder, stateSize):
    problemName = problem.task_name
    problemName = problemName.replace("-", "-")
    stateSizePercentage = "{:.0%}".format(stateSize)
    outputFolder += f"/state{stateSizePercentage}"
    Path(outputFolder).mkdir(parents=True, exist_ok=True)
    fileName = f"{outputFolder}/{problemName}.c"
    cFile = open(fileName, "w")
    temp = intro(problem, stateSize)
    cCode = temp[0]
    outStateSize = temp[1]
    cCode += indexFunctions()
    cCode += actions(problem)
    cCode += mainLoop(problem)
    cFile.write(cCode)
    cFile.close()
    global typeToNum
    typeToNum = list()
    global objectToNum
    objectToNumTemp = objectToNum
    objectToNum = list()
    global typeObjectNum
    typeObjectNum = list()
    global numObjects
    numObjects = 0
    global predicates
    predicates = list()
    global maxParameters
    maxParameters = 0
    global actionParameters
    actionParameters = list()
    return fileName, outStateSize, objectToNumTemp, problemName

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='PDDLtranslate',
                                     description="translates a PDDL problem into a CBMC solvable file")
    parser.add_argument('-d', '--domain', type=str, required=True, help='the domain PDDL file')
    parser.add_argument('-p', '--problem', type=str, required=True, help='the problem PDDL file')
    parser.add_argument('-s', '--stateSize', type=float, default=1,
                        help='state size; 0-1 percentage based: e.g. 0.2 = 20% max possible size, >1 sets static state '
                             'size')
    args = parser.parse_args()
    d = args.domain
    p = args.problem
    s = args.stateSize
    parsedProblem = parse(d, p)
    rootFolder = p.rsplit("/", 1)[0]
    cOutFolder = f"{rootFolder}/output/cFiles"
    writeProgram(parsedProblem, cOutFolder, s)