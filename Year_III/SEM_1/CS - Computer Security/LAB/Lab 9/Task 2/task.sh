#!/bin/bash
./printenv -c > out_c.txt
./printenv -p > out_p.txt

diff out_c.txt out_p.txt