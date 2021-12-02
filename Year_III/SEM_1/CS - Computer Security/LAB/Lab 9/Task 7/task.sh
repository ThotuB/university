#!/bin/bash

gcc -fPIC -g -c sleepy.c
gcc -shared -o libsleepy.so.1.0.1 sleepy.o -lc

export LD_PRELOAD=./libsleepy.so.1.0.1