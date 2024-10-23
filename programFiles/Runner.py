import argparse
import os
import signal
import sys
import timeit
import datetime

from programFiles.ParsePDDL import parse
from programFiles.CProgramWriter import writeProgram
from programFiles.CBMCSolver import solve
from programFiles.LogWriter import writeLogs, corrolate, sortedNicely
from programFiles.Validator import validate

#global variables, set by arguments
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
loadSnapshotBool = False
stopOnInvalid = False
numRuns = 1

def __saveSnapshot(problemsRun, inputFolder, problemNum, numProblems, runNumber = 0):
    """saves the current progress of the solver through the problems
    so that it can be contiuned if execution is inturrupted"""
    lineBreak = "<><><><><><><><><>\n"
    
    toWrite = f"input folder: {inputFolder}\n"
    toWrite += f"starting depth: {startingDepth}\n"
    toWrite += f"depth step: {depthStep}\n"
    toWrite += f"max depth: {maxDepth}\n"
    toWrite += f"manual depth: {manualDepth}\n"
    toWrite += f"verbose: {verbose}\n"
    toWrite += f"concise: {concise}\n"
    toWrite += f"p timeout: {pTimeout}\n"
    toWrite += f"d timeout: {dTimeout}\n"
    toWrite += f"geo allocation: {geoAllocation}\n"
    toWrite += f"state size: {(stateSize * 100)}%\n"
    if problemNum is None:
        toWrite += f"problem number: NAN\n"
    else:
        toWrite += f"problem number: {problemNum}\n"
    if problemNum is None:
        toWrite += f"number of problems: NAN\n"
    else:
        toWrite += f"number of problems: {numProblems}\n"
    toWrite += f"run number: {runNumber + 1}\n"
    toWrite += f"number of runs: {numRuns}\n"
    toWrite += f"stop on invalid: {stopOnInvalid}\n"
    toWrite += lineBreak

    for prob in problemsRun:
        toWrite += f"{prob}\n"

    with open("save.txt", "w") as saveFile:
        saveFile.write(toWrite)

def __loadSnapshot():
    """loads the current snapshot so that execution can be continued from where it has halted"""
    try:
        with open("save.txt", "r") as saveFile:
            lineBreak = "<><><><><><><><><>\n"
            parts = saveFile.read().split(lineBreak)
            arguments = parts[0].splitlines()
            problems = parts[1].splitlines()
    except FileNotFoundError as err:
        print("save file not found", file=sys.stderr)
        raise err

    global startingDepth, depthStep, maxDepth, manualDepth, stopOnInvalid
    global verbose, concise, pTimeout, dTimeout, geoAllocation, stateSize, numRuns

    inputFolder = arguments[0].split(": ")[1]
    startingDepth = int(arguments[1].split(": ")[1])
    depthStep = int(arguments[2].split(": ")[1])
    maxDepth = int(arguments[3].split(": ")[1])
    manualDepth = int(arguments[4].split(": ")[1])
    verbose = eval(arguments[5].split(": ")[1])
    concise = eval(arguments[6].split(": ")[1])
    pTimeout = int(arguments[7].split(": ")[1])
    dTimeout = int(arguments[8].split(": ")[1])
    geoAllocation = float(arguments[9].split(": ")[1])

    percentageStateSize = int(float(arguments[10].split(": ")[1][:-1]))
    stateSize = percentageStateSize / 100
    try:
        problemNum = int(arguments[11].split(": ")[1])
    except ValueError:
        problemNum = None
    try:
        numProblems = int(arguments[12].split(": ")[1])
    except ValueError:
        numProblems = None

    runNum = int(arguments[13].split(": ")[1]) - 1
    numRuns = int(arguments[14].split(": ")[1])
    stopOnInvalid = eval(arguments[15].split(": ")[1])
    return problems, inputFolder, problemNum, numProblems, runNum

def __executeSingleProblem(parsedProblem, inputFolder, cOutFolder, logOutFolder, problemFile, domainFile, runNum = 0,
                           problemsRun=None, positionInfo=None):
    """takes a single PDDL problem and writes its corresponding C program and then runs the solver"""
    if problemsRun is None:
        problemsRun = list()
    if positionInfo is None:
        positionInfo = [None, None]
    cFile = None
    realStateSize = None
    objectToNum = None
    problemName = None
    oldActionNames = None
    newActionNames = None
    cName = None
    first = True
    stopExecution = False
    localConcise = concise
    for iteration in range(runNum, numRuns):
        if first:
            if positionInfo[0] is None:
                print(f"writing c program with state size: {stateSize * 100}%")
            else:
                print(f"writing c program {positionInfo[0]}/{positionInfo[1]} with state size: {stateSize * 100}%")
            # write the c file
            cFile, realStateSize, objectToNum, problemName = writeProgram(parsedProblem, cOutFolder, stateSize)
            oldActionNames = list()
            newActionNames = list()
            for act in parsedProblem.actions:
                oldName = act.name
                newName = oldName.replace("-", "_")
                oldActionNames.append(oldName)
                newActionNames.append(newName)
            cName = str(cFile).split("/")[-1]
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
        __saveSnapshot(problemsRun, inputFolder, positionInfo[0], positionInfo[1], iteration + 1)
        if stopOnInvalid and not valid:
            stopExecution = True
            break
    return stopExecution

def __run():
    """takes a folder as input and then runs every PDDL problem in the folder, including subfolders
    can also run a singular PDDL problem if given"""
    allowedRequirements = [":strips", ":typing", ":equality", ":disjunctive-preconditions", 
                           ":negation", ":negative-preconditions"]
    # TODO, ":conditional-effects", ":universal-preconditions", ":quantified-preconditions",
    #  ":existential-preconditions", ":adl", ":derived-predicates", ":action-costs",":fluents", ":numeric-fluents",
    #  ":domain-axioms", ":safety-constraints", ":ucpop"]
    if multi:
        problemNum = None
        numProblems = None
        
        if loadSnapshotBool:
            problemsRun, inputFolder, problemNum, numProblems, runNum = __loadSnapshot()
        else:
            inputFolder = domain
            problemsRun = list()
            runNum = 0

        pddlFiles = list()
        domainProblems = dict()
        domains = dict()
        problemFiles = list()
        files = list()
        for p, s, f in os.walk(inputFolder):
            for file in f:
                toAdd = os.path.join(p, file)
                files.append(toAdd)
        files = sortedNicely(files)
        for file in files:
            if file.endswith(".pddl"):
                pddlFiles.append(file)
                
                with open(file, "r") as f:
                    contents = f.read()
                
                if "(define (domain " in contents:
                    temp = contents.split("(define (domain ")[1]
                    name = temp.split(")", 1)[0]
                    domains[name] = file
                    domainProblems[name] = list()
                else:
                    problemFiles.append(file)

        if problemNum is None:
            numProblems = len(problemFiles)
            problemNum = 1

        for pFile in problemFiles:
            with open(pFile, "r") as f:
                contents = f.read()
            
            temp = contents.split("(:domain ")[1]
            currentDomain = temp.split(")")[0]
            
            if currentDomain in domains:
                domainProblems[currentDomain].append(pFile)
        outputFolder = f"{inputFolder}/output"
        logFolders = set()
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
                currentFolder = prob.rsplit("/", 1)[0]
                uniquePath = currentFolder.split(f"{inputFolder}/", 1)[1]
                cOutFolder = f"{outputFolder}/{uniquePath}/cFiles"
                logOutFolder = f"{outputFolder}/{uniquePath}/logs"
                logFolders.add(logOutFolder)

                stopExecution = __executeSingleProblem(parsedProblem, inputFolder, cOutFolder, logOutFolder,
                                                       prob, domains[dom], runNum, problemsRun, (problemNum, numProblems))
                problemNum += 1
                runNum = 0
                problemsRun.append(prob)
                __saveSnapshot(problemsRun, inputFolder, problemNum, numProblems)
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
        outputFolder = f"{rootFolder}/output"
        cOutFolder = f"{outputFolder}/cFiles"
        logOutFolder = f"{outputFolder}/logs"
        logFolders = {logOutFolder}
        __executeSingleProblem(parsedProblem, rootFolder, cOutFolder, logOutFolder, problem, domain)
    for folder in logFolders:
        corrolate(folder)
    if not concise:
        print("logs printed to:")
        print(f"\t{os.path.abspath(outputFolder)}")

def inturruptHandler(signalType, frame):
    """catches SIGINT (ctrl-c) inturrupts.
    So that the time the program has been running for can be printed before stopping"""
    global startTime
    intTime = timeit.default_timer()
    elapsedTime = intTime - startTime
    formattedTime = datetime.timedelta(seconds=elapsedTime)
    formattedTime = str(formattedTime).split(".")[0]
    print(f"\nProgram interrupted after (H:MM:SS): {formattedTime}")
    if signal.Signals(signalType).name != signal.SIGINT.name:
        print(f"{signalType}{frame}")
    sys.exit(0)

def __saveInit():
    """saves the current run options to an init file so they can be used easily in the future"""
    toWrite = f"starting depth: {startingDepth}\n"
    toWrite += f"depth step: {depthStep}\n"
    toWrite += f"max depth: {maxDepth}\n"
    toWrite += f"manual depth: {manualDepth}\n"
    toWrite += f"verbose: {verbose}\n"
    toWrite += f"concise: {concise}\n"
    toWrite += f"p timeout: {pTimeout}\n"
    toWrite += f"d timeout: {dTimeout}\n"
    toWrite += f"geo allocation: {geoAllocation}\n"
    toWrite += f"state size: {(stateSize * 100)}%\n"
    toWrite += f"number of runs: {numRuns}\n"
    toWrite += f"stop on invalid: {stopOnInvalid}\n"

    with open("init.txt", "w") as saveFile:
        saveFile.write(toWrite)

def __loadInit():
    """loads the run settings from an init file"""
    try:
        with open("init.txt", "r") as saveFile:
            arguments = saveFile.read().splitlines()

        global startingDepth, depthStep, maxDepth, manualDepth, stopOnInvalid
        global verbose, concise, pTimeout, dTimeout, geoAllocation, stateSize, numRuns

        startingDepth = int(arguments[0].split(": ")[1])
        depthStep = int(arguments[1].split(": ")[1])
        maxDepth = int(arguments[2].split(": ")[1])
        manualDepth = int(arguments[3].split(": ")[1])
        verbose = eval(arguments[4].split(": ")[1])
        concise = eval(arguments[5].split(": ")[1])
        pTimeout = int(arguments[6].split(": ")[1])
        dTimeout = int(arguments[7].split(": ")[1])
        geoAllocation = float(arguments[8].split(": ")[1])

        percentageStateSize = int(float(arguments[9].split(": ")[1][:-1]))
        stateSize = percentageStateSize / 100
        numRuns = int(arguments[10].split(": ")[1])
        stopOnInvalid = eval(arguments[11].split(": ")[1])

    except FileNotFoundError as err:
        print("init file not found", file=sys.stderr)
        raise err

def __main(p):
    """parses the program arguments before running the code"""
    args = p.parse_args()
    global domain, problem, multi, startingDepth, depthStep, maxDepth, manualDepth, verbose, concise
    global pTimeout, dTimeout, geoAllocation, stateSize, loadSnapshotBool, stopOnInvalid, startTime, numRuns
    loadSnapshotBool = args.load
    if not loadSnapshotBool:
        # XOR check
        if bool(args.domain) != bool(args.problem):
            p.error('--domain and --problem must be given together')
        elif bool(args.domain) and bool(args.problem) and not bool(args.folder):
            domain = args.domain
            problem = args.problem
            multi = False
        else:
            if bool(args.domain) and bool(args.problem):
                p.error("Specify either singular files or folder location for batch processing")
            if bool(args.folder):
                inFolder = args.folder
            else:
                inFolder = "input"

            os.makedirs(inFolder, exist_ok=True)
            multi = True
            domain = inFolder
            problem = domain

        if bool(args.geometricAllocation) and (not bool(args.maxDepth) or not bool(args.__problemTimeout)):
            p.error('if using --geometricAllocation, must set a --maxDepth and a --problemTimeout')
        loadInitBool = args.loadInit
        if not loadInitBool:
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
            stopOnInvalid = args.stopOnInvalid
            numRuns = args.numRuns
            saveInitBool = args.saveInit
            if saveInitBool:
                __saveInit()
        else:
            __loadInit()

    startTime = timeit.default_timer()
    signal.signal(signal.SIGINT, inturruptHandler)

    __run()

    endTime = timeit.default_timer()
    elapsedTime = endTime - startTime
    formattedTime = datetime.timedelta(seconds=elapsedTime)
    formattedTime = str(formattedTime).split(".")[0]

    print("------------------------")
    print("overall run time (H:MM:SS): " + str(formattedTime))
    print("------------------------")

def getArgs():
    """gets the program arguments"""
    parser = argparse.ArgumentParser(prog="cbmcPlan.py",
                                     description='Converts PDDL files into a C program and solves it using CBMC')
    parser.add_argument('folder', type=str, default="input",
                        help='Folder containing files for batch processing')
    parser.add_argument('-d', '--domain', type=str, default=False,
                        help='Specifies the domain PDDL file, if required')
    parser.add_argument('-p', '--problem', type=str, default=False,
                        help='Specifies the problem PDDL file, if required')
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
                        help='State size as a percentage: e.g., 0.2 means 20 percent of the maximum possible size')
    parser.add_argument('-v', '--verbose', action='store_true', default=False,
                        help='Enable verbose output on the command line')
    parser.add_argument('-c', '--concise', action='store_true', default=False,
                        help='Enable concise output on the command line')
    parser.add_argument('-l', '--load', action='store_true', default=False,
                        help='Continue execution from where it was interrupted')
    parser.add_argument('-si', '--saveInit', action='store_true', default=False,
                        help='save the current settings to init file')
    parser.add_argument('-li', '--loadInit', action='store_true', default=False,
                        help='load settings from init file')
    parser.add_argument('-so', '--stopOnInvalid', action='store_true', default=False,
                        help='Stops the program execution on the first invalid problem, instead of continuing')
    parser.add_argument('-n', '--numRuns', type=int, default=1,
                        help='number of times to run each problem')
    __main(parser)

if __name__ == "__main__":
    getArgs()