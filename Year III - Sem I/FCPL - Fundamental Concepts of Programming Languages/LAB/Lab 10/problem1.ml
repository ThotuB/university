let my_and conds = match conds with
    | (true, x) -> x
    | _ -> false
;;

let my_or conds = match conds with
    | (false, x) -> x
    | _ -> true
;;

Printf.printf "and(T, T): %b\n" (my_and (true, true));;
Printf.printf "and(T, F): %b\n" (my_and (true, false));;
Printf.printf "and(F, T): %b\n" (my_and (false, true));;
Printf.printf "and(F, F): %b\n" (my_and (false, false));;
(* and(T, T) = true *)
(* and(T, F) = false *)
(* and(F, T) = false *)
(* and(F, F) = false *)

Printf.printf "or(T, T): %b\n" (my_or (true, true));;
Printf.printf "or(T, F): %b\n" (my_or (true, false));;
Printf.printf "or(F, T): %b\n" (my_or (false, true));;
Printf.printf "or(F, F): %b\n" (my_or (false, false));;
(* or(T, T) = true *)
(* or(T, F) = true *)
(* or(F, T) = true *)
(* or(F, F) = false *)