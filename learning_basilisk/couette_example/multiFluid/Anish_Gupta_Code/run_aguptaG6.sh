#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 24:00:00
rm -rf aguptaG6 aguptaG6.tst
make aguptaG6.tst
