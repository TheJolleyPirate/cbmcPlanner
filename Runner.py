import argparse
import os
import re
import timeit
import datetime
from pathlib import Path

from ParsePDDL import parse
from CProgramWriter import writeProgram
from CBMCSolver import solve
from LogWriter import writeLogs
from Validator import validate
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
    results = solve(cFile, maxDepth, depth, startingDepth, depthStep, manual, oldActionNames, newActionNames,
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
    problemLogs = writeLogs(problemName, logOutFolder, results, valid, stateSize, realStateSize, pTimeout, dTimeout)
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
    allowedRequirements = [":strips", ":typing", ":equality"]  # TODO , ":negation"]#, ":conditional-effects"]
    if multi:
        inputFolder = domain
        files = os.listdir(inputFolder)
        if inputFolder == "input":
            cOutFolder = "output/cFiles"
            logOutFolder = "output/logs"
        else:
            cOutFolder = str(inputFolder) + "/output/cFiles"
            logOutFolder = str(inputFolder) + "/output/logs"
        Path(cOutFolder).mkdir(parents=True, exist_ok=True)
        Path(logOutFolder).mkdir(parents=True, exist_ok=True)
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
        numProblems = len(problemFiles)
        problemNum = 1
        for dom in domains:
            problems = domainProblems[dom]
            for prob in problems:
                parsedProblem = parse(domains[dom], prob)
                for requirement in parsedProblem.requirements.requirements:
                    if requirement not in allowedRequirements:
                        raise ValueError(
                            "Sorry the allowed requirements are currently limited and " + requirement + " is not allowed")
                log = executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, prob, domains[dom], (problemNum, numProblems))
                problemNum += 1
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
        Path(cOutFolder).mkdir(parents=True, exist_ok=True)
        Path(logOutFolder).mkdir(parents=True, exist_ok=True)
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
                                     description='translates PDDL into a c program then solves it using CBMC')
    parser.add_argument('-d', '--domain', type=str, help='the domain PDDL file if needed')
    parser.add_argument('-p', '--problem', type=str, help='the problem PDDL file if needed')
    parser.add_argument('-sd', '--startingDepth', type=int, default=1, help='the starting depth of the solver, default 1')
    parser.add_argument('-ds', '--depthStep', type=int, default=1, help='the amount the depth changes between solve attempts, default 1')
    parser.add_argument('-md', '--maxDepth', type=int, default=None,
                        help='the maximum depth of the solver, default max theoretical depth of problem')
    parser.add_argument('-dp', '--depth', type=int, default=None, help='the depth you want to run the solver at, only matters if using manual')
    parser.add_argument('-m', '--manual', action='store_true', default=False,
                        help='if set will run solver only once either at the given depth, or at max theoretical depth '
                             'of problem')
    parser.add_argument('-f', '--folder', type=Path, default=False,
                        help='the folder containing the files to batch process')
    parser.add_argument('-v', '--verbose', action='store_true', default=False,
                        help='makes the command line output verbose')
    parser.add_argument('-c', '--concise', action='store_true', default=False,
                        help='makes the command line output verbose')
    parser.add_argument('-pt', '--problemTimeout', type=int, default=False,
                        help='gives a timeout for running each PDDL problem')
    parser.add_argument('-dt', '--depthTimeout', type=int, default=300,
                        help='set the timeout for running at each depth of problem(s), default: 300, set to 0 to disable')
    parser.add_argument('-ga', '--geometricAllocation', type=float, default=0,
                        help='controls the geometric allocation; >=1 turns it off, otherwise sets common factor for geometric series. '
                             'E.g. 2 means the max depth will have 1/2 the total time and 3 means the max depth will have 2/3 the total time'
                             'converesly 1.5 means the max depth will have 1/3 of the total time and 1.25 means the max depth has 1/4 the total time.'
                             'Overrides depth timeout')
    parser.add_argument('-s', '--stateSize', type=float, default=1,
                        help='state size; 0-1 percentage based: e.g. 0.2 = 20% max possible size, >1 sets static state size')
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
    if bool(args.manual) ^ bool(args.depth):
        parser.error('--manual and --depth must be given together')
    startingDepth = args.startingDepth
    depthStep = args.depthStep
    maxDepth = args.maxDepth
    depth = args.depth
    manual = args.manual
    verbose = args.verbose
    concise = args.concise
    pTimeout = args.problemTimeout
    dTimeout = args.depthTimeout
    geoAllocation = args.geometricAllocation
    stateSize = args.stateSize

    startTime = timeit.default_timer()
    run()
    endTime = timeit.default_timer()
    time = endTime - startTime
    time = datetime.timedelta(seconds=time)
    print("/|\\/|\\/|\\/|\\/|\\/|\\/|\\/|\\")
    print("overall run time(H:MM:SS): " + str(time))