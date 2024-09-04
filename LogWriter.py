from pathlib import Path


def writeLogs(problem, logOutFolder, results, valid, stateSize, pTimeout, dTimeout):
    plan = results[0]
    depth = results[1]
    userTime = results[2]
    timeout = results[3]
    if bool(plan):
        temp = ""
        counter = 0
        for action in plan:
            temp += str(counter) + ": (" + action + ") "
            counter += 1
        plan = temp
    logs = ""
    problemDetails = "problem details:\n"
    problemDetails += "\tstate size: " + str(stateSize) + "\n"
    problemDetails += "\tproblem timeout: " + str(pTimeout) + "\n"
    problemDetails += "\tdepth timeout: " + str(dTimeout) + "\n"
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
        if timeout:
            logs += "timeout\n"
        elif not bool(plan):
            logs += "no plan found\n"
        else:
            logs += "invalid plan\n"
        logs += problemDetails
        logs += "with\n"
        if not timeout and bool(plan):
            logs += "\tplan: " + str(plan) + "\n"
        elif timeout and not bool(plan):
            logs += "\tno plan found\n"
    logs += "\tdepth: " + str(depth) + "\n"
    if userTime is not None:
        time = "{:0.2f}".format(userTime)
        logs += "\ttime: " + time + " seconds\n"
    if valid:
        logOutFolder += "/valid"
    else:
        if timeout:
            logOutFolder += "/invalid/timeout"
        elif not bool(plan):
            logOutFolder += "/invalid/noPlanFound"
        else:
            logOutFolder += "/invalid/invalidPlan"
    Path(logOutFolder).mkdir(parents=True, exist_ok=True)
    fileName = logOutFolder + "/" + problem + "-state" + str(stateSize)
    if pTimeout:
        fileName += "-pT" + str(pTimeout)
    if dTimeout:
        fileName += "-dT" + str(dTimeout)
    fileName += ".log"
    logFile = open(fileName, "w")
    logFile.write(logs)
    logFile.close()
    return logs