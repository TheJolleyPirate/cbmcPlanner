#!/bin/bash
: 'echo "Running: Runner.py -f input/for-graphs -md 20 -dt 0"
python3 Runner.py -f input/for-graphs -md 20 -dt 0
echo "Running: Runner.py -f input/for-graphs -s 0.8 -md 20 -dt 0"
python3 Runner.py -f input/for-graphs -s 0.8 -md 20 -dt 0
echo "Running: Runner.py -f input/for-graphs -s 0.6 -md 20 -dt 0"
python3 Runner.py -f input/for-graphs -s 0.6 -md 20 -dt 0
echo "Running: Runner.py -f input/for-graphs -s 0.4 -md 20 -dt 0"
python3 Runner.py -f input/for-graphs -s 0.4 -md 20 -dt 0
echo "Running: Runner.py -f input/for-graphs -s 0.2 -md 20 -dt 0"
python3 Runner.py -f  input/for-graphs -s 0.2 -md 20 -dt 0'

python3 Runner.py -f input/miconic -dt 0 md 20