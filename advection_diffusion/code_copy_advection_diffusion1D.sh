#!/bin/bash

mkdir 1D_dt_dx_Tests
cd 1D_dt_dx_Tests

for i in -2 -3 -4 -5

do
	mkdir dt_$i
	cp ~/Documents/Cultured_Meat_Modelling/advection_diffusion/advection_ALONE.c dt_$i
	cp ~/Documents/Cultured_Meat_Modelling/advection_diffusion/Makefile dt_$i
	cd dt_$i
	sed -i "11 s/1e-2/1e$i/" advection_ALONE.c
	sed -i "20 s/64e0/64e$((-2-i))/" advection_ALONE.c
	cd ..
done