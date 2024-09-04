import argparse
import multiprocessing
import os
import subprocess
import timeit
from pathlib import Path
from time import sleep

from sympy.logic.inference import valid

from LogWriter import writeLogs

pTimeBool = False

def individualSolver(cFile: str, cmdList, depth, timeout, concise, verbose, lastStepTime):
    fileName = cFile.split("/")[-1]
    toProcess = False
    timeoutBool = False
    if verbose:
        if not lastStepTime:
            print("running " + fileName + " with depth " + str(depth))
        else:
            temp = "{:0.2f}".format(lastStepTime)
            print("running " + fileName + " with depth " + str(depth) + ", previous depth time: " + str(temp) + " seconds")
    elif not concise:
        if not lastStepTime:
            print("\r\trunning " + fileName + " with depth " + str(depth), end='')
        else:
            temp = "{:0.2f}".format(lastStepTime)
            print("\r\trunning " + fileName + " with depth " + str(depth) + ", previous depth time: " + str(temp) + " seconds", end='')
    cmdList[-1] = str(depth)
    try:
        start = timeit.default_timer()
        cmd = subprocess.run(cmdList, capture_output=True, text=True, timeout=timeout)
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
                print("\ntime: " + temp + " seconds")
            if verbose:
                print(results)
            toProcess = goalChecker[-2]
    except subprocess.TimeoutExpired:
        print("")
        timeoutBool = True
        time = timeout
    return toProcess, time, timeoutBool

def problemTimeout(pTimeout):
    sleep(pTimeout)
    global pTimeBool
    pTimeBool = True

def solve(cFile, maxDepth, depth, startDepth, depthStep, manual, oldActionNames, newActionNames, objectToNum, concise, verbose, pTimeout, dTimeout):
    toProcess = False
    cbmcPath = os.path.abspath("externalTools/ubuntu-22-cbmc-6.1.1/cbmc")
    cmdList = [cbmcPath, cFile, "--compact-trace", "--unwind", ""]
    timeoutBool = False
    userTime = None
    time = 0
    if not manual:
        # TODO: implement geometric allocation, and problem timeout
        depth = startDepth - depthStep
        if pTimeout:
            global pTimeBool
            pTimeBool = False
            probTimer = multiprocessing.Process(target=sleep, args=[pTimeout])
            probTimer.start()
            while True:
                if maxDepth is not None:
                    if depth >= maxDepth:
                        break
                depth += depthStep
                results = individualSolver(cFile, cmdList, depth, dTimeout, concise, verbose, time)
                time = results[1]
                if bool(results[0]) or bool(results[2]) or pTimeBool:
                    toProcess = results[0]
                    userTime = time
                    timeoutBool = results[2]
                    probTimer.terminate()
                    probTimer.close()
                    break
        else:
            while True:
                if maxDepth is not None:
                    if depth >= maxDepth:
                        break
                depth += depthStep
                results = individualSolver(cFile, cmdList, depth, dTimeout, concise, verbose, time)
                time = results[1]
                if bool(results[0]) or bool(results[2]):
                    toProcess = results[0]
                    userTime = time
                    timeoutBool = results[2]
                    break
    else:
        results = individualSolver(cFile, cmdList, depth, dTimeout, concise, verbose, False)
        toProcess = results[0]
        userTime = results[1]
        timeoutBool = results[2]
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
        print("found plan: " + str(planList))
        planInfo = planList
    else:
        if timeoutBool:
            print("timeout")
        else:
            print("no plan found with max depth " + str(maxDepth))
        planInfo = False
    return planInfo, depth, userTime, timeoutBool

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
    parser.add_argument('-dp', '--depth', type=int, default=None,
                        help='the depth you want to run the solver at, only matters if using manual')
    parser.add_argument('-m', '--manual', action='store_true', default=False,
                        help='if set will run solver only once either at the given depth, or at max theoretical depth '
                             'of problem')
    parser.add_argument('-v', '--verbose', action='store_true', default=False,
                        help='makes the command line output verbose')
    parser.add_argument('-c', '--concise', action='store_true', default=False,
                        help='makes the command line output verbose')
    parser.add_argument('-pt', '--problemTimeout', type=int, default=False,
                        help='gives a timeout for running each PDDL problem')
    parser.add_argument('-dt', '--depthTimeout', type=int, default=300,
                        help='set the timeout for running at each depth of problem(s), default: 300, set to 0 to disable')
    parser.add_argument('-ga', '--geometricAllocation', action='store_true', default=False,
                        help='activates geometric allocation, based off maxDepth and problemTimeout')
    args = parser.parse_args()
    cf = args.cFile
    md = args.maxDepth
    d = args.depth
    sd = args.startingDepth
    ds = args.depthStep
    m = args.manual
    c = args.concise
    v = args.verbose
    pt = args.problemTimeout
    dt = args.depthTimeout

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
    r = solve(cf, md, d, sd, ds, m, oan, nan, otn, c, v, pt, dt)
    loc = cf.rsplit("/", 1)
    rootFolder = loc[0]
    logOutFolder = rootFolder
    Path(logOutFolder).mkdir(parents=True, exist_ok=True)
    name = str(loc[1]).split(".c")[0]
    if r[3]:
        valid = False
    else:
        valid = None
    log = writeLogs(name, logOutFolder, r, valid, stateSize, pt, dt)
    print(log)