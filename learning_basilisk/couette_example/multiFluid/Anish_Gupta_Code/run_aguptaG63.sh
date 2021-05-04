#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 24:00:00
rm -rf aguptaG63 aguptaG63.tst
make aguptaG63.tst
