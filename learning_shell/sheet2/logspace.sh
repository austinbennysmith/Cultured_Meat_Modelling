#!/bin/sh
echo -n "What is s?"
read s
echo -n "What is e?"
read e
echo -n "Length of list?"
read howmany
howmany=$(echo "$howmany-1" | bc -l)

if [ $s == $e ];
then 
	echo $s >> parameters.dat;

elif [ $howmany == 0 ]
then
	echo $s $e >> parameters.dat;

elif [ $s != $e ];
then
	start=$(echo "l($s)/l(10)" | bc -l)
	end=$(echo "l($e)/l(10)" | bc -l)
	step=$(echo "($end-$start)/$howmany" | bc -l)
	#echo $start
	#echo $end
	#echo $step
	echo $(seq $start $step $end)

	#Below is a less accurate way to get the exponent that I am not using:
	#for i in $(seq $start $step $end); do 
	#	echo "e($i*l(10))" | bc -l
	#done

	for i in $(seq $start $step $end); do
		myvar=$(awk -v t=$i 'BEGIN { a=t; a = 10 ^ a; print a}');
		echo $myvar >> parameters.dat
	done


	#powerlist=seq $s $step $e
	#echo $powerlist

	#step=$(echo "($e-$s)/$howmany" | bc -l )
	#echo `seq $s $step $e` > parameters.dat
fi
