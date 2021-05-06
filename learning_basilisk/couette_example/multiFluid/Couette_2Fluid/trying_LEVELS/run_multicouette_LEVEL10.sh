#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 24:00:00
rm -rf multicouette_LEVEL10 multicouette_LEVEL10.tst
make multicouette_LEVEL10.tst
