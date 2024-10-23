import argparse
from pathlib import Path
from programFiles.ConditionParser import parseCondition
from programFiles.ParsePDDL import parse
from externalTools.fastDownwardParser.pddl.tasks import Task
from externalTools.fastDownwardParser.pddl.pddl_types import Type

# Global variables to store mappings and counts
typeToNum = list()
objectToNum = list()
typeObjectNum = list()
numObjects = 0
predicates = list()
maxParameters = 0
actionParameters = list()

def __intro(problem: Task, stateSize):
    """Generates the preamble for the C code and sets up global variables."""

    # Start the preamble
    preStatecCode = "//PREAMBLE\n//action translation:\n"

    # Add action translations to the preamble
    for act in problem.actions:
        name = act.name
        newName = name.replace("-", "_")
        preStatecCode += f"//{newName}=={name}\n"
    preStatecCode += "//END OF PREAMBLE\n"
    # Included libraries
    preStatecCode += "#include<stdio.h>\n"
    preStatecCode += "#include <stdlib.h>\n"
    # CBMC indeterminate function
    preStatecCode += "int nondet_Int();\n"
    preStatecCode += "//problem definition\n"
    # Setting up the state
    preStatecCode += "//state\n"
    cCode = "//reserve state[0] to always be false\n"
    cCode += "int nextIndex = 1;\n"
    cCode += "//objects\n"

    # Initialize lists for types and objects
    types = list()
    objects = list()
    global typeToNum, typeObjectNum
    # Populate typeToNum and typeObjectNum
    for var in problem.types:
        typeObjectNum.append(0)
        typeToNum.append(str(var))
        types.append(var)
        newVar = str(var).replace("-", "_")
        objects.append(f"int {newVar}[] = {{")
    
    # Initialize object number counter
    objectNum = -1
    global objectToNum
    # Populate objectToNum and objects
    for var in problem.objects:
        objectNum += 1
        obj = str(var).split(": ")
        objectToNum.append(obj[0])
        typeObjectNum[0] += 1  # The first type is all objects
        
        # Append object number to the corresponding type
        if objects[0].endswith("{"):
            objects[0] += str(objectNum)
        else:
            objects[0] += f", {objectNum}"

        # Add to other types
        for i in range(1, len(types)):
            if obj[1] == str(types[i]):
                typeObjectNum[i] += 1
                if objects[i].endswith("{"):
                    objects[i] += str(objectNum)
                else:
                    objects[i] += f", {objectNum}"
                
                # Handle base types recursively
                currentTypeName = Type(types[i]).basetype_name
                while currentTypeName is not None:
                    num = typeToNum.index(str(currentTypeName))
                    typeObjectNum[num] += 1
                    if objects[num].endswith("{"):
                        objects[num] += str(objectNum)
                    else:
                        objects[num] += f", {objectNum}"
                    currentTypeName = Type(types[num]).basetype_name

    # Build object translation section
    # Append object arrays to cCode
    for obj in objects:
        cCode += f"{obj}}};\n"

    # Handle predicates
    global numObjects
    numObjects = objectNum + 1
    cCode += "//predicates\n"
    global predicates
    maxStateSize = 0
    for var in problem.predicates:
        #get predicate, remove closing bracket and then splite around opening bracket
        temp = str(var)[:-1].split("(")
        # Replace - with _
        name = temp[0].replace("-", "_")
        # Replace '=' with 'equals'
        if name == "=":
            name = "equals"
        predicateElements = temp[1].split(", ")
        predicateTypes = list()
        tempString = ""
        elementSizes = list()

        # Construct predicate types and sizes
        if len(predicateElements) > 1 or predicateElements[0] != "":
            for i in range(len(predicateElements)):
                current = predicateElements[i].split(": ")[1]
                predicateTypes.append(current)
                tempString += f"[{objectNum + 1}]"
                # Get the size of each element
                elementSizes.append(typeObjectNum[typeToNum.index(current)])

        # Calculate max state size
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

    # Combine preamble and main code
    cCode = preStatecCode + cCode
    return cCode, stateSize

def __indexFunctions():
    """Generates index functions for predicates."""

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

def __actions(problem: Task):
    """Generates action functions based on the problem's actions."""

    cCode = "\n//actions functions\n"
    global objectToNum, typeToNum, maxParameters, actionParameters
    for act in problem.actions:
        name = act.name.replace("-", "_")
        cCode += f"void {name}("

        # Adding action parameters
        numParams = 0
        params = list()
        for param in act.parameters:
            numParams += 1
            temp = str(param).split(": ")
            currentVar = temp[0][1:].replace("-", "_")
            cCode += f"int {currentVar}, "
            paramType = temp[1]
            if paramType == "":
                paramType = "object"
            params.append(paramType)
        actionParameters.append((name, params))
        if numParams > maxParameters:
            maxParameters = numParams
        cCode = f"{cCode[:-2]}){{\n"

        # Adding action preconditions
        conditions = act.precondition.dumpToString()
        cCode += f"\tif({parseCondition(conditions, objectToNum)}){{\n"

        # Adding action effects
        negativeEffects = ""
        positiveEffects = ""
        for eff in act.effects:
            temp = str(eff.literal).split("Atom ")
            isNegated = temp[0]
            remainder = temp[1]
            predicate, variables = remainder.split("(", 1)
            predicate = predicate.replace("-", "_")
            if predicate == "=":
                predicate = "equals"

            variables = variables[:-1].split(", ")
            effectString = f"\t\tstate[getIndex_{predicate}("
            if len(variables) > 1 or variables[0] != "":
                for var in variables:
                    temp = var[1:].replace("-", "_")
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

def __predicateSetterRecursion(name, indicesLeft, tabs, subscript=0):
    """Recursively sets predicates to -1 based on their dimensionality."""

    global numObjects
    cCode = ""

    if indicesLeft > 0:
        cCode += f"{tabs}for(int i{subscript} = 0; i{subscript} < {numObjects}; i{subscript}++){{\n"
        cCode += __predicateSetterRecursion(name, indicesLeft - 1, tabs + "\t", subscript + 1)
        cCode += f"{tabs}}}\n"
    else:
        temp = ""
        for i in range(subscript):
            temp += f"[i{i}]"
        cCode += f"{tabs}{name}{temp} = -1;\n"
    return cCode

def __boundsSetterRecursion(name, params, indicesLeft, tabs, subscript=0, oldInput=""):
    """Sets bounds for nondeterministic parameters in action function calls."""

    global typeToNum, typeObjectNum
    cCode = ""

    if indicesLeft > 0:
        current = typeToNum.index(params[subscript])
        objectSize = typeObjectNum[current]
        cCode += f"{tabs}index{subscript} = nondet_Int();\n"
        cCode += f"{tabs}if(index{subscript} >= 0 && index{subscript} < {objectSize}){{\n"
        param = str(params[subscript]).replace("-", "_")
        newInput = oldInput + f"{param}[index{subscript}], "
        cCode += __boundsSetterRecursion(name, params, indicesLeft - 1, tabs + "\t", subscript + 1, newInput)
        cCode += f"{tabs}}}\n"
    else:
        if len(oldInput) > 0:
            temp = oldInput[:-2]
        else:
            temp = ""
        cCode += f"{tabs}{name}({temp});\n"
    return cCode

def __mainLoop(problem: Task):
    """Generates the main loop of the program."""

    cCode = "//main loop\n"
    cCode += "int main(){\n"
    global predicates, objectToNum, maxParameters, actionParameters

    # Initialize predicates to -1
    for pred in predicates:
        name = pred[0]
        numIndices = len(pred[1])
        cCode += f"\t//setting {name} to -1\n"
        cCode += __predicateSetterRecursion(name, numIndices, "\t")

    # Setting initial state
    for init in problem.init:
        if "Atom" not in str(init):
            raise ValueError(f"found something unexpected: {init}")

        temp = str(init).split("Atom ")[1].split("(")
        predicate = temp[0].replace("-", "_")
        if predicate == "=":
            predicate = "equals"

        variables = temp[1][:-1].split(", ")
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
    # Decision variables
    cCode += "\t//decision variables\n"
    cCode += "\tint actionDecision;\n"
    for i in range(maxParameters):
        cCode += f"\tint index{i};\n"
    # Main loop
    cCode += "\t//main loop\n"
    cCode += "\twhile(1 == 1){\n"
    cCode += "\t\t//choose action\n"
    cCode += "\t\tactionDecision = nondet_Int();\n"
    cCode += "\t\tswitch(actionDecision){\n"

    # Generate cases for actions
    caseNum = 0
    for act in problem.actions:
        caseNum += 1
        cCode += f"\t\tcase {caseNum}:\n"
        name = act.name.replace("-", "_")
        params = list()
        for acp in actionParameters:
            if name == acp[0]:
                params = acp[1]
                break
        cCode += __boundsSetterRecursion(name, params, len(params), "\t\t\t")
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

def writeProgram(problem: Task, outputFolder, stateSize=1):
    """Writes the generated C program to a file."""

    problemName = problem.task_name.replace("-", "-")
    stateSizePercentage = "{:.0%}".format(stateSize)
    outputFolder += f"/state{stateSizePercentage}"
    Path(outputFolder).mkdir(parents=True, exist_ok=True)
    fileName = f"{outputFolder}/{problemName}.c"
    temp = __intro(problem, stateSize)
    cCode = temp[0]
    outStateSize = temp[1]
    cCode += __indexFunctions()
    cCode += __actions(problem)
    cCode += __mainLoop(problem)
    with open(fileName, "w") as cFile:
        cFile.write(cCode)

    # reset global variables
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
    """allows for PDDL files to be translated to C programs without using the solver"""
    # Argument parsing for command line input
    parser = argparse.ArgumentParser(description="translates a PDDL problem into a CBMC solvable file")
    parser.add_argument('-d', '--domain', type=str, required=True, help='the domain PDDL file')
    parser.add_argument('-p', '--problem', type=str, required=True, help='the problem PDDL file')
    parser.add_argument('-s', '--stateSize', type=float, default=1,
                        help='State size as a percentage: e.g., 0.2 means 20% of the maximum possible size')

    args = parser.parse_args()
    d = args.domain
    p = args.problem
    s = args.stateSize
    parsedProblem = parse(d, p)
    rootFolder = p.rsplit("/", 1)[0]
    cOutFolder = f"{rootFolder}/output/cFiles"
    writeProgram(parsedProblem, cOutFolder, s)