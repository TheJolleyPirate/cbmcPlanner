import collections
import os
import re
import statistics
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

def writeLogs(problem, logOutFolder, results, valid, problemStateSize, realStateSize, pTimeout, dTimeout, maximumDepth, gAllocation, overwrite = False):
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
    if finalTime is not None:
        formattedTime = f"{finalTime:.2f}"
        fileLogs += f"\ttime: {formattedTime} seconds\n"
    else:
        fileLogs += "\ttime: n/a\n"
        formattedTime = "n/a"

    # Log history of execution times
    if history is not None:
        fileLogs += "history:\n"
        addLast = True
        nextIndex = 1
        for i in range(len(history)):
            current = history[i]
            runTime = "{:0.2f}".format(current[0])
            runDepth = current[1]
            if runDepth == depth:
                addLast = False
            fileLogs += f"\t{i + 1}: depth {runDepth} in {runTime} seconds\n"
            nextIndex = i + 2
        if addLast:
            fileLogs += f"\t{nextIndex}: depth {depth} in {formattedTime} seconds\n"

    # Prepare output folder based on problem state size and other parameters
    fileName = getLogFileName(logOutFolder, problemStateSize, maximumDepth, pTimeout, dTimeout, gAllocation, problem, plan, timeoutBool, valid)
    if overwrite:
        with open(fileName, "w") as logFile:
            logFile.write(fileLogs)
    else:
        if os.path.isfile(fileName):
            fileLogs = f"breakbreakbreak\n{fileLogs}"
        # Write the logs to the file
        with open(fileName, "a") as logFile:
            logFile.write(fileLogs)

    # Prepare print logs for console output
    if plan:
        printLogs = f"Plan found for {problem} with depth {depth} and time {formattedTime} seconds\nPlan: {plan}"
    else:
        printLogs = f"No plan found for {problem} with depth {depth} and time {formattedTime} seconds"

    return fileLogs, printLogs, fileName

def sorted_nicely(l):
    """ Sort the given iterable in a human-friendly way. """
    """function by Mark Byers
    sourced from https://stackoverflow.com/questions/2669059/how-to-sort-alpha-numeric-set-in-python"""
    """ Sort the given iterable in the way that humans expect."""
    convert = lambda text: int(text) if text.isdigit() else text
    alphanum_key = lambda key: [convert(c) for c in re.split('([0-9]+)', key)]
    return sorted(l, key=alphanum_key)

def corrolate(root):
    files = list()
    for p, s, f in os.walk(root):
        for file in f:
            toAdd = os.path.join(p, file)
            if "output/logs/constructed" not in toAdd:
                files.append(toAdd)

    averageFiles = list()
    constructedFolder = f"{root}/constructed"
    Path(constructedFolder).mkdir(parents=True, exist_ok=True)
    for file in files:
        if not file.endswith(".log"):
            continue
        with open(file, 'r') as multiLog:
            runs = multiLog.read()
        runs = runs.split("breakbreakbreak")
        pathPart = file.split("/")
        percentageStateSize = 0
        for i in range(len(pathPart)):
            if "state" in pathPart[i] and ("valid" in pathPart[i+1] or "invalid" in pathPart[i+1]):
                percentageStateSize = pathPart[i].split("state")[1]
                percentageStateSize = percentageStateSize.split("%")[0]
                percentageStateSize = int(percentageStateSize) / 100
                break
        stateSize = False
        maxDepth = False
        planBool = False
        depth = False
        problemName = False
        valid = False
        pTimeout = False
        dTimeout = False
        timeoutBool = False
        gAllocation = 0
        endTimes = list()
        planList = list()
        historyDict = dict()
        for run in runs:
            run = run.split("history:")
            if len(run) < 2:
                continue
            preamble = run[0].splitlines()
            history = run[1].splitlines()
            finalTime = False
            for line in preamble:
                if "state size: " in line and not stateSize:
                    stateSize = int(line.split("state size: ")[1])
                if "maximum depth: " in line and not maxDepth:
                    maxDepth = int(line.split("maximum depth: ")[1])
                if "plan: " in line and not planBool:
                    planBool = True
                    plan = line.split("plan: ")[1]
                    actions = plan.split("(")[1:]
                    for act in actions:
                        action = act.split(")")[0]
                        planList.append(action)
                if "depth: " in line and "maximum depth: " not in line and not depth:
                    depth = int(line.split("depth: ")[1])
                if "SOLVED!" in line and not problemName:
                    problemName = line.split(" SOLVED!")[0]
                    valid = True
                if "FAILED" in line and not problemName:
                    problemName = line.split(" FAILED")[0]
                    valid = False
                if "validity unknown (not yet checked)" in line and not problemName:
                    problemName = line.split(" validity")[0]
                    valid = None
                if "problem timeout: " in line and not pTimeout:
                    pTimeout = int(line.split("problem timeout: ")[1])
                if "depth timeout: " in line and not dTimeout:
                    dTimeout = int(line.split("depth timeout: ")[1])
                if "reason failed: timeout" in line:
                    timeoutBool = True
                if "geometric series common factor: " in line and not gAllocation:
                    gAllocation = float(line.split("geometric series common factor: ")[1])
                if "time: " in line:
                    finalTime = line.split("time: ")[1]
                    finalTime = float(finalTime.split(" ")[0])
            if finalTime:
                endTimes.append(finalTime)
            finalDepthAdded = False
            for line in history:
                if "depth " in line:
                    temp = line.split("depth ")[1]
                    parts = temp.split(" ")
                    currentDepth = int(parts[0])
                    currentTime = float(parts[2])
                    if currentDepth == depth:
                        finalDepthAdded = True
                    if currentDepth in historyDict:
                        historyDict[currentDepth].append(currentTime)
                    else:
                        historyDict[currentDepth] = list()
                        historyDict[currentDepth].append(currentTime)
            if not finalDepthAdded:
                if depth in historyDict:
                    historyDict[depth].append(finalTime)
                else:
                    historyDict[depth] = list()
                    historyDict[depth].append(finalTime)

        logFolder = f"{constructedFolder}/averaged"
        Path(logFolder).mkdir(parents=True, exist_ok=True)
        averageEndTime = statistics.fmean(endTimes)
        averageHistory = list()
        for d in historyDict:
            currentTime = statistics.fmean(historyDict[d])
            averageHistory.append([currentTime, d])
        averageHistory = averageHistory[:-1]
        details = [planList, depth, averageEndTime, timeoutBool, averageHistory]

        results = writeLogs(problemName, logFolder, details, valid, percentageStateSize, stateSize, pTimeout, dTimeout, maxDepth, gAllocation, overwrite=True)
        fileName = results[2]
        averageFiles.append(fileName)

    problemFiles = dict()
    for file in averageFiles:
        if not file.endswith(".log"):
            continue
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
                if ("logs" == parts[i-1] or "averaged" == parts[i-1]) and "state" in parts[i]:
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
            history = splitLogs[1]
            historyLines = history.splitlines()
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
        combinedFolder = f"{constructedFolder}/combined"
        Path(combinedFolder).mkdir(parents=True, exist_ok=True)
        fileName = f"{combinedFolder}/{n}"
        with open(fileName, "w") as final:
            final.write(combinedString)

        usedStates = set()
        depthLen = 0
        oldKeys = list()
        for current in depths:
            for s in depths[current]:
                usedStates.add(s)
            if len(current) > depthLen:
                depthLen = len(current)
            oldKeys.append(current)
        for key in oldKeys:
            newKey = key.zfill(depthLen)
            depths[newKey] = depths.pop(key)

        usedStates = sorted_nicely(usedStates)
        usedStates.reverse()
        depths = collections.OrderedDict(sorted(depths.items()))

        mdTableString = "|depth"
        csvTableString = "depth"
        for state in usedStates:
            mdTableString += f"\t|{state}"
            csvTableString += f",{state}"
        mdTableString += "\t|\n"
        csvTableString += "\n"

        for depth in depths:
            currentDepths = depths[depth]
            mdTableString += f"|{depth}"
            csvTableString += f"{depth}"
            for state in usedStates:
                if state in currentDepths:
                    currentTime = currentDepths[state]
                    roundedTime = float('%.5g' % float(currentTime))
                    mdTableString += f"\t|{roundedTime}"
                    csvTableString += f",{roundedTime}"
                else:
                    mdTableString += f"\t|-"
                    csvTableString += f","
            mdTableString += "\t|\n"
            csvTableString += "\n"
        mdTableString = mdTableString[:-1]
        csvTableString = csvTableString[:-1]
        mdTableFolder = f"{constructedFolder}/tables/md"
        csvTableFolder = f"{constructedFolder}/tables/csv"
        Path(mdTableFolder).mkdir(parents=True, exist_ok=True)
        Path(csvTableFolder).mkdir(parents=True, exist_ok=True)
        mdFile = f"{mdTableFolder}/{n}"
        with open(mdFile, "w") as md:
            md.write(mdTableString)
        csvExtension = n.rsplit(".", 1)[0] + ".csv"
        csvFile = f"{csvTableFolder}/{csvExtension}"
        with open(csvFile, "w") as csv:
            csv.write(csvTableString)

if __name__ == "__main__":
    try:
        argFolder = sys.argv[1]
    except IndexError:
        argFolder = "output/logs"
    if not os.path.isdir(argFolder):
        raise ValueError("provided argument is not a vaild directory")
    corrolate(argFolder)