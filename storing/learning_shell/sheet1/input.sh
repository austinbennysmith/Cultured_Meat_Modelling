#!/bin/sh
echo -n "Please input a number."
read n
for i in {1..10}; do
	echo $((i*n))' GetRidOfMe '$((i*n+1)) >> 3c.dat
done
