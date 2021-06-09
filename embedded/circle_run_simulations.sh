#!/bin/bash

cd Re_tests

for i in 0 1 2 3 4

do
	cd Re_$i
	make around_circle.tst
	cd ..
done