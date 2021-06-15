#!/bin/bash

mkdir circle_Re_tests
cd circle_Re_tests

for i in -5 -4 -3 -2 -1

do
	mkdir Re_$i
	cp ~/Documents/Cultured_Meat_Modelling/embedded/around_circle.c Re_$i
	cp ~/Documents/Cultured_Meat_Modelling/embedded/Makefile Re_$i
	cd Re_$i
	sed -i "11 s/0.1/1e$i/" around_circle.c
	cd ..
done