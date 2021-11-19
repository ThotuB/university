let rotate_left list = match list with
    | head::tail -> tail @ [head]
    | [] -> []
;;

let rotate_right = fun list ->
    List.rev (rotate_left (List.rev list))
;;

rotate_left [1; 2; 3; 4; 5];;
(* int list = [2; 3; 4; 5; 1] *)

rotate_right [1; 2; 3; 4; 5];;
(* int list = [4; 5; 1; 2; 3] *)