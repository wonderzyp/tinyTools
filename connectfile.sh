#!/bin/bash

# write by Yeping.ZHENG
# 2022.12.08 

if [ -z $1 ]; then
  echo "usage: ./connectfile.sh  <MPI_NodeNum - 1>"
  exit 1
fi  

# divide outputfile into 7 parts
for (( k=7; k>=1; --k ))
do
  for (( i=$1; i>=1; i--))
  do
    j=`expr $[$i-1]`
    cat $k\_$i.txt >> $k\_$j.txt

    rm $k\_$i.txt
  done
done

for (( i=7; i>=2; --i ))
do
  j=`expr $[$i-1]`
  cat $i\_0.txt >> $j\_0.txt

  rm $i\_0.txt
done

