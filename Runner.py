import argparse
import os
import re
import sys
import timeit
import datetime

from ParsePDDL import parse
from CProgramWriter import writeProgram
from CBMCSolver import solve
from LogWriter import writeLogs
from Validator import validate

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
        global startingDepth, depthStep, maxDepth, manualDepth, verbose, concise, pTimeout, dTimeout, geoAllocation, stateSize
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

def executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, problemFile, domainFile, positionInfo = None):
    #first step write the c program
    if positionInfo is None:
        print("writing c program")
    else:
        print(f"writing c program {positionInfo[0]}/{positionInfo[1]}")
    cFile, realStateSize, objectToNum, problemName = writeProgram(parsedProblem, cOutFolder, stateSize)
    oldActionNames = list()
    newActionNames = list()
    for act in parsedProblem.actions:
        oldName = act.name
        newName = oldName.replace("-", "_")
        oldActionNames.append(oldName)
        newActionNames.append(newName)
    #second step solve the c program
    cName = str(cFile).split("/")[-1]
    if concise:
        print(f"solving {problemName} with CBMC")
    else:
        print(f"solving {problemName} with CBMC:")
    results = solve(cFile, maxDepth, manualDepth, startingDepth, depthStep, oldActionNames, newActionNames,
                    objectToNum, concise, verbose, pTimeout, dTimeout, geoAllocation)
    #third step validate the solution
    stopExecution = False
    if bool(results[0]):
        print(f"validating plan to solve {cName}:")
        valid = validate(results[0], domainFile, problemFile, verbose)
        if valid:
            print("\tplan valid")
        else:
            print("\tplan invalid")
    else:
        valid = False
    if stopOnInvalid and not valid:
        stopExecution = True
    #fourth step write the logs
    problemLogs = writeLogs(problemName, logOutFolder, results, valid, stateSize, realStateSize, pTimeout, dTimeout, maxDepth, geoAllocation)
    return problemLogs, stopExecution

def sorted_nicely( l ):
    """function by Mark Byers
    sourced from https://stackoverflow.com/questions/2669059/how-to-sort-alpha-numeric-set-in-python"""
    """ Sort the given iterable in the way that humans expect."""
    convert = lambda text: int(text) if text.isdigit() else text
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ]
    return sorted(l, key = alphanum_key)

def run():
    logs = list()
    allowedRequirements = [":strips", ":typing", ":equality", ":disjunctive-preconditions", ":negation",
                           ":negative-preconditions"]
    # TODO, ":conditional-effects", ":universal-preconditions", ":quantified-preconditions",
    #  ":existential-preconditions", ":adl", ":derived-predicates", ":action-costs",":fluents", ":numeric-fluents",
    #  ":domain-axioms", ":safety-constraints", ":ucpop"]

    # unimplemented requirements needed by supurviser domains:
    # cave-diving: conditional-effects  action-costs
    # GED: adl(quantified-preconditions(universal-preconditions existential-preconditions) conditional-effects)
    #   derived-predicates fluents action-costs functions(numeric-fluents)
    # I don't think that this can support action-costs as CBMC does not support them
    # Fully supported:
    # pipesworld-tankage: n/a

    # requirements not currently planned to be implemented:
    #   :action-expansions :foreach-expansions :dag-expansions :subgoals-through-axioms :expression-evaluation
    #   :open-world :true-negation :durative-actions :durative-inequalities :continuous-effects :timed-initial-literals
    #   :preferences :constraints
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
                    name = temp.split(")")[0]
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
                            f"Sorry the allowed requirements are currently limited and {requirement} is not allowed")
                log, stopExecution = executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, prob, domains[dom], (problemNum, numProblems))
                problemNum += 1
                problemsRun.append(prob)
                save(problemsRun, inputFolder, cOutFolder, logOutFolder, problemNum, numProblems)
                logs.append(log)
                if stopExecution:
                    break
    else:
        print(f"Combining Domain: {domain} with problem: {problem}")
        parsedProblem = parse(domain, problem)
        rootFolder = problem.rsplit("/", 1)[0]
        for requirement in parsedProblem.requirements.requirements:
            if requirement not in allowedRequirements:
                raise ValueError(
                    f"Sorry the allowed requirements are currently limited and {requirement} is not allowed")
        cOutFolder = f"{rootFolder}/output/cFiles"
        logOutFolder = f"{rootFolder}/output/logs"
        log = executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, problem, domain)
        logs.append(log)
    if not concise:
        first = True
        print("\\|/\\|/\\|/\\|/\\|/\\|/\\|/\\|/")
        for log in logs:
            if not first:
                print("")
            else:
                first = False
            if verbose:
                print(log[0])
            else:
                print(log[1])

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='cbmcPlan',
                                     description='Converts PDDL files into a C program and solves it using CBMC')
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
                        help='stops the program execution on the first invalid solution found, instead of continuing')
    args = parser.parse_args()
    #XOR check
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

    startTime = timeit.default_timer()
    run()
    endTime = timeit.default_timer()
    time = endTime - startTime
    time = datetime.timedelta(seconds=time)
    time = str(time).split(".")[0]
    print("/|\\/|\\/|\\/|\\/|\\/|\\/|\\/|\\")
    print("overall run time(H:MM:SS): " + str(time))
    # TODO: madagascar: test problems in another planning tool to get plan lengths
    # TODO: Implement Regression Testing
    # TODO: test each problem with different depths, timeouts, and state sizes then make graph
    # TODO: write report