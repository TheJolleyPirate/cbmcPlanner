import os
import subprocess

def validate(planList, domain, problem, verbose=False):
    """
    Validates a given plan against a specified domain and problem.
    """
    # Construct the plan string from the list of actions
    plan = ""
    actionNum = 0
    firstAction = True

    for action in planList:
        if firstAction:
            firstAction = False
        else:
            # Add a newline for subsequent actions
            plan += "\n"
        plan += f"{actionNum}: ({action})"
        actionNum += 1

    # Write the plan to a temporary file
    with open("temp.txt", "w") as planFile:
        planFile.write(plan)

    # Get absolute paths for the domain, problem, plan files and validator
    domainFile = os.path.abspath(domain)
    problemFile = os.path.abspath(problem)
    planFile = os.path.abspath("temp.txt")
    valPath = os.path.abspath("externalTools/val/Validate")

    # Prepare the command for the validation tool
    cmdList = [valPath, domainFile, problemFile, planFile]

    # Run the validation command
    cmd = subprocess.run(cmdList, capture_output=True, text=True)
    results = cmd.stdout

    # Clean up the temporary plan file
    os.remove("temp.txt")

    # Print results if verbose mode is enabled
    if verbose:
        print(results)

    # Check if the validation was successful
    if "Plan valid" in results:
        return True
    else:
        test = results.strip()
        if test == "":
            err = cmd.stderr
            raise subprocess.SubprocessError(err)
        return False
