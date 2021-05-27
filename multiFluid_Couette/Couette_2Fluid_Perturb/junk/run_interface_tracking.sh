#!/bin/bash
#SBATCH -n 12
#SBATCH --mem=64G
#SBATCH -t 24:00:00
rm -rf interface_tracking interface_tracking.tst
make interface_tracking.tst
