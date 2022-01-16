#!/bin/bash
echo "ENVIRONTMENT VARIABLES:"
env

echo "PARTICULAR ENV VAR:"
env | grep "^PWD="
printenv PWD

export MY_VAR="I am tired"
printenv MY_VAR || echo "MY_VAR is not set"

unset MY_VAR
printenv MY_VAR || echo "MY_VAR is not set"