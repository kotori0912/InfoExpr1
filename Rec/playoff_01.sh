#!/bin/sh

gcc PlayOff_01.c

echo "total, time" >> poff_01.csv

for i in `seq $2`; do
  ./a.out $1 $2 $i >> poff_01.csv
done

echo "finish" >> poff_01.csv
