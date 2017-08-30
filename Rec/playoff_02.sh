#!/bin/sh

gcc PlayOff_02.c

echo "total, time, recnum" >> poff_02.csv

for i in `seq 30`; do
  for j in `seq $i`;  do
      ./a.out $1 $i $j $2 >> poff_02.csv
  done    
done

echo "finish" >> poff_02.csv