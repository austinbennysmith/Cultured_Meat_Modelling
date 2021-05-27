#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 24:00:00
rm -rf aguptaG62 aguptaG62.tst
make aguptaG62.tst
