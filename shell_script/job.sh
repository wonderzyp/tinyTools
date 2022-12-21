#!/bin/bash

#SBATCH -J test32
#SBATCH -p xahctest

#SBATCH -N 4
#SBATCH --ntasks-per-node=16
#SBATCH --cpus-per-task=4
#SBATCH -o %j-zrmpi.log
#SBATCH -e %j-zrmpi.log

echo ${SLURM_JOB_NODELIST}
echo start on $(date)

mpirun --output-filename ./output -np 64 ./zaran
#srun --mpi=pmix_v3  ./zaran

echo end on $(date)