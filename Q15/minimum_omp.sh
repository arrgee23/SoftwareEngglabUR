#!/bin/sh
compile="gcc -fopenmp minimum_omp.c -o minimum"
eval $compile

size=100000000
for thread in 1 2 4 8 16 32
do
	run="./minimum $thread $size"
	eval $run &
	PID=$!
	wait $PID
done

delete="rm minimum"
eval $delete
