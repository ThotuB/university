let get_head list = match list with
    | head::_ -> head
    | [] -> raise (Failure "get_head: empty list")
;;

let get_tail list = match list with
    | _::tail -> tail
    | [] -> raise (Failure "get_tail: empty list")
;;

Printf.printf "get_head: %d\n" (get_head [1; 2; 3]);;
Printf.printf "get_tail: ";;
List.iter (Printf.printf "%d ") (get_tail [1; 2; 3]);;