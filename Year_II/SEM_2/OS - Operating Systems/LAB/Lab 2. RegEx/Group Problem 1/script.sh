#!/bin/bash

while read line; do
    WC=`echo $line | egrep "^[A-Z]" | egrep "^[^\.]*\.$" | egrep "^[A-Za-z0-9, ]*\.$" | egrep -v ",[ ]+si " | wc -c`
    echo $WC
done 