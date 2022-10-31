#!/bin/bash
if test $# -eq 0
then 
	echo Usage: $0 dir1 dir2 ...
	exit
fi

test_d="./Test"

if test -d $test_d
then
	echo "Test directory already exists"
else
	echo "Creating Test directory"
	mkdir $test_d
fi
cd $test_d
d_count=0
for dir
do 
	d_count=`expr $d_count + 1`
	echo Dir: $d_count

	if test -d $dir
	then
		for e in $dir/*
		do
			if test -n $e
			then
				rm $e
			fi
		done
	else
		mkdir $dir
	fi
	
	cd $dir
	for i in {1..100}
	do
		file_name=`echo f$i`
		touch $file_name
		f=`expr $d_count \* 5`
		r=`expr $i % $f`
		if test $r -eq 0
		then
			link_name=`echo l$i`
			ln -s $file_name $link_name
		fi
	done
	cd ..
done
