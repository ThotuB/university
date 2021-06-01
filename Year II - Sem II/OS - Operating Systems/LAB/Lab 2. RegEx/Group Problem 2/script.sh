#!/bin/bash

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 <file_out> <directory>"
    exit
fi

cnt=0

for file_name in "$2"/*; do
    echo "$file_name"

    if test -h "$file_name"
    then
        echo "case link"
        (( cnt++ ))
    else 
        if test -f "$file_name"
        then
            echo "case file"
            isprop=`cat "$file_name" | egrep "^[A-Z]" | egrep "^[^\.]*\.$" | egrep "^[A-Za-z0-9, ]*\.$" | egrep -v ",[ ]+si " | wc -l`
            if [[ $isprop -ne 0 ]]; then
                echo "$file_name" $isprop >> $1
            fi
        else
            if test -d "$file_name"
            then
                echo "case dir"
                $0 $1 "$file_name"
                cnt=`expr $cnt + $?`
            fi
        fi
    fi
    
done

echo $cnt
exit $cnt

