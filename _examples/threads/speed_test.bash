#!/bin/bash



for N in {1..50}
do

    python3 ./speed_test.py &

done
wait