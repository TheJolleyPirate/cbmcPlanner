import os
import subprocess
import timeit


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
        if verbose:
            print(results)
        goalChecker = results.split("Violated property:")
        if "GOAL CHECKER: FAIL MEANS PLAN FOUND" in goalChecker[-1]:
            toProcess = goalChecker[-2]
    except subprocess.TimeoutExpired:
        timeoutBool = True
        time = timeout
    return toProcess, time, timeoutBool


def solve(cFile, maxDepth, depth, startDepth, depthStep, manual, oldActionNames, newActionNames, objectToNum, concise, verbose):
    toProcess = False
    timeout = 300
    cbmcPath = os.path.abspath("externalTools/ubuntu-22-cbmc-6.1.1/cbmc")
    cmdList = [cbmcPath, cFile, "--compact-trace", "--unwind", ""]
    timeoutBool = False
    userTime = None
    time = 0
    if not manual:
        depth = startDepth - depthStep
        while depth <= maxDepth:
            depth += depthStep
            results = individualSolver(cFile, cmdList, depth, timeout, concise, verbose, time)
            time = results[1]
            if bool(results[0]) or bool(results[2]):
                toProcess = results[0]
                userTime = time
                timeoutBool = results[2]
                break
    else:
        results = individualSolver(cFile, cmdList, depth, timeout, concise, verbose, False)
        toProcess = results[0]
        userTime = results[1]
        timeoutBool = results[2]
    if bool(toProcess) and not timeoutBool:
        lines = toProcess.splitlines()
        planList = list()
        for line in lines:
            for i in range(len(oldActionNames)):
                actionWithBracket = newActionNames[i] + "("
                if actionWithBracket in line:
                    temp = line + "\n"
                    temp = temp.split(" ", 2)[2]
                    temp = temp[:-1]
                    temp = temp.split("(")[1]
                    temp = temp[:-1]
                    variableNums = temp.split(", ")
                    action = oldActionNames[i]
                    for varNum in variableNums:
                        var = objectToNum[int(varNum)]
                        action += " " + var
                    planList.append(action)
                    break
        print("\nfound plan: " + str(planList))
        planInfo = planList
    else:
        if timeoutBool:
            print("\ntimeout")
        else:
            print("\nno plan found")

        planInfo = False
    return planInfo, depth, userTime, timeoutBool