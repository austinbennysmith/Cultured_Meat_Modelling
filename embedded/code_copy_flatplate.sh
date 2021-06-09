#!/bin/bash

mkdir plate_Re_tests
cd plate_Re_tests

for i in 0 1 2 3

do
	mkdir Re_$i
	cp ~/Documents/Cultured_Meat_Modelling/embedded/flat_plate.c Re_$i
	cp ~/Documents/Cultured_Meat_Modelling/embedded/Makefile Re_$i
	cd Re_$i
	sed -i "13 s/0.01/1e$i/" flat_plate.c
	cd ..
done