#!/bin/bash

if [[ $# -lt 4 ]]; then
    echo "USAGE: $0 -i <input_file> -0 <output_file>"
    exit
fi

input=$2
output=$4

regex="^[A-Za-z][A-Za-z0-9-]*@[A-Za-z][A-Za-z0-9]*\.(com|ro|eu);([1-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])(\.([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])){2}\.([1-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-4])\n$"

> $output

# while read -r line; do
#     #echo $line | cat -v
#     line=${line%$'\n'}
#     if [[ $line =~ $regex ]]; then
#         echo "OK" >> $output
#     else
#         echo "ERROR" >> $output
#     fi
# done < $input

for i in ${!arr[@]};
do
    log=${arr[$i]}
    echo $log

    if [[ $log =~ $regex ]]; then
        echo "OK" >> $output
    else
        echo "ERROR" >> $output
    fi
done