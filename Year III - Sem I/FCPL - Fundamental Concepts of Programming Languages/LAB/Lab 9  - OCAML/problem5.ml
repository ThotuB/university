let rec ack = fun x y ->
    if x = 0 then 
        (y + 1)
    else if y = 0 then
        ack (x - 1) 1
    else 
        ack (x - 1) (ack x (y - 1))
;;

Printf.printf "%d\n" (ack 2 1);;
(* 5 *)

Printf.printf "%d\n" (ack 1 2);;
(* 4 *)

Printf.printf "%d\n" (ack 3 2);;
(* 29 *)

Printf.printf "%d\n" (ack 3 3);;
(* 61 *)