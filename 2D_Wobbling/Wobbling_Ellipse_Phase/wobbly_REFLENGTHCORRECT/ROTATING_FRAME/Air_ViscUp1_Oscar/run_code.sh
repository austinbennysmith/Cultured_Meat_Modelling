#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 168:00:00
cd L9
make with_stations_air.tst
cd ..
cd L10
make with_stations_air.tst
cd ..
cd L11
make with_stations_air.tst