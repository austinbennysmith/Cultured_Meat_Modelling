#!/bin/bash

mkdir Re_tests
cd Re_tests

for i in 0 1 2 3 4

do
	mkdir Re_$i
	cp ~/Documents/Cultured_Meat_Modelling/embedded/around_circle.c Re_$i
	cp ~/Documents/Cultured_Meat_Modelling/embedded/Makefile Re_$i
	cd Re_$i
	sed -i "13 s/0.01/1e$i/" around_circle.c
	cd ..
done