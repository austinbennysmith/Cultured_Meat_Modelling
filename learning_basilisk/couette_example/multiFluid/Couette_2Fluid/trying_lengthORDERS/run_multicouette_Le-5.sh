#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 24:00:00
rm -rf multicouette_Le-5 multicouette_Le-5.tst
make multicouette_Le-5.tst
