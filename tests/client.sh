#!/bin/bash

for N in {1..50}
do
    ruby client.rb $(shuf -i 1-4 -n 1) &
done
wait