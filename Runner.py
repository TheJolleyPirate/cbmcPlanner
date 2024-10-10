import argparse
import os
import re
import signal
import sys
import timeit
import datetime

from ParsePDDL import parse
from CProgramWriter import writeProgram
from CBMCSolver import solve
from LogWriter import writeLogs, corrolate
from Validator import validate

startTime = 0
domain = ""
problem = ""
multi = False
startingDepth = 1
depthStep = 1
maxDepth = 0
manualDepth = 0
verbose = False
concise = False
pTimeout = 0
dTimeout = 300
geoAllocation = 0
stateSize = 1
loadBool = False
stopOnInvalid = False
numRuns = 1

def save(problemsRun, inputFolder, cOutFolder, logOutFolder, problemNum, numProblems):
    el = "\n"
    lineBreak = "<><><><><><><><><>" + el
    toWrite = ""
    
    toWrite += f"input folder: {inputFolder}{el}"
    toWrite += f"c files output folder: {cOutFolder}{el}"
    toWrite += f"log files output folder: {logOutFolder}{el}"
    toWrite += f"starting depth: {startingDepth}{el}"
    toWrite += f"depth step: {depthStep}{el}"
    toWrite += f"max depth: {maxDepth}{el}"
    toWrite += f"manual depth: {manualDepth}{el}"
    toWrite += f"verbose: {verbose}{el}"
    toWrite += f"concise: {concise}{el}"
    toWrite += f"p timeout: {pTimeout}{el}"
    toWrite += f"d timeout: {dTimeout}{el}"
    toWrite += f"geo allocation: {geoAllocation}{el}"
    toWrite += f"state size: {(stateSize * 100)}%{el}"
    toWrite += f"problem number: {problemNum}{el}"
    toWrite += f"number of problems: {numProblems}{el}"
    toWrite += lineBreak

    for prob in problemsRun:
        toWrite += prob + el

    with open("save.txt", "w") as saveFile:
        saveFile.write(toWrite)

def load():
    try:
        with open("save.txt", "r") as saveFile:
            lineBreak = "<><><><><><><><><>\n"
            parts = saveFile.read().split(lineBreak)
            arguments = parts[0].splitlines()
            problems = parts[1].splitlines()

        global startingDepth, depthStep, maxDepth, manualDepth
        global verbose, concise, pTimeout, dTimeout, geoAllocation, stateSize
        
        inputFolder = arguments[0].split(": ")[1]
        cOutFolder = arguments[1].split(": ")[1]
        logOutFolder = arguments[2].split(": ")[1]
        startingDepth = int(arguments[3].split(": ")[1])
        depthStep = int(arguments[4].split(": ")[1])
        maxDepth = int(arguments[5].split(": ")[1])
        manualDepth = int(arguments[6].split(": ")[1])
        verbose = eval(arguments[7].split(": ")[1])
        concise = eval(arguments[8].split(": ")[1])
        pTimeout = int(arguments[9].split(": ")[1])
        dTimeout = int(arguments[10].split(": ")[1])
        geoAllocation = float(arguments[11].split(": ")[1])
        
        percentageStateSize = int(float(arguments[12].split(": ")[1][:-1]))
        stateSize = percentageStateSize / 100
        
        problemNum = int(arguments[13].split(": ")[1])
        numProblems = int(arguments[14].split(": ")[1])
        
        return problems, inputFolder, cOutFolder, logOutFolder, problemNum, numProblems
    
    except FileNotFoundError as err:
        print("save file not found", file=sys.stderr)
        raise err

def executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, problemFile, domainFile, positionInfo=None):
    if positionInfo is None:
        print(f"writing c program with state size: {stateSize * 100}%")
    else:
        print(f"writing c program {positionInfo[0]}/{positionInfo[1]} with state size: {stateSize * 100}%")
    #write the c file
    cFile, realStateSize, objectToNum, problemName = writeProgram(parsedProblem, cOutFolder, stateSize)
    
    oldActionNames = list()
    newActionNames = list()
    for act in parsedProblem.actions:
        oldName = act.name
        newName = oldName.replace("-", "_")
        oldActionNames.append(oldName)
        newActionNames.append(newName)

    cName = str(cFile).split("/")[-1]
    stopExecution = False
    first = True
    localConcise = concise
    for iteration in range(numRuns):
        if first:
            first = False
        elif not verbose:
            localConcise = True
        solveString = f"solving {problemName} with CBMC"
        if positionInfo is not None:
            solveString += f", problem: {positionInfo[0]}/{positionInfo[1]}"
        if numRuns > 1:
            solveString += f", iteration: {iteration + 1}/{numRuns}"
        print(solveString)
        #solve the c file
        results = solve(cFile, maxDepth, manualDepth, startingDepth, depthStep,
                        oldActionNames, newActionNames, objectToNum, localConcise,
                        verbose, pTimeout, dTimeout, geoAllocation)
        if results[0]:
            if not localConcise:
                print(f"validating plan to solve {cName}:")
            valid = validate(results[0], domainFile, problemFile, verbose)

            if valid and not localConcise:
                print("\tplan valid")
            elif not localConcise:
                print("\tplan invalid")
        else:
            valid = False
        #write logs to file
        writeLogs(problemName, logOutFolder, results, valid, stateSize,
                  realStateSize, pTimeout, dTimeout, maxDepth, geoAllocation)
        if stopOnInvalid and not valid:
            stopExecution = True
            break
    return stopExecution

def sorted_nicely(l):
    """ Sort the given iterable in a human-friendly way. """
    """function by Mark Byers
    sourced from https://stackoverflow.com/questions/2669059/how-to-sort-alpha-numeric-set-in-python"""
    """ Sort the given iterable in the way that humans expect."""
    convert = lambda text: int(text) if text.isdigit() else text
    alphanum_key = lambda key: [convert(c) for c in re.split('([0-9]+)', key)]
    return sorted(l, key=alphanum_key)

def run():
    allowedRequirements = [":strips", ":typing", ":equality", ":disjunctive-preconditions", 
                           ":negation", ":negative-preconditions"]
    # TODO, ":conditional-effects", ":universal-preconditions", ":quantified-preconditions",
    #  ":existential-preconditions", ":adl", ":derived-predicates", ":action-costs",":fluents", ":numeric-fluents",
    #  ":domain-axioms", ":safety-constraints", ":ucpop"]
    if multi:
        problemNum = None
        numProblems = None
        
        if loadBool:
            problemsRun, inputFolder, cOutFolder, logOutFolder, problemNum, numProblems = load()
        else:
            inputFolder = domain
            problemsRun = list()
            if inputFolder == "input":
                cOutFolder = "output/cFiles"
                logOutFolder = "output/logs"
            else:
                cOutFolder = f"{inputFolder}/output/cFiles"
                logOutFolder = f"{inputFolder}/output/logs"
        
        files = os.listdir(inputFolder)
        pddlFiles = list()
        domainProblems = dict()
        domains = dict()
        problemFiles = list()
        files = sorted_nicely(files)
        
        for file in files:
            if file.endswith(".pddl"):
                current = f"{inputFolder}/{file}"
                pddlFiles.append(current)
                
                with open(current, "r") as f:
                    contents = f.read()
                
                if "(define (domain " in contents:
                    temp = contents.split("(define (domain ")[1]
                    name = temp.split(")", 1)[0]
                    domains[name] = current
                    domainProblems[name] = list()
                else:
                    problemFiles.append(file)

        for pFile in problemFiles:
            current = f"{inputFolder}/{pFile}"
            
            with open(current, "r") as f:
                contents = f.read()
            
            temp = contents.split("(:domain ")[1]
            currentDomain = temp.split(")")[0]
            
            if currentDomain in domains:
                domainProblems[currentDomain].append(current)

        if not loadBool:
            numProblems = len(problemFiles)
            problemNum = 1

        for dom in domains:
            problems = domainProblems[dom]
            for prob in problems:
                if prob in problemsRun:
                    continue
                
                parsedProblem = parse(domains[dom], prob)
                
                for requirement in parsedProblem.requirements.requirements:
                    if requirement not in allowedRequirements:
                        raise ValueError(
                            f"Sorry the allowed requirements are limited and {requirement} is not allowed"
                        )
                stopExecution = executeSingleProblem(parsedProblem, cOutFolder, logOutFolder,
                                                          prob, domains[dom], (problemNum, numProblems))
                problemNum += 1
                problemsRun.append(prob)
                save(problemsRun, inputFolder, cOutFolder, logOutFolder, problemNum, numProblems)
                if stopExecution:
                    break
    else:
        print(f"Combining Domain: {domain} with problem: {problem}")
        parsedProblem = parse(domain, problem)
        rootFolder = problem.rsplit("/", 1)[0]
        
        for requirement in parsedProblem.requirements.requirements:
            if requirement not in allowedRequirements:
                raise ValueError(
                    f"Sorry the allowed requirements are limited and {requirement} is not allowed"
                )
        
        cOutFolder = f"{rootFolder}/output/cFiles"
        logOutFolder = f"{rootFolder}/output/logs"
        executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, problem, domain)
    corrolate(logOutFolder)
    if not concise:
        print("logs printed to:")
        print(f"\t{os.path.abspath(logOutFolder)}")

def inturruptHandler(signalType, frame):
    global startTime
    intTime = timeit.default_timer()
    elapsedTime = intTime - startTime
    formattedTime = datetime.timedelta(seconds=elapsedTime)
    formattedTime = str(formattedTime).split(".")[0]
    print(f"\nProgram interrupted after (H:MM:SS): {formattedTime}")
    if signal.Signals(signalType).name != signal.SIGINT.name:
        print(f"{signalType}{frame}")
    sys.exit(0)

def main():
    parser = argparse.ArgumentParser(
        prog='cbmcPlan',
        description='Converts PDDL files into a C program and solves it using CBMC'
    )
    parser.add_argument('-d', '--domain', type=str, default=False,
                        help='Specifies the domain PDDL file, if required')
    parser.add_argument('-p', '--problem', type=str, default=False,
                        help='Specifies the problem PDDL file, if required')
    parser.add_argument('-f', '--folder', type=str, default=False,
                        help='Folder containing files for batch processing')
    parser.add_argument('-sd', '--startingDepth', type=int, default=1,
                        help='Initial depth of the solver, default is 1')
    parser.add_argument('-ds', '--depthStep', type=int, default=1,
                        help='Depth increment between solving attempts, default is 1')
    parser.add_argument('-md', '--maxDepth', type=int, default=0,
                        help='Maximum depth the solver is allowed to reach')
    parser.add_argument('-m', '--manualDepth', type=int, default=0,
                        help='Run the solver once at the specified depth')
    parser.add_argument('-pt', '--problemTimeout', type=int, default=0,
                        help='Set timeout in seconds for each PDDL problem')
    parser.add_argument('-dt', '--depthTimeout', type=int, default=300,
                        help='Set timeout in seconds for each depth level, default is 300 seconds; set to 0 to disable')
    parser.add_argument('-ga', '--geometricAllocation', type=float, default=0,
                        help='Manage geometric allocation; value <= 1 disables it. Specify the common factor for the '
                             'geometric series. E.g., 2 means the max depth will get half the total time, 3 means '
                             'two-thirds. Conversely, 1.5 means one-third of the time, and 1.25 means one-fourth. '
                             'Overrides depth timeout.')
    parser.add_argument('-s', '--stateSize', type=float, default=1,
                        help='State size as a percentage: e.g., 0.2 means 20% of the maximum possible size')
    parser.add_argument('-v', '--verbose', action='store_true', default=False,
                        help='Enable verbose output on the command line')
    parser.add_argument('-c', '--concise', action='store_true', default=False,
                        help='Enable concise output on the command line')
    parser.add_argument('-l', '--load', action='store_true', default=False,
                        help='Continue execution from where it was interrupted')
    parser.add_argument('-si', '--stopOnInvalid', action='store_true', default=False,
                        help='Stops the program execution on the first invalid problem, instead of continuing')
    parser.add_argument('-n', '--numRuns', type=int, default=1,
                        help='number of times to run each problem')

    args = parser.parse_args()
    global domain, problem, multi, startingDepth, depthStep, maxDepth, manualDepth, verbose, concise
    global pTimeout, dTimeout, geoAllocation, stateSize, loadBool, stopOnInvalid, startTime, numRuns

    # XOR check
    if bool(args.domain) != bool(args.problem):
        parser.error('--domain and --problem must be given together')
    elif bool(args.domain) and bool(args.problem) and not bool(args.folder):
        domain = args.domain
        problem = args.problem
        multi = False
    else:
        if bool(args.domain) and bool(args.problem):
            parser.error("Specify either singular files or folder location for batch processing")
        if bool(args.folder):
            inFolder = args.folder
        else:
            inFolder = "input"

        os.makedirs(inFolder, exist_ok=True)
        multi = True
        domain = inFolder
        problem = domain

    if bool(args.geometricAllocation) and (not bool(args.maxDepth) or not bool(args.problemTimeout)):
        parser.error('if using --geometricAllocation, must set a --maxDepth and a --problemTimeout')

    startingDepth = args.startingDepth
    depthStep = args.depthStep
    maxDepth = args.maxDepth
    manualDepth = args.manualDepth
    verbose = args.verbose
    concise = args.concise
    pTimeout = args.problemTimeout
    dTimeout = args.depthTimeout
    geoAllocation = args.geometricAllocation
    stateSize = args.stateSize
    loadBool = args.load
    stopOnInvalid = args.stopOnInvalid
    numRuns = args.numRuns

    startTime = timeit.default_timer()
    signal.signal(signal.SIGINT, inturruptHandler)

    run()

    endTime = timeit.default_timer()
    elapsedTime = endTime - startTime
    formattedTime = datetime.timedelta(seconds=elapsedTime)
    formattedTime = str(formattedTime).split(".")[0]

    print("------------------------")
    print("overall run time (H:MM:SS): " + str(formattedTime))
    print("------------------------")

if __name__ == "__main__":
    main()