#!/bin/bash

cd circle_Re_tests

for i in -5 -4 -3 -2 -1

do
	mv Re_$i Re_$((i+5))
done
