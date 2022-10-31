#!/bin/bash

if [[ $# -lt 2 ]]; then
    echo "Usage: $0 file_name nr1 [nr2, ...]"
    exit
fi

file_name=$1

shift

suma=0
counter=0

#suma
for arg in "$@"
do
    if [[ $(( arg % 2 )) -eq 0 ]]; then
        (( counter++ ))
    fi

    suma=$(( suma + arg ))

done

echo $suma
echo $counter
echo ${#suma}

if [ -f $file_name ] && [ -h $file_name -eq 1 ] ; then
    echo $suma > $file_name | echo ${#suma} >> $file_name
else
    echo "Please give a good file name"
    exit
fi