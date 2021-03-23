#!/bin/sh
echo {1..10} >> 3b1.dat
for i in {1..10}; do
	printf "$i " >> 3b2.dat
done
