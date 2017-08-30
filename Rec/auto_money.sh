#!/bin/sh

gcc enum_coin.c

x=0
y=0

for i in `seq 5`; do
  echo $x >> coin.csv
  for j in `seq 5`; do
    y=`expr $y + 10`
    ./a.out $x $y >> coin.csv
  done 
  x=`expr $x + 50`
  y=0
done

