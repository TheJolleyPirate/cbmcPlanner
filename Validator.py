import os
import subprocess


def validate(planList, domain, problem, verbose):
    plan = ""
    actionNum = 0
    first = True
    for action in planList:
        if first:
            first = False
        else:
            plan += "\n"
        plan += str(actionNum) + ": (" + action + ")"
        actionNum += 1
    planFile = open("temp.txt", "w")
    planFile.write(plan)
    planFile.close()
    domainFile = os.path.abspath(domain)
    problemFile = os.path.abspath(problem)
    planFile = os.path.abspath("temp.txt")
    valPath = os.path.abspath("externalTools/val/Validate")
    cmdList = [valPath, domainFile, problemFile, planFile]
    cmd = subprocess.run(cmdList, capture_output=True, text=True)
    results = cmd.stdout
    os.remove("temp.txt")
    if verbose:
        print(results)
    if "Plan valid" in results:
        return True
    else:
        test = results.strip()
        if test == "":
            err = cmd.stderr
            raise subprocess.SubprocessError(err)
        return False