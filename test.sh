#!/bin/bash
echo "Running: Runner.py -f input/for-graphs -s 0.9 -md 10 -dt 0"
python3 Runner.py -f input/for-graphs -s 0.9 -md 10 -dt 0
echo "Running: Runner.py -f input/for-graphs -s 0.7 -md 10 -dt 0"
python3 Runner.py -f input/for-graphs -s 0.7 -md 10 -dt 0
echo "Running: Runner.py -f input/for-graphs -s 0.5 -md 10 -dt 0"
python3 Runner.py -f input/for-graphs -s 0.5 -md 10 -dt 0
echo "Running: Runner.py -f input/for-graphs -s 0.3 -md 10 -dt 0"
python3 Runner.py -f input/for-graphs -s 0.3 -md 10 -dt 0
