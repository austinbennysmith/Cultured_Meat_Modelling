#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 24:00:00
rm -rf multicouette_Le-2 multicouette_Le-2.tst
make multicouette_Le-2.tst
