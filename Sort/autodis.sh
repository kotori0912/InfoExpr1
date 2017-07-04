#/bin/sh

echo "$1SORT" >> Q02_comb.csv

x=0

for var in {2..10}
do
  x=`expr "$x" + 1`
  y=`echo "scale=3; ($x / 10.0) + 1" | bc`

  gcc W09_02.c
  ./a.out $1 $var $y $2 >> Q02_comb.csv 
done
