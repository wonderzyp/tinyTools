#!/bin/bash


# write by Zheng Yeping, DUT, 2022-12-7

# clean the old output data and run mpi
# all output can be found in ./build/output/

# usage: put it in ./build, with zaran
# runmpi.sh <nodeNum>

if [ -d output ]; then
  yes | rm  ./output/*
  echo "clean old data success"
else
  mkdir output
fi

echo "try to invoke $1 nodes run mpi"
mpirun -outfile-pattern=./output/debug-%r -errfile-pattern=./output/err-%r -np $1 ./zaran

echo "all finished"
