#!/bin/bash
OUTPUT_NOENV=`./env`
OUTPUT_ENV=`./env -e`
diff <(echo "$OUTPUT_NOENV") <(echo "$OUTPUT_ENV")