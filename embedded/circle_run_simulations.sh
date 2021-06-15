#!/bin/bash

cd circle_Re_tests

for i in -5 -4 -3 -2 -1

do
	cd Re_$i
	make around_circle.tst
	cd ..
done