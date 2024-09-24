import collections
import os
import re
import sys
from pathlib import Path

def getLogFileName(logOutFolder, problemStateSize, maximumDepth, pTimeout, dTimeout, gAllocation, problem, plan = False, timeoutBool = False, valid = "indet"):
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

    # Determine the validity path for logging
    if valid == "indet":
        fileNames = list()
        problem = str(problem).lower()
        fileNames.append(f"{logOutFolder}/{problem}.log")
        fileNames.append(f"{logOutFolder}/valid/{problem}.log")
        fileNames.append(f"{logOutFolder}/invalid/timeout/{problem}.log")
        fileNames.append(f"{logOutFolder}/invalid/noPlanFound/{problem}.log")
        fileNames.append(f"{logOutFolder}/invalid/invalidPlan/{problem}.log")
        return fileNames
    else:
        if valid is None:
            logOutFolder += ""
        elif valid:
            logOutFolder += "/valid"
        else:
            if timeoutBool:
                logOutFolder += "/invalid/timeout"
            elif not plan:
                logOutFolder += "/invalid/noPlanFound"
            else:
                logOutFolder += "/invalid/invalidPlan"
        # Create the output directory if it doesn't exist
        Path(logOutFolder).mkdir(parents=True, exist_ok=True)
        # Create the log file name
        fileName = f"{logOutFolder}/{problem}.log"
        return fileName

def writeLogs(problem, logOutFolder, results, valid, problemStateSize, realStateSize, pTimeout, dTimeout, maximumDepth, gAllocation):
    """
    Writes logs for the problem-solving results to a specified output folder.
    """
    plan = results[0]
    depth = results[1]
    finalTime = results[2]
    timeoutBool = results[3]
    history = results[4]

    # Format the plan for logging
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

    # Append timeout and depth information if applicable
    if pTimeout:
        problemDetails += f"\tproblem timeout: {pTimeout}\n"
    if dTimeout:
        problemDetails += f"\tdepth timeout: {dTimeout}\n"
    if maximumDepth:
        problemDetails += f"\tmaximum depth: {maximumDepth}\n"
    if gAllocation > 1:
        problemDetails += f"\tgeometric series common factor: {gAllocation}\n"

    # Log the problem outcome based on validity
    if valid is None:
        fileLogs += f"{problem} validity unknown (not yet checked)\n"
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
        elif not plan:
            fileLogs += "no plan found\n"
        else:
            fileLogs += "invalid plan\n"
        
        fileLogs += problemDetails
        fileLogs += "with\n"

        if not timeoutBool and plan:
            fileLogs += f"\tplan: {plan}\n"
        elif timeoutBool and not plan:
            fileLogs += "\tno plan found\n"

    # Log depth and execution time
    fileLogs += f"\tdepth: {depth}\n"
    formattedTime = f"{finalTime:.2f}"
    if finalTime is not None:
        fileLogs += f"\ttime: {formattedTime} seconds\n"
    else:
        fileLogs += "\ttime: n/a\n"

    # Log history of execution times
    if history is not None:
        fileLogs += "history:\n"
        for i in range(len(history)):
            current = history[i]
            runTime = "{:0.2f}".format(current[0])
            runDepth = current[1]
            fileLogs += f"\t{i}: depth {runDepth} in {runTime} seconds\n"

    # Prepare output folder based on problem state size and other parameters
    fileName = getLogFileName(logOutFolder, problemStateSize, maximumDepth, pTimeout, dTimeout, gAllocation, problem, plan, timeoutBool, valid)

    # Write the logs to the file
    with open(fileName, "w") as logFile:
        logFile.write(fileLogs)

    # Prepare print logs for console output
    if plan:
        printLogs = f"Plan found for {problem} with depth {depth} and time {formattedTime} seconds\nPlan: {plan}"
    else:
        printLogs = f"No plan found for {problem} with depth {depth} and time {formattedTime} seconds"

    return fileLogs, printLogs

def sorted_nicely(l):
    """ Sort the given iterable in a human-friendly way. """
    """function by Mark Byers
    sourced from https://stackoverflow.com/questions/2669059/how-to-sort-alpha-numeric-set-in-python"""
    """ Sort the given iterable in the way that humans expect."""
    convert = lambda text: int(text) if text.isdigit() else text
    alphanum_key = lambda key: [convert(c) for c in re.split('([0-9]+)', key)]
    return sorted(l, key=alphanum_key)


def combineByProblem(root):
    files = list()
    for p, s, f in os.walk(root):
        for file in f:
            toAdd = os.path.join(p, file)
            if "output/logs/combined" not in toAdd:
                files.append(toAdd)
    problemFiles = dict()
    for file in files:
        name = file.rsplit("/", 1)[1]
        if name in problemFiles:
            problemFiles[name].append(file)
        else:
            problemFiles[name] = [file]


    for n in problemFiles:
        currentFileList = problemFiles[n]
        currentFileList = sorted_nicely(currentFileList)
        combinedString = ""
        depths = dict()
        states = list()
        for currentFile in currentFileList:
            combinedString += f"{currentFile}\n"
            parts = str(currentFile).split("/")
            val = ""
            state = ""
            for i in range(len(parts)):
                if "logs" == parts[i -1] and "state" in parts[i]:
                    state = parts[i]
                elif "invalid" in parts[i]:
                    val = "F"
                elif "valid" in parts[i]:
                    val = "S"
            state = state.strip("state").split("-")[0]
            state = f"{state}{val}"
            states.append(state)
            with open(currentFile, "r") as logfile:
                currentLog = logfile.read()
                combinedString += currentLog

            splitLogs = currentLog.split("history")
            endDepth = splitLogs[0]
            endDepthLines = endDepth.splitlines()
            history = splitLogs[1]
            historyLines = history.splitlines()
            depth = ""
            time = ""
            for line in endDepthLines:
                if "depth: " in line:
                    depth = line.split("depth: ")[1].strip()
                if "time: " in line:
                    time = line.split("time: ")[1]
                    time = time.split(" ")[0]
            if depth in depths:
                depths[depth][state] = time
            else:
                depths[depth] = dict()
                depths[depth][state] = time
            for line in historyLines:
                if "depth " in line:
                    temp = line.split("depth ")[1]
                    temp = temp.split(" ")
                    depth = temp[0].strip()
                    time = temp[2]
                    if depth in depths:
                        depths[depth][state] = time
                    else:
                        depths[depth] = dict()
                        depths[depth][state] = time

        combinedFolder = f"{root}/combined"
        Path(combinedFolder).mkdir(parents=True, exist_ok=True)
        fileName = f"{combinedFolder}/{n}"
        with open(fileName, "w") as final:
            final.write(combinedString)

        usedStates = set()
        depthLen = 0
        oldKeys = list()
        for depth in depths:
            for s in depths[depth]:
                usedStates.add(s)
            if len(depth) > depthLen:
                depthLen = len(depth)
            oldKeys.append(depth)
        for key in oldKeys:
            newKey = key.zfill(depthLen)
            depths[newKey] = depths.pop(key)

        usedStates = sorted_nicely(usedStates)
        usedStates.reverse()
        depths = collections.OrderedDict(sorted(depths.items()))

        tableString = "depth"
        for state in usedStates:
            tableString += f"\t|{state}"
        tableString += "\n"

        for depth in depths:
            currentDepths = depths[depth]
            tableString += depth
            for state in usedStates:
                if state in currentDepths:
                    currentTime = currentDepths[state]
                    roundedTime = float('%.5g' % float(currentTime))
                    tableString += f"\t|{roundedTime}"
                else:
                    tableString += f"\t|-"
            tableString += "\n"
        tableString = tableString[:-1]
        tableFolder = f"{combinedFolder}/tables"
        Path(tableFolder).mkdir(parents=True, exist_ok=True)
        fileName = f"{tableFolder}/{n}"
        with open(fileName, "w") as final:
            final.write(tableString)

if __name__ == "__main__":
    inputFolder = sys.argv[1]
    combineByProblem(inputFolder)