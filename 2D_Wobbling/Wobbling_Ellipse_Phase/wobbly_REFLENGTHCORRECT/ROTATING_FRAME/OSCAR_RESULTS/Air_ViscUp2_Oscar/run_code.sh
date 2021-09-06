#!/bin/bash
#SBATCH -n 96
#SBATCH --mem=64G
#SBATCH -t 96:00:00
cd L9
make with_stations_air.tst
cd ..
cd L10
make with_stations_air.tst
cd ..
cd L11
make with_stations_air.tst
