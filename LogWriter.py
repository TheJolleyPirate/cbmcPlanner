from pathlib import Path

def writeLogs(problem, logOutFolder, results, valid, problemStateSize, realStateSize, pTimeout, dTimeout, maximumDepth):
    plan = results[0]
    depth = results[1]
    finalTime = results[2]
    timeoutBool = results[3]
    history = results[4]
    if bool(plan):
        temp = ""
        counter = 0
        for action in plan:
            temp += str(counter) + ": (" + action + ") "
            counter += 1
        plan = temp
    logs = ""
    problemDetails = "problem details:\n"
    problemDetails += "\tstate size: " + str(realStateSize) + "\n"
    if bool(pTimeout):
        problemDetails += "\tproblem timeout: " + str(pTimeout) + "\n"
    if bool(dTimeout):
        problemDetails += "\tdepth timeout: " + str(dTimeout) + "\n"
    if bool(maximumDepth):
        problemDetails += "\tmaximum depth: " + str(maximumDepth) + "\n"
    if valid is None:
        logs += problem + " validaty unkown (not yet checked)\n"
        logs += problemDetails
        logs += "with:\n"
        logs += "\tplan: " + str(plan) + "\n"
    elif valid:
        logs += problem + " SOLVED!\n"
        logs += problemDetails
        logs += "with:\n"
        logs += "\tplan: " + str(plan) + "\n"
    else:
        logs += problem + " FAILED\n"
        logs += "\treason failed: "
        if timeoutBool:
            logs += "timeout\n"
        elif depth >= maximumDepth:
            logs += "depth out\n"
        elif not bool(plan):
            logs += "no plan found\n"
        else:
            logs += "invalid plan\n"
        logs += problemDetails
        logs += "with\n"
        if not timeoutBool and bool(plan):
            logs += "\tplan: " + str(plan) + "\n"
        elif timeoutBool and not bool(plan):
            logs += "\tno plan found\n"
    logs += "\tdepth: " + str(depth) + "\n"
    if finalTime is not None:
        time = "{:0.2f}".format(finalTime)
        logs += "\ttime: " + time + " seconds\n"
    if history is not None:
        logs += "history:\n"
        for i in range(len(history)):
            current = history[i]
            runTime = "{:0.2f}".format(current[0])
            runDepth = current[1]
            logs += "\t" + str(i) + ": depth " + str(runDepth) + " in " + runTime + " seconds\n"

    stateSizePercentage = "{:.0%}".format(problemStateSize)
    logOutFolder += "/state" + str(stateSizePercentage)
    if maximumDepth:
        logOutFolder += "-md" + str(maximumDepth)
    if pTimeout:
        logOutFolder += "-pT" + str(pTimeout)
    if dTimeout:
        logOutFolder += "-dT" + str(dTimeout)
    if valid:
        logOutFolder += "/valid"
    else:
        if timeoutBool:
            logOutFolder += "/invalid/timeout"
        elif not bool(plan):
            logOutFolder += "/invalid/noPlanFound"
        else:
            logOutFolder += "/invalid/invalidPlan"
    Path(logOutFolder).mkdir(parents=True, exist_ok=True)
    fileName = logOutFolder + "/" + problem + "-state" + str(realStateSize) + ".log"
    logFile = open(fileName, "w")
    logFile.write(logs)
    logFile.close()
    return logs