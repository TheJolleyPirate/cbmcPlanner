import argparse
import multiprocessing
import os
import subprocess
import timeit
import math
from time import sleep

from LogWriter import writeLogs

pTimeBool = False

def individualSolver(cFile: str, cmdList, depth, timeout, concise, verbose, lastStepTime, gAllocation):
    fileName = cFile.split("/")[-1]
    toProcess = False
    timeoutBool = False
    stateBool = False
    if verbose:
        if not lastStepTime:
            print(f"\trunning {fileName} with depth {depth}")
        else:
            temp = "{:0.2f}".format(lastStepTime)
            print(f"\trunning {fileName} with depth {depth}, previous depth time: {temp} seconds")
    elif not concise:
        if not lastStepTime:
            print(f"\r\trunning {fileName} with depth {depth}", end='')
        else:
            temp = "{:0.2f}".format(lastStepTime)
            print(f"\r\trunning {fileName} with depth {depth}, previous depth time: {temp} seconds", end='')
    cmdList[-1] = str(depth)
    try:
        start = timeit.default_timer()
        if bool(timeout):
            cmd = subprocess.run(cmdList, capture_output=True, text=True, timeout=timeout)
        else:
            cmd = subprocess.run(cmdList, capture_output=True, text=True)
        stop = timeit.default_timer()
        time = stop - start
        results = cmd.stdout
        err = cmd.stderr
        if err != "":
            raise subprocess.SubprocessError(err)
        goalChecker = results.split("Violated property:")
        #might have multiple violated properties
        #when solver has to internally change depth, it throws a violated property
        #should ignore these
        if "GOAL CHECKER: FAIL MEANS PLAN FOUND" in goalChecker[-1]:
            if not concise:
                temp = "{:0.2f}".format(time)
                print(f"\ntime: {temp} seconds")
            if verbose:
                print(results)
            if len(goalChecker) > 1:
                toProcess = goalChecker[-2]
            else:
                stateBool = True
    except subprocess.TimeoutExpired:
        if gAllocation <= 1:
            print("")
            timeoutBool = True
        time = timeout
    return toProcess, time, timeoutBool, stateBool

def problemTimeout(pTimeout):
    sleep(pTimeout)
    global pTimeBool
    pTimeBool = True

def currentTimeout(currentDepth, maxDepth, pTimeout, commonFactor):
    geometricSeries = (commonFactor ** maxDepth) / (commonFactor - 1)
    timeout = pTimeout * (commonFactor ** (currentDepth - 1)) / geometricSeries
    return timeout

def solveLoop(startDepth, maxDepth, depthStep, gAllocation, pTimeout, dtimeout, cFile, cmdList, concise, verbose):
    depth = startDepth - depthStep
    relativeMaxDepth = math.ceil((maxDepth - startDepth + 1) / depthStep)
    relativeCurrentDepth = 1
    toProcess = False
    timeoutBool = False
    currentTime = 0
    history = list()
    d = dtimeout
    while True:
        if bool(maxDepth):
            if depth >= maxDepth:
                break
        depth += depthStep
        if gAllocation > 1:
            d = currentTimeout(relativeCurrentDepth, relativeMaxDepth, pTimeout, gAllocation)
            relativeCurrentDepth += 1
        results = individualSolver(cFile, cmdList, depth, d, concise, verbose, currentTime, gAllocation)
        currentTime = results[1]
        planFound = bool(results[0])
        stateBool = results[3]
        if gAllocation <= 1:
            timeoutBool = results[2]
        if planFound or timeoutBool or pTimeBool or stateBool:
            toProcess = results[0]
            timeoutBool = results[2]
            break
        else:
            temp = (currentTime, depth)
            history.append(temp)
    return toProcess, currentTime, timeoutBool, depth, history, d

def solve(cFile, maxDepth, manualDepth, startDepth, depthStep, oldActionNames, newActionNames, objectToNum, concise,
          verbose, pTimeout, dTimeout, gAllocation):
    cbmcPath = os.path.abspath("externalTools/ubuntu-22-cbmc-6.1.1/cbmc")
    cmdList = [cbmcPath, cFile, "--compact-trace", "--unwind", ""]
    if not bool(manualDepth):
        global pTimeBool
        pTimeBool = False
        if pTimeout:
            probTimer = multiprocessing.Process(target=problemTimeout, args=[pTimeout])
            probTimer.start()
            results = solveLoop(startDepth, maxDepth, depthStep, gAllocation, pTimeout, dTimeout, cFile, cmdList,
                                concise, verbose)
            probTimer.terminate()
            probTimer.join()
        else:
            results = solveLoop(startDepth, maxDepth, depthStep, gAllocation, pTimeout, dTimeout, cFile, cmdList,
                                concise, verbose)
        toProcess = results[0]
        finalTime = results[1]
        timeoutBool = results[2]
        depth = results[3]
        history = results[4]
        timeout = results[5]
    else:
        depth = manualDepth
        results = individualSolver(cFile, cmdList, depth, dTimeout, concise, verbose, False, 0)
        toProcess = results[0]
        finalTime = results[1]
        timeoutBool = results[2]
        timeout = results[5]
        history = None
    if bool(toProcess) and not timeoutBool:
        lines = toProcess.splitlines()
        planList = list()
        #ran into error where action names containing shorter action names are ignored
        #e.g. unstack being read as stack
        #to fix this could sort newActionNames, but that is imprecise and introduces vulnerabilities
        #will collect names which match, and then pick the longest
        for line in lines:
            matches = list()
            for i in range(len(oldActionNames)):
                actionWithBracket = newActionNames[i] + "("
                if actionWithBracket in line:
                    matches.append(oldActionNames[i])
            if bool(matches):
                actionName = ""
                for match in matches:
                    if len(match) > len(actionName):
                        actionName = match
                temp = line + "\n"
                temp = temp.split(" ", 2)[2]
                temp = temp[:-1]
                temp = temp.split("(")[1]
                temp = temp[:-1]
                variableNums = temp.split(", ")
                action = actionName
                for varNum in variableNums:
                    var = objectToNum[int(varNum)]
                    action += " " + var
                planList.append(action)
        print(f"found plan: {planList}")
        planInfo = planList
    else:
        if timeoutBool:
            print(f"timeout: {timeout} seconds")
        else:
            print(f"no plan found with max depth: {maxDepth}")
        planInfo = False
    return planInfo, depth, finalTime, timeoutBool, history

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='cbmcSolve',
                                     description='solves a CBMC planning problem generated by CProgramWriter')
    parser.add_argument("cFile",type=str, help='the c File for CBMC to solve')
    parser.add_argument('-sd', '--startingDepth', type=int, default=1,
                        help='the starting depth of the solver, default 1')
    parser.add_argument('-ds', '--depthStep', type=int, default=1,
                        help='the amount the depth changes between solve attempts, default 1')
    parser.add_argument('-md', '--maxDepth', type=int, default=None,
                        help='the maximum depth of the solver, default max theoretical depth of problem')
    parser.add_argument('-m', '--manualDepth', type=int, default=0, help='runs the solver once at the '
                                                                         'specified depth')
    parser.add_argument('-v', '--verbose', action='store_true', default=False,
                        help='makes the command line output verbose')
    parser.add_argument('-c', '--concise', action='store_true', default=False,
                        help='makes the command line output verbose')
    parser.add_argument('-pt', '--problemTimeout', type=int, default=False,
                        help='gives a timeout for running each PDDL problem')
    parser.add_argument('-dt', '--depthTimeout', type=int, default=300,
                        help='set the timeout for running at each depth of problem(s), default: 300, set to 0 to '
                             'disable')
    parser.add_argument('-ga', '--geometricAllocation', type=float, default=0,
                        help='controls the geometric allocation; >=1 turns it off, otherwise sets common factor for '
                             'geometric series. E.g. 2 means the max depth will have 1/2 the total time and 3 means the'
                             ' max depth will have 2/3 the total time converesly 1.5 means the max depth will have 1/3 '
                             'of the total time and 1.25 means the max depth has 1/4 the total time. Overrides depth '
                             'timeout')
    args = parser.parse_args()
    cf = args.cFile
    md = args.maxDepth
    sd = args.startingDepth
    ds = args.depthStep
    m = args.manual
    c = args.concise
    v = args.verbose
    pt = args.problemTimeout
    dt = args.depthTimeout
    ga = args.geometricAllocation
    contents = open(cf, 'r').read()
    clines = contents.splitlines()
    otn = None
    stateSize = None
    breakCheck = [False, False]
    for cline in clines:
        if "//objectNames = {" in cline:
            names = cline.split("//objectNames = {")[1]
            names = names[:-2]
            otn = names.split(", ")
            breakCheck[0] = True
        if "int n = " in cline:
            stateSize = cline.split("int n = ")[1]
            stateSize = stateSize[:-1]
            stateSize = int(stateSize)
            breakCheck[1] = True
        if breakCheck[0] and breakCheck[1]:
            break

    if otn is None:
        raise ValueError("could not find variable names in c file")
    if stateSize is None:
        raise ValueError("could not find state size in c file")
    preamble = contents.split("//END OF PREAMBLE")[0]
    clines = preamble.splitlines()
    clines = clines[2:]
    oan = list()
    nan = list()
    for cline in clines:
        comparistion = cline[2:]
        actions = comparistion.split("==")
        nan.append(actions[0])
        oan.append(actions[1])
    r = solve(cf, md, m, sd, ds, oan, nan, otn, c, v, pt, dt, ga)
    loc = cf.rsplit("/", 1)
    rootFolder = loc[0]
    logOutFolder = rootFolder
    name = str(loc[1]).split(".c")[0]
    if r[3]:
        valid = False
    else:
        valid = None
    # TODO: get problem state size from c file
    logs = writeLogs(name, logOutFolder, r, valid, "unkown", stateSize, pt, dt, md)
    if v:
        print(logs[0])
    else:
        print(logs[1])