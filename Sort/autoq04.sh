#!/bin/sh

echo "$1"

x=0
y=0

for var in {1..11}
do 
    gcc $1 
    ./a.out $y >> Q04.csv
    x=`expr "$x" + 1`
    y=`echo "scale=3; $x / 10.0" | bc`
done
 
 
