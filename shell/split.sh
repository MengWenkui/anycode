#!/bin/bash

if [ $# != 2 ]
then 
    echo "$0 filename parts"
    exit
fi

for ((i = 1;  i <= $2; i++))
do
    awk 'NR % "'$2'" == "'$i'" {print $0}' $1 > $1_part_$i 
done


