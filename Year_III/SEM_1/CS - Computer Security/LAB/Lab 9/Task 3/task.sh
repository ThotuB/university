#!/bin/bash
gcc env.c -o env

./env > out_null.txt
./env -e > out_env.txt

diff out_null.txt out_env.txt