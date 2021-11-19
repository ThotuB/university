let get_head list = match list with
    | head::_ -> head
    | [] -> raise (Failure "get_head: empty list")
;;

let get_tail list = match list with
    | _::tail -> tail
    | [] -> raise (Failure "get_tail: empty list")
;;

get_head [1; 2; 3];;
(* int = 1 *)

get_tail [1; 2; 3];;
(* int list = [2; 3] *)

get_head [];;
(* Exception: (Failure "get_head: empty list") *)

get_tail [];;
(* Exception: (Failure "get_tail: empty list") *)