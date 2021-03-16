#!/bin/sh
echo -n "Please input a number."
read n
for i in {1..10}; do
	val = $((i * n))
	echo "$val GetRidOfMe $((val+1))" >> 3c.dat
done
