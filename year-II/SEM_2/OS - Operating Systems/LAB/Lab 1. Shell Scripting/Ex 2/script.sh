bash 
#!/bin/bash
if [[ $# -ne 3 ]]; then
    echo "Please pass 3 arguments"
    exit
fi

if [[ $2 = "+" || $2 = "-" || $2 = "/" || $2 = "*" || $2 = "%" ]]; then
    var = expr $1 $2 $3
else 
    echo "Please use a correct operator"
fi
