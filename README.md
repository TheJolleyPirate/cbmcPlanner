TODO  
  
python Runner.py -h  
usage: PDDLtoC [-h] [-d DOMAIN] [-p PROBLEM] [-sd STARTINGDEPTH] [-ds DEPTHSTEP] [-md MAXDEPTH] [-dp DEPTH] [-m] [-f FOLDER] [-v] [-c]  
translates PDDL into a c program which can be solved using CBMC  
  
options:  
  -h, --help            show this help message and exit  
  -d DOMAIN, --domain DOMAIN  
                        the domain PDDL file if needed  
  -p PROBLEM, --problem PROBLEM  
                        the problem PDDL file if needed  
  -sd STARTINGDEPTH, --startingDepth STARTINGDEPTH  
                        the starting depth of the solver, default 1  
  -ds DEPTHSTEP, --depthStep DEPTHSTEP  
                        the amount the depth changes between solve attempts, default 1  
  -md MAXDEPTH, --maxDepth MAXDEPTH  
                        the maximum depth of the solver, default max theoretical depth of problem  
  -dp DEPTH, --depth DEPTH  
                        the depth you want to run the solver at, only matters if using manual  
  -m, --manual          if set will run solver only once either at the given depth, or at max theoretical depth of problem  
  -f FOLDER, --folder FOLDER  
                        the folder containing the files to batch process  
  -v, --verbose         makes the command line output verbose  
  -c, --concise         makes the command line output verbose  
