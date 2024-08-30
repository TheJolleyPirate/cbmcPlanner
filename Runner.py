import argparse
import os
from pathlib import Path
from ParsePDDL import parse
from CProgramWriter import writeProgram
from CMBCSolver import solve
from LogWriter import writeLogs
from Validator import validate


def executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, problemFile, domainFile):
    #first step write the c program
    print("writing c program")
    programDetails = writeProgram(parsedProblem, cOutFolder)
    cFile = programDetails[0]
    problemName = programDetails[3]
    stateSize = programDetails[1]
    global maxDepth
    if maxDepth is None:
        maxDepth = stateSize
    global depth
    if depth is None:
        depth = maxDepth
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
                    objectToNum, concise, verbose)
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
    problemLogs = writeLogs(problemName, logOutFolder, results, valid, stateSize)
    return problemLogs


def run():
    logs = list()
    if not multi:
        parsedProblem = parse(domain, problem)
        allowedRequirements = [":strips", ":typing", ":equality"]  # , ":negation"]#, ":conditional-effects"]
        for requirement in parsedProblem.requirements.requirements:
            if requirement not in allowedRequirements:
                raise ValueError(
                    "Sorry the allowed requirements are currently limited and " + requirement + " is not allowed")
        cOutFolder = "output/cFiles"
        logOutFolder = "output/logs"
        Path("/" + cOutFolder).mkdir(parents=True, exist_ok=True)
        Path("/" + logOutFolder).mkdir(parents=True, exist_ok=True)
        log = executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, problem, domain)
        logs.append(log)
    else:
        inputFolder = domain
        files = os.listdir(inputFolder)
        if inputFolder == "input":
            cOutFolder = "output/cFiles"
            logOutFolder = "output/logs"
        else:
            cOutFolder = inputFolder + "/output/cFiles"
            logOutFolder = inputFolder + "/output/logs"
        Path(cOutFolder).mkdir(parents=True, exist_ok=True)
        Path(logOutFolder).mkdir(parents=True, exist_ok=True)
        pddlFiles = list()
        domainProblems = dict()
        domains = dict()
        problemFiles = list()
        for file in files:
            if ".pddl" in file:
                current = inputFolder + "/" + file
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
            current = inputFolder + "/" + pFile
            contents = open(current, "r").read()
            temp = contents
            temp = temp.split("(:domain ")[1]
            currentDomain = temp.split(")")[0]
            for dom in domains:
                if currentDomain == dom:
                    domainProblems[dom].append(current)
                    break
        for dom in domains:
            problems = domainProblems[dom]
            for prob in problems:
                parsedProblem = parse(domains[dom], prob)
                log = executeSingleProblem(parsedProblem, cOutFolder, logOutFolder, prob, domains[dom])
                logs.append(log)
    if not concise:
        first = True
        print("\n\n\\|/\\|/\\|/\\|/\\|/\\|/\\|/\\|/")
        for log in logs:
            if not first:
                print("******************")
            print(log)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='PDDLtoC',
                                     description='translates PDDL into a c program which can be solved using CBMC')
    parser.add_argument('-d', '--domain', help='the domain PDDL file if needed')
    parser.add_argument('-p', '--problem', help='the problem PDDL file if needed')
    parser.add_argument('-sd', '--startingDepth', help='the starting depth of the solver, default 1')
    parser.add_argument('-ds', '--depthStep', help='the amount the depth changes between solve attempts, default 1')
    parser.add_argument('-md', '--maxDepth',
                        help='the maximum depth of the solver, default max theoretical depth of problem')
    parser.add_argument('-dp', '--depth', help='the depth you want to run the solver at, only matters if using manual')
    parser.add_argument('-m', '--manual', action='store_true',
                        help='if set will run solver only once either at the given depth, or at max theoretical depth '
                             'of problem')
    parser.add_argument('-f', '--folder',
                        help='the folder containing the files to batch process')
    parser.add_argument('-v', '--verbose', action='store_true',
                        help='makes the command line output verbose')
    parser.add_argument('-c', '--concise', action='store_true',
                        help='makes the command line output verbose')
    #problem timeout
    #depth timeout
    #geometric allocation

    args = parser.parse_args()
    multi = False
    inFolder = "input"
    verbose = False
    concise = False
    os.makedirs(inFolder, exist_ok=True)
    if bool(args.domain) ^ bool(args.problem):
        parser.error('--domain and --problem must be given together')
        exit(-1)
    elif bool(args.domain) and bool(args.problem):
        domain = args.domain
        problem = args.problem
    else:
        multi = True
        domain = "input"
        problem = domain
    if bool(args.startingDepth):
        startingDepth = args.startingDepth
    else:
        startingDepth = 1
    if bool(args.depthStep):
        depthStep = args.depthStep
    else:
        depthStep = 1
    if bool(args.maxDepth):
        maxDepth = args.maxDepth
    else:
        maxDepth = None
    if bool(args.depth):
        depth = args.depth
    else:
        depth = None
    if bool(args.manual):
        manual = True
    else:
        manual = False
    if bool(args.folder):
        if bool(args.domain) and bool(args.problem):
            parser.error("You should specify either singular files, or folder location, assuming you want to batch "
                         "process from file location")
        multi = True
        domain = args.folder
        problem = domain
    if bool(args.verbose):
        verbose = True
    if bool (args.concise):
        concise = True
    run()