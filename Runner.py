import argparse
import os
import re
import sys
import timeit
import datetime
from wakepy import keep

from ParsePDDL import parse
from CProgramWriter import writeProgram
from CBMCSolver import solve
from LogWriter import writeLogs
from Validator import validate

def save(problemsRun, inputFolder, cOutFolder, logOutFolder, problemNum, numProblems):
    el = "\n"
    lineBreak = "<><><><><><><><><>" + el
    toWrite = lineBreak
    toWrite += str(inputFolder) + el
    toWrite += str(cOutFolder) + el
    toWrite += str(logOutFolder) + el
    toWrite += str(startingDepth) + el
    toWrite += str(depthStep) + el
    toWrite += str(maxDepth) + el
    toWrite += str(manualDepth) + el
    toWrite += str(verbose) + el
    toWrite += str(concise) + el
    toWrite += str(pTimeout) + el
    toWrite += str(dTimeout) + el
    toWrite += str(geoAllocation) + el
    toWrite += str(stateSize) + el
    toWrite += str(problemNum) + el
    toWrite += str(numProblems) + el
    toWrite += lineBreak
    for prob in problemsRun:
        toWrite += prob + el
    saveFile = open("save.txt", "w")
    saveFile.write(toWrite)
    saveFile.close()

def load():
    try:
        saveFile = open("save.txt", "r")
        lineBreak = "<><><><><><><><><>\n"
        parts = saveFile.read().split(lineBreak)
        arguments = parts[0].splitlines()
        problems = parts[1].splitlines()
        saveFile.close()
        inputFolder = arguments[0]
        cOutFolder = arguments[1]
        logOutFolder = arguments[2]
        global startingDepth
        startingDepth = int(arguments[3])
        global depthStep
        depthStep = int(arguments[4])
        global maxDepth
        maxDepth = int(arguments[5])
        global manualDepth
        manualDepth = int(arguments[6])
        global verbose
        verbose = eval(arguments[7])
        global concise
        concise = eval(arguments[8])
        global pTimeout
        pTimeout = int(arguments[9])
        global dTimeout
        dTimeout = int(arguments[10])
        global geoAllocation
        geoAllocation = int(arguments[11])
        global stateSize
        stateSize = int(arguments[12])
        problemNum = int(arguments[13])
        numProblems = int(arguments[14])
        return problems, inputFolder, cOutFolder, logOutFolder, problemNum, numProblems
    except FileNotFoundError as err:
        print("save file not found", file=sys.stderr)
        raise err
def executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, problemFile, domainFile, positionInfo = None):
    #first step write the c program
    if positionInfo is None:
        print("writing c program")
    else:
        print("writing c program " + str(positionInfo[0]) + "/" + str(positionInfo[1]))
    programDetails = writeProgram(parsedProblem, cOutFolder, stateSize)
    cFile = programDetails[0]
    problemName = programDetails[3]
    realStateSize = programDetails[1]
    objectToNum = programDetails[2]
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
        print("solving " + problemName + " with CBMC")
    else:
        print("solving " + problemName + " with CBMC:")
    results = solve(cFile, maxDepth, manualDepth, startingDepth, depthStep, oldActionNames, newActionNames,
                    objectToNum, concise, verbose, pTimeout, dTimeout, geoAllocation)
    #third step validate the solution
    if bool(results[0]):
        print("validating plan to solve " + cName + ":")
        valid = validate(results[0], domainFile, problemFile, verbose)
        if valid:
            print("\tplan valid")
        else:
            print("\tplan invalid")
    else:
        valid = False
    #fourth step write the logs
    problemLogs = writeLogs(problemName, logOutFolder, results, valid, stateSize, realStateSize, pTimeout, dTimeout, maxDepth)
    return problemLogs

def sorted_nicely( l ):
    """function by Mark Byers
    sourced from https://stackoverflow.com/questions/2669059/how-to-sort-alpha-numeric-set-in-python"""
    """ Sort the given iterable in the way that humans expect."""
    convert = lambda text: int(text) if text.isdigit() else text
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ]
    return sorted(l, key = alphanum_key)

def run():
    logs = list()
    allowedRequirements = [":strips", ":typing", ":equality", ":disjunctive-preconditions"]
    # TODO, ":negation", ":conditional-effects", ":negative-preconditions", ":universal-preconditions",
    #  ":quantified-preconditions", ":existential-preconditions", ":adl", ":derived-predicates", ":action-costs",
    #  ":fluents", ":numeric-fluents", ":domain-axioms", ":safety-constraints", ":ucpop"]

    # unimplemented requirements needed by supurviser domains:
    # cave-diving: conditional-effects negative-preconditions action-costs
    # GED: adl(quantified-preconditions(universal-preconditions existential-preconditions) conditional-effects) derived-predicates fluents action-costs functions(numeric-fluents)
    # pipesworld-tankage: no extra requirements

    # requirements not currently planned to be implemented
    # :action-expansions :foreach-expansions :dag-expansions :subgoals-through-axioms :expression-evaluation
    # :open-world :true-negation :durative-actions :durative-inequalities :continuous-effects :timed-initial-literals
    # :preferences :constraints
    if multi:
        problemNum = None
        numProblems = None
        if load:
            results = load()
            problemsRun = results[0]
            inputFolder = results[1]
            cOutFolder = results[2]
            logOutFolder = results[3]
            problemNum = results[4]
            numProblems = results[5]
        else:
            inputFolder = domain
            problemsRun = list()
            if inputFolder == "input":
                cOutFolder = "output/cFiles"
                logOutFolder = "output/logs"
            else:
                cOutFolder = str(inputFolder) + "/output/cFiles"
                logOutFolder = str(inputFolder) + "/output/logs"
        files = os.listdir(inputFolder)
        pddlFiles = list()
        domainProblems = dict()
        domains = dict()
        problemFiles = list()
        files = sorted_nicely(files)
        for file in files:
            if ".pddl" in file:
                current = str(inputFolder) + "/" + file
                pddlFiles.append(current)
                contents = open(current, "r").read()
                if "(define (domain " in contents:
                    temp = contents
                    temp = temp.split("(define (domain ")[1]
                    name = temp.split(")")[0]
                    domains.update({name: current})
                    domainProblems.update({name: list()})
                else:
                    problemFiles.append(file)
        for pFile in problemFiles:
            current = str(inputFolder) + "/" + pFile
            contents = open(current, "r").read()
            temp = contents
            temp = temp.split("(:domain ")[1]
            currentDomain = temp.split(")")[0]
            for dom in domains:
                if currentDomain == dom:
                    domainProblems[dom].append(current)
                    break
        if not load:
            numProblems = len(problemFiles)
            problemNum = 1
        runProblems = list()
        for dom in domains:
            problems = domainProblems[dom]
            for prob in problems:
                if prob in problemsRun:
                    continue
                print("combining Domain: " + domain + " with problem: " + problem)
                parsedProblem = parse(domains[dom], prob)
                for requirement in parsedProblem.requirements.requirements:
                    if requirement not in allowedRequirements:
                        raise ValueError(
                            "Sorry the allowed requirements are currently limited and " + requirement + " is not allowed")
                log = executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, prob, domains[dom], (problemNum, numProblems))
                problemNum += 1
                runProblems.append(prob)
                save(prob, cOutFolder, logOutFolder, problemNum, numProblems)
                logs.append(log)
    else:
        print("combining Domain: " + domain + " with problem: " + problem)
        parsedProblem = parse(domain, problem)
        rootFolder = problem.rsplit("/", 1)[0]
        for requirement in parsedProblem.requirements.requirements:
            if requirement not in allowedRequirements:
                raise ValueError(
                    "Sorry the allowed requirements are currently limited and " + requirement + " is not allowed")
        cOutFolder =  rootFolder + "/output/cFiles"
        logOutFolder = rootFolder + "/output/logs"
        log = executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, problem, domain)
        logs.append(log)
    if not concise:
        first = True
        print("\\|/\\|/\\|/\\|/\\|/\\|/\\|/\\|/")
        for log in logs:
            if not first:
                print("******************")
            if "failed" in log:
                print(log)
            else:
                print(log)

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
    args = parser.parse_args()
    if bool(args.domain) ^ bool(args.problem):
        parser.error('--domain and --problem must be given together')
    elif bool(args.domain) and bool(args.problem) and not bool(args.folder):
        domain = args.domain
        problem = args.problem
        multi = False
    else:
        if bool(args.domain) and bool(args.problem):
            parser.error("You should specify either singular files, or folder location, assuming you want to batch "
                         "process from file location")
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
    load = args.load
    with keep.running():
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