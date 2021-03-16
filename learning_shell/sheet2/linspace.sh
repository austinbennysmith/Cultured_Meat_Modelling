#!/bin/sh
echo -n "What is s?"
read s
echo -n "What is e?"
read e
echo -n "How many between?"
read howmany
howmany=$(($howmany-1))
step=$(echo "($e-$s)/$howmany" | bc -l )
#for i in `seq $s $step $e`; do 
#	echo $i >> parameters.dat
#done
echo `seq $s $step $e` > parameters.dat