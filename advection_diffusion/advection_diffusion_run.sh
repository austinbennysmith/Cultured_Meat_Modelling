#!/bin/bash

cd 1D_dt_dx_Tests

for i in -2 -3 -4 -5

do
	cd dt_$i
	make advection_ALONE.tst
	cd ..
done