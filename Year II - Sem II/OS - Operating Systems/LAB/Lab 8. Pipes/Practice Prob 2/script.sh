#!/bin/bash
avg=0
temp_total=0
number_of_args=$#

if [ $# -lt 1 ] ; then
   echo -e "USAGE: $0 number1 number2 ... numberN\n"
   exit 1
fi
  
for i in $*
do
   temp_total=`expr $temp_total + $i`

done

avg=`expr $temp_total / $number_of_args`
echo "Average of all number is $avg"
exit 2