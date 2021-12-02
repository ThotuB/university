#!/bin/bash
export LD_LIBRARY_PATH=/usr/local/lib
export MY_VAR=sleepy

OUT_SYSTEMCALL=`env`
OUT_CPROGRAM=`./env`

diff <(echo "$OUT_SYSTEMCALL") <(echo "$OUT_CPROGRAM")