#!/bin/sh

echo "$1SORT" >> Q01.csv

x=0
y=0

for var in {1..11}
  do 
      gcc W09_01.c 
      ./a.out $1 $y >> Q01.csv
      x=`expr "$x" + 1`
      y=`echo "scale=3; $x / 10.0" | bc`
  done
 
 
