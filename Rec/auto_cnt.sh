#!/bin/sh

gcc enum_parti.c

for i in `seq 9`; do
  for j in `seq $i`;  do
      ./a.out $i $j >> parti_01.txt
  done    
done
