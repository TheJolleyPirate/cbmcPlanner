

def writeLogs(problem, logOutFolder, results, valid, stateSize):
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
    if valid:
        logs += problem + " solved!\n"
        logs += "\twith:\n"
        logs += "\t\tplan: " + str(plan) + "\n"
    else:
        logs += problem + " not solved\n"
        logs += "\treason failed: "
        if timeout:
            logs += "timeout\n"
        elif not bool(plan):
            logs += "no plan found\n"
        else:
            logs += "invalid plan\n"
        logs += "\twith\n"
        if not timeout and bool(plan):
            logs += "\t\tplan: " + str(plan) + "\n"
        elif timeout and not bool(plan):
            logs += "\t\tno plan found\n"
    logs += "\t\tdepth: " + str(depth) + "\n"
    if userTime is not None:
        time = "{:0.2f}".format(userTime)
        logs += "\t\ttime: " + time + " seconds\n"
    #log state size
    logs += "\t\tstate size: " + str(stateSize) + "\n"
    logFile = open(logOutFolder + "/" + problem + ".log", "w")
    logFile.write(logs)
    logFile.close()
    return logs