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

Printf.printf "my_not(T) = %b\n" (my_not true);;
Printf.printf "my_not(F) = %b\n" (my_not false);;
(* my_not(T) = false *)
(* my_not(F) = true *)

Printf.printf "my_and(T, T) = %b\n" (my_and true true);;
Printf.printf "my_and(T, F) = %b\n" (my_and true false);;
Printf.printf "my_and(F, T) = %b\n" (my_and false true);;
Printf.printf "my_and(F, F) = %b\n" (my_and false false);;
(* my_and(T, T) = true  *)
(* my_and(T, F) = false *)
(* my_and(F, T) = false *)
(* my_and(F, F) = false *)

Printf.printf "my_or(T, T) = %b\n" (my_or true true);;
Printf.printf "my_or(T, F) = %b\n" (my_or true false);;
Printf.printf "my_or(F, T) = %b\n" (my_or false true);;
Printf.printf "my_or(F, F) = %b\n" (my_or false false);;
(* my_or(T, T) = true  *)
(* my_or(T, F) = true  *)
(* my_or(F, T) = true  *)
(* my_or(F, F) = false *)
