#!/bin/bash
numarray=({1..20})
letarray=({a..z})

for i in {1..20}; do
	echo $i ${letarray[$i]} $(shuf -i 2-100 -n 1) >> columns.dat;
done
echo ${myarray[*]:2:7}
