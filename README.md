# Program description
translates PDDL files into C programs which can be solved using CBMC<br/>

examples usage:
<pre>
python cbmcPlan.py
</pre>
<pre>
python cbmcPlan.py -d "your domain" -p "your problem"
</pre>
<pre>
python cbmcPlan.py -f "your input folder"
</pre>
## Installation
Unfortunatly this program will only run on linux.<br/>
you need to have python3 or later installed.<br/>
then simply run the program as:
<pre>
python3 cbmcPlanner/cbmcPlan.py [args]
</pre>
## Usage
<pre>
usage: cbmcPlan.py [-h] [-d DOMAIN] [-p PROBLEM] [-sd STARTINGDEPTH] [-ds DEPTHSTEP] [-md MAXDEPTH] [-m MANUALDEPTH] [-pt PROBLEMTIMEOUT] [-dt DEPTHTIMEOUT] [-ga GEOMETRICALLOCATION] [-s STATESIZE] [-v] [-c] [-l]
                   [-si] [-li] [-so] [-n NUMRUNS]
                   folder

Converts PDDL files into a C program and solves it using CBMC

positional arguments:
  folder                Folder containing files for batch processing

options:
  -h, --help            show this help message and exit
  -d DOMAIN, --domain DOMAIN
                        Specifies the domain PDDL file, if required
  -p PROBLEM, --problem PROBLEM
                        Specifies the problem PDDL file, if required
  -sd STARTINGDEPTH, --startingDepth STARTINGDEPTH
                        Initial depth of the solver, default is 1
  -ds DEPTHSTEP, --depthStep DEPTHSTEP
                        Depth increment between solving attempts, default is 1
  -md MAXDEPTH, --maxDepth MAXDEPTH
                        Maximum depth the solver is allowed to reach
  -m MANUALDEPTH, --manualDepth MANUALDEPTH
                        Run the solver once at the specified depth
  -pt PROBLEMTIMEOUT, --problemTimeout PROBLEMTIMEOUT
                        Set timeout in seconds for each PDDL problem
  -dt DEPTHTIMEOUT, --depthTimeout DEPTHTIMEOUT
                        Set timeout in seconds for each depth level, default is 300 seconds; set to 0 to disable
  -ga GEOMETRICALLOCATION, --geometricAllocation GEOMETRICALLOCATION
                        Manage geometric allocation; value <= 1 disables it. Specify the common factor for the geometric series. E.g., 2 means the max depth will get half the total time, 3 means two-thirds.
                        Conversely, 1.5 means one-third of the time, and 1.25 means one-fourth. Overrides depth timeout.
  -s STATESIZE, --stateSize STATESIZE
                        State size as a percentage: e.g., 0.2 means 20 percent of the maximum possible size
  -v, --verbose         Enable verbose output on the command line
  -c, --concise         Enable concise output on the command line
  -l, --load            Continue execution from where it was interrupted
  -si, --saveInit       save the current settings to init file
  -li, --loadInit       load settings from init file
  -so, --stopOnInvalid  Stops the program execution on the first invalid problem, instead of continuing
  -n NUMRUNS, --numRuns NUMRUNS
                        number of times to run each problem
</pre>
## External tools Licenses
### Fast Downward
GNU General Public License<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Version 3, 29 June 2007
### CBMC
(C) 2001-2016, Daniel Kroening, Edmund Clarke,
Computer Science Department, University of Oxford
Computer Science Department, Carnegie Mellon University

All rights reserved. Redistribution and use in source and binary forms, with
or without modification, are permitted provided that the following
conditions are met:

  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

  3. All advertising materials mentioning features or use of this software
     must display the following acknowledgement:

     This product includes software developed by Daniel Kroening,
     Edmund Clarke,
     Computer Science Department, University of Oxford
     Computer Science Department, Carnegie Mellon University

  4. Neither the name of the University nor the names of its contributors
     may be used to endorse or promote products derived from this software
     without specific prior written permission.

   
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
### VAL
Copyright 2019 - University of Strathclyde, King's College London and Schlumberger Ltd

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.