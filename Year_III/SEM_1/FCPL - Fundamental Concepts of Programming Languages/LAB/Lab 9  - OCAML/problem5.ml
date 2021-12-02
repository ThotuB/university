let rec ack = fun x y ->
    if x = 0 then 
        (y + 1)
    else if y = 0 then
        ack (x - 1) 1
    else 
        ack (x - 1) (ack x (y - 1))
;;

ack 2 1;;
(* int = 5 *)

ack 1 2;;
(* int = 4 *)

ack 3 2;;
(* int = 29 *)

ack 3 3;;
(* int = 61 *)

ack 3 6;;
(* int = 509 *)