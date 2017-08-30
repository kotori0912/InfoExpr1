#!/bin/sh

ruby tag.rb > tag.txt

gcc Keiro.c
./a.out < tag.txt > ans.txt
