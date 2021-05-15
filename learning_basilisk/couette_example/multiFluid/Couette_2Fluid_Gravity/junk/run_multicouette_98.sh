#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 24:00:00
rm -rf multicouette_98 multicouette_98.tst
make multicouette_98.tst
