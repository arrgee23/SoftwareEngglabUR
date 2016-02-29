#!/bin/sh
compile="gcc q3.c -lpthread -o vowel"
eval $compile

size=100000000
for thread in 1 2 3 4
do
	run="./vowel $thread"
	eval $run &
	PID=$!
	wait $PID
done

delete="rm vowel"
eval $delete
