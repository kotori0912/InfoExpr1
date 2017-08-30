#!/bin/sh

gcc Leven.c

for i in `seq 10`; do
    ./a.out < $i.txt >> leven.csv
done
