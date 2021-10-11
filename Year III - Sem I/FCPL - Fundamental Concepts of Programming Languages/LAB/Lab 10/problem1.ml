let my_and conds = match conds with
    | (true, x) -> x
    | _ -> false
;;

let my_or conds = match conds with
    | (false, x) -> x
    | _ -> true
;;

Printf.printf "and(true, true): %b\n" (my_and (true, true));;
Printf.printf "and(true, false): %b\n" (my_and (true, false));;
Printf.printf "and(false, true): %b\n" (my_and (false, true));;
Printf.printf "and(false, false): %b\n" (my_and (false, false));;

Printf.printf "or(true, true): %b\n" (my_or (true, true));;
Printf.printf "or(true, false): %b\n" (my_or (true, false));;
Printf.printf "or(false, true): %b\n" (my_or (false, true));;
Printf.printf "or(false, false): %b\n" (my_or (false, false));;