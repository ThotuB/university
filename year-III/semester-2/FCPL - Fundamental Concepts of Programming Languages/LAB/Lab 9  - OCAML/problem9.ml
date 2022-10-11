let rec maximum1 = fun list ->
    if list = [] then
        Int.min_int
    else
        (max (List.hd list) (maximum1 (List.tl list)))
;;

let rec maximum2 = fun list ->
    if List.length list <= 1 then
        List.hd list
    else
        (max (List.hd list) (maximum2 (List.tl list)))
;;

maximum1 [1; 2; 3; 4; 5; 2; 3; 1];;
(* int = 5 *)

maximum1 [3];;
(* int = 3 *)

maximum1 [];;
(* int = Int.min_int (-4611686018427387904) *)


maximum2 [1; 2; 3; 4; 5; 2; 3; 1];;
(* int = 5 *)

maximum2 [3];;
(* int = 3 *)

maximum2 [];;
(* Exception: (Failure hd) *)