# Program description (in progress)
translates PDDL into a c program which can be solved using CBMC<br/>
examples usage:
* python Runner.py
* python Runner.py -d "your domain" -p "your problem"
* python Runner.py -f "your input folder"
## Options
* -h, --help<br/>
  * show this help message and exit<br/>
* -d DOMAIN, --domain DOMAIN<br/>
  * the domain PDDL file if needed<br/>
* -p PROBLEM, --problem PROBLEM<br/>
  * the problem PDDL file if needed<br/>
* -sd STARTINGDEPTH, --startingDepth STARTINGDEPTH<br/>
  * the starting depth of the solver, default 1<br/>
* -ds DEPTHSTEP, --depthStep DEPTHSTEP<br/>
  * the amount the depth changes between solve attempts, default 1<br/>
* -md MAXDEPTH, --maxDepth MAXDEPTH<br/>
  * the maximum depth of the solver, default max theoretical depth of problem<br/>
* -dp DEPTH, --depth DEPTH<br/>
  * the depth you want to run the solver at, only matters if using manual<br/>
* -m, --manual<br/>
  * if set will run solver only once either at the given depth, or at max theoretical depth of problem<br/>
* -f FOLDER, --folder FOLDER<br/>
  * the folder containing the files to batch process<br/>
* -v, --verbose<br/>
  * makes the command line output verbose<br/>
* -c, --concise<br/>
  * makes the command line output verbose<br/>
