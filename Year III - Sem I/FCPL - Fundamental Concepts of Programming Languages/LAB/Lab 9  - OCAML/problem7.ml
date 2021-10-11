let my_not = fun cond ->
    if cond then
        false
    else 
        true
;;

let my_and = fun cond1 cond2 ->
    if cond1 then 
        cond2
    else
        false
;;

let my_or = fun cond1 cond2 ->
    if cond1 then 
        true
    else 
        cond2
;;

Printf.printf "my_not(true) = %b\n" (my_not true);;
Printf.printf "my_not(false) = %b\n" (my_not false);;

Printf.printf "my_and(true, true) = %b\n" (my_and true true);;
Printf.printf "my_and(true, false) = %b\n" (my_and true false);;
Printf.printf "my_and(false, true) = %b\n" (my_and false true);;
Printf.printf "my_and(false, false) = %b\n" (my_and false false);;

Printf.printf "my_or(true, true) = %b\n" (my_or true true);;
Printf.printf "my_or(true, false) = %b\n" (my_or true false);;
Printf.printf "my_or(false, true) = %b\n" (my_or false true);;
Printf.printf "my_or(false, false) = %b\n" (my_or false false);;
