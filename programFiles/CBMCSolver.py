import argparse
import multiprocessing
import os
import subprocess
import timeit
import math
from time import sleep
from programFiles.LogWriter import writeLogs

# Global variable to track if problem timeout has occurred
pTimeBool = False

def __individualSolver(cFile: str, cmdList, depth, timeout, concise, verbose, lastStepTime, gAllocation):
    """Solves an individual problem instance with the given depth and parameters.
    Returns the results of the solver execution."""
    fileName = os.path.basename(cFile)
    toProcess = False
    timeoutBool = False
    stateBool = False

    # Print the running status based on verbosity and conciseness
    if verbose:
        if not lastStepTime:
            print(f"\trunning {fileName} with depth {depth}")
        else:
            print(f"\trunning {fileName} with depth {depth}, previous depth time: {lastStepTime:.2f} seconds")
    elif not concise:
        if not lastStepTime:
            print(f"\r\trunning {fileName} with depth {depth}", end='')
        else:
            print(f"\r\trunning {fileName} with depth {depth}, previous depth time: {lastStepTime:.2f} seconds", end='')
    else:
        if not lastStepTime:
            print(f"\r\trunning problem with depth {depth}", end='')
        else:
            print(f"\r\trunning problem with depth {depth}, last depth time: {lastStepTime:.2f} secs", end='')

    # Update command list with current depth
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
        if err:
            raise subprocess.SubprocessError(err)

        # Check for violated properties in the results
        goalChecker = results.split("Violated property:")
        if "GOAL CHECKER: FAIL MEANS PLAN FOUND" in goalChecker[-1]:
            if len(goalChecker) > 1:
                toProcess = goalChecker[-2]
            else:
                stateBool = True

    except subprocess.TimeoutExpired:
        # Handle timeout scenario
        if gAllocation <= 1:
            timeoutBool = True
        time = timeout

    return toProcess, time, timeoutBool, stateBool

def __problemTimeout(pTimeout):
    """Sets a timeout for the problem execution."""
    sleep(pTimeout)
    global pTimeBool
    pTimeBool = True

def __currentTimeout(currentDepth, maxDepth, pTimeout, commonFactor):
    """Calculates the timeout for the current depth based on a geometric series."""
    geometricSeries = (commonFactor ** maxDepth) / (commonFactor - 1)
    timeout = pTimeout * (commonFactor ** (currentDepth - 1)) / geometricSeries
    return timeout

def __solveLoop(startDepth, maxDepth, depthStep, gAllocation, pTimeout, dtimeout, cFile, cmdList, concise, verbose):
    """Main loop to attempt solving the problem at increasing depths.
    Returns the results of the solving attempts."""
    depth = startDepth - depthStep
    relativeMaxDepth = math.ceil((maxDepth - startDepth + 1) / depthStep)
    relativeCurrentDepth = 1
    toProcess = False
    timeoutBool = False
    currentTime = 0
    history = list()
    d = dtimeout
    totalTime = 0
    while True:
        if maxDepth and depth >= maxDepth:
            break
        depth += depthStep

        # Update depth timeout based on geometric allocation if applicable
        if gAllocation > 1:
            d = __currentTimeout(relativeCurrentDepth, relativeMaxDepth, pTimeout, gAllocation)
            relativeCurrentDepth += 1

        # Solve the individual problem at the current depth
        results = __individualSolver(cFile, cmdList, depth, d, concise, verbose, currentTime, gAllocation)
        currentTime = results[1]
        totalTime += currentTime
        planFound = bool(results[0])
        stateBool = results[3]
        if gAllocation <= 1:
            timeoutBool = results[2]

        # Check for conditions to break the loop
        if planFound or timeoutBool or pTimeBool or stateBool:
            toProcess = results[0]
            timeoutBool = results[2]
            break

        history.append((currentTime, depth))

    return toProcess, currentTime, timeoutBool, depth, history, totalTime

def solve(cFile, maxDepth, manualDepth, startDepth, depthStep, oldActionNames, newActionNames, objectToNum, concise,
          verbose, pTimeout, dTimeout, gAllocation):
    """Main function to handle the solving process of the given problem file.
    Returns the plan information and other relevant results."""
    cbmcPath = os.path.abspath("./externalTools/ubuntu-22-cbmc-6.1.1/cbmc")
    cmdList = [cbmcPath, cFile, "--compact-trace", "--unwind", ""]

    if not manualDepth:
        global pTimeBool
        pTimeBool = False

        if pTimeout:
            # Start a separate process to handle problem timeout
            probTimer = multiprocessing.Process(target=__problemTimeout, args=[pTimeout])
            probTimer.start()

            # Execute the solving loop
            results = __solveLoop(startDepth, maxDepth, depthStep, gAllocation, pTimeout, dTimeout, cFile, cmdList,
                                  concise, verbose)

            probTimer.terminate()
            probTimer.join()

        else:
            # Execute the solving loop without timeout
            results = __solveLoop(startDepth, maxDepth, depthStep, gAllocation, pTimeout, dTimeout, cFile, cmdList,
                                  concise, verbose)

        # Extract results from the solving attempt
        toProcess = results[0]
        finalTime = results[1]
        timeoutBool = results[2]
        depth = results[3]
        history = results[4]
        totalTime = results[5]

    else:
        # Handle the case of manual depth solving
        depth = manualDepth
        results = __individualSolver(cFile, cmdList, depth, dTimeout, concise, verbose, False, 0)
        toProcess = results[0]
        finalTime = results[1]
        timeoutBool = results[2]
        history = None
        totalTime = results[5]

    # Process the result if a plan was found and no timeout occurred
    planInfo = False
    if toProcess and not timeoutBool:
        lines = toProcess.splitlines()
        planList = list()

        # Collect action names while ensuring unique matching
        for line in lines:
            matches = list()
            for i in range(len(oldActionNames)):
                actionWithBracket = newActionNames[i] + "("
                if actionWithBracket in line:
                    # Collect matching action names
                    matches.append(oldActionNames[i])

            if matches:
                # Find the longest matching action name
                action = max(matches, key=len)
                temp = line.split(" ", 2)[2]
                variableNums = temp.split("(")[1][:-1]
                variableNums = variableNums.split(", ")

                # Construct the action string with variable names
                for varNum in variableNums:
                    var = objectToNum[int(varNum)]
                    action += " " + var
                planList.append(action)
        planInfo = planList
    resultsString = ""
    if planInfo:
        if not concise:
            resultsString += f"\n\tfound plan: {planInfo}"
        else:
            resultsString += f", found plan"
    else:
        if timeoutBool:
            if not concise:
                resultsString += "\n\tfailed due to timeout"
            else:
                resultsString += ", failed; timeout"
        else:
            if not concise:
                resultsString += "\n\tfailed due to no plan found"
            else:
                resultsString += ", failed; no plan found"
    if not concise:
        resultsString += f"\n\tfinal time: {finalTime:.2f} seconds"
        resultsString += f"\n\toverall time: {totalTime:.2f} seconds"
    else:
        resultsString += f"\n\tfinal time: {finalTime:.2f} secs"
        resultsString += f", overall time: {totalTime:.2f} secs"
    print(resultsString)

    return planInfo, depth, finalTime, timeoutBool, history

if __name__ == "__main__":
    """lets the solver be run independently on preprocessed c programs"""
    # Set up command line argument parsing
    parser = argparse.ArgumentParser(description='solves a CBMC planning problem generated by CProgramWriter')
    parser.add_argument("cFile", type=str, help='the c file for CBMC to solve')
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
                        help='makes the command line output concise')
    parser.add_argument('-pt', '--problemTimeout', type=int, default=False,
                        help='gives a timeout for running each PDDL problem')
    parser.add_argument('-dt', '--depthTimeout', type=int, default=300,
                        help='set the timeout for running at each depth of problem(s), default: 300, set to 0 to '
                             'disable')
    parser.add_argument('-ga', '--geometricAllocation', type=float, default=0,
                        help='controls the geometric allocation; >=1 turns it off, otherwise sets common factor for '
                             'geometric series. E.g. 2 means the max depth will have 1/2 the total time and 3 means the'
                             ' max depth will have 2/3 the total time conversely 1.5 means the max depth will have 1/3 '
                             'of the total time and 1.25 means the max depth has 1/4 the total time. Overrides depth '
                             'timeout')

    # Parse arguments
    args = parser.parse_args()
    cf = args.cFile
    md = args.maxDepth
    sd = args.startingDepth
    ds = args.depthStep
    m = args.manualDepth
    c = args.concise
    v = args.verbose
    pt = args.problemTimeout
    dt = args.depthTimeout
    ga = args.geometricAllocation

    # Read the contents of the C file
    with open(cf, 'r') as file:
        contents = file.read()

    clines = contents.splitlines()
    otn = None
    stateSize = None
    breakCheck = [False, False]

    # Extract object names and state size from the C file
    for cline in clines:
        if "//objectNames = {" in cline:
            names = cline.strip("//objectNames = {")[:-2]
            otn = names.split(", ")
            breakCheck[0] = True
        if "int n = " in cline:
            stateSize = int(cline.strip("int n = ")[:-1])
            breakCheck[1] = True
        if breakCheck[0] and breakCheck[1]:
            break

    # Raise error if object names or state size not found
    if otn is None:
        raise ValueError("could not find variable names in c file")
    if stateSize is None:
        raise ValueError("could not find state size in c file")

    # Extract preamble information
    preamble = contents.split("//END OF PREAMBLE")[0]
    # Skip the first two lines (comments)
    clines = preamble.splitlines()[2:]
    oan = list()
    nan = list()

    # Collect action names from the preamble
    for cline in clines:
        actions = cline[2:].split("==")
        nan.append(actions[0])
        oan.append(actions[1])

    # Solve the problem using the extracted information
    r = solve(cf, md, m, sd, ds, oan, nan, otn, c, v, pt, dt, ga)

    # Prepare logging information
    loc = cf.rsplit("/", 1)
    rootFolder = loc[0]
    logOutFolder = rootFolder
    name = str(loc[1]).split(".c")[0]
    if r[3]:
        valid = False
    else:
        valid = None
    # TODO: get problem state size from c file
    # Write logs based on solving results
    logs = writeLogs(name, logOutFolder, r, valid, "unknown", stateSize, pt, dt, md, ga)

    # Print logs based on verbosity
    if v:
        print(logs[0])
    else:
        print(logs[1])