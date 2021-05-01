#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 24:00:00
rm -rf agupta4 agupta4.tst
make agupta4.tst
