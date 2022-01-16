#!/bin/bash
gcc env.c -o env

sudo chown root env
sudo chmod 4755 env

# export PATH=...
export LD_LIBRARY_PATH=/usr/local/lib
export MY_VAR=sleepy

env > out_env.txt
./env > out_cenv.txt

diff out_env.txt out_cenv.txt