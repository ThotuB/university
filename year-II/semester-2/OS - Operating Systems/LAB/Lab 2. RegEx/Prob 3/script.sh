#!/bin/bash

if [[ $# -lt 2 ]]; then
    echo "USAGE: $0 -i <input_file> -0 <output_file>"
    exit
fi

text="001122334455"

> $2

for i in {0..5}; do
    echo $text | sed 's/[0-9][0-9]/&:/' | cut -c -3 >> echo -n >> $2 
    text=$(echo $text | cut -c 3-)
done