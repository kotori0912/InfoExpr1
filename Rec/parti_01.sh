#!/bin/sh

gcc enumParti_EX1.c

echo "total, time, recnum" >> parti_01.csv

for i in `seq 12`; do
  for j in `seq $i`;  do
      ./a.out $1 $i $j >> parti_01.csv
  done    
  echo "finish" >> parti_01.csv
done
