#!/bin/bash

cd plate_Re_tests

for i in 0 1 2 3

do
	cd Re_$i
	make flat_plate.tst
	cd ..
done