#!/bin/sh

gcc enumParti_EX2.c

for i in `seq 50`; do
  for j in `seq $i`;  do
      ./a.out $1 $i $j >> parti_02.csv
  done    
  echo "finish" >> parti_02.csv
done