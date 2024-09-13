from pathlib import Path

def writeLogs(problem, logOutFolder, results, valid, problemStateSize, realStateSize, pTimeout, dTimeout, maximumDepth, gAllocation):
    plan = results[0]
    depth = results[1]
    finalTime = results[2]
    timeoutBool = results[3]
    history = results[4]
    if bool(plan):
        temp = ""
        counter = 0
        for action in plan:
            temp += f"{counter}: ({action}) "
            counter += 1
        plan = temp
    fileLogs = ""
    problemDetails = "problem details:\n"
    problemDetails += f"\tstate size: {realStateSize}\n"
    if bool(pTimeout):
        problemDetails += f"\tproblem timeout: {pTimeout}\n"
    if bool(dTimeout):
        problemDetails += f"\tdepth timeout: {dTimeout}\n"
    if bool(maximumDepth):
        problemDetails += f"\tmaximum depth: {maximumDepth}\n"
    if gAllocation > 1:
        problemDetails += f"\tgeometric series common factor: {gAllocation}\n"
    if valid is None:
        fileLogs += f"{problem} validaty unknown (not yet checked)\n"

        fileLogs += problemDetails
        fileLogs += "with:\n"
        fileLogs += f"\tplan: {plan}\n"
    elif valid:
        fileLogs += f"{problem} SOLVED!\n"
        fileLogs += problemDetails
        fileLogs += "with:\n"
        fileLogs += f"\tplan: {plan}\n"
    else:
        fileLogs += f"{problem} FAILED\n"
        fileLogs += "\treason failed: "
        if timeoutBool:
            fileLogs += "timeout\n"
        elif depth >= maximumDepth:
            fileLogs += "depth out\n"
        elif not bool(plan):
            fileLogs += "no plan found\n"
        else:
            fileLogs += "invalid plan\n"
        fileLogs += problemDetails
        fileLogs += "with\n"
        if not timeoutBool and bool(plan):
            fileLogs += f"\tplan: {plan}\n"
        elif timeoutBool and not bool(plan):
            fileLogs += "\tno plan found\n"
    fileLogs += f"\tdepth: {depth}\n"
    if finalTime is not None:
        time = "{:0.2f}".format(finalTime)
        fileLogs += f"\ttime: {time} seconds\n"
    else:
        time = "n/a"
    if history is not None:
        fileLogs += "history:\n"
        for i in range(len(history)):
            current = history[i]
            runTime = "{:0.2f}".format(current[0])
            runDepth = current[1]
            fileLogs += f"\t{i}: depth {runDepth} in {runTime} seconds\n"
    stateSizePercentage = "{:.0%}".format(problemStateSize)
    logOutFolder += f"/state{stateSizePercentage}"
    if maximumDepth:
        logOutFolder += f"-md{maximumDepth}"
    if pTimeout:
        logOutFolder += f"-pt{pTimeout}"
    if dTimeout:
        logOutFolder += f"-dt{dTimeout}"
    if gAllocation > 1:
        logOutFolder += f"-ga{gAllocation}"
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
    fileName = f"{logOutFolder}/{problem}-state{realStateSize}.log"
    with open(fileName, "w") as logFile:
        logFile.write(fileLogs)

    if bool(plan):
        printLogs = f"plan found for {problem} with depth {depth} and time {time} seconds\nplan: {plan}"
    else:
        printLogs = f"no plan found for {problem} with depth {depth} and time {time} seconds"
    return fileLogs, printLogs