#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 24:00:00
rm -rf multicouette_LEVEL8 multicouette_LEVEL8.tst
make multicouette_LEVEL8.tst
