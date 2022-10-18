let rec reverse list = match list with
    | [] -> []
    | head::tail -> reverse tail @ [head]
;;

reverse [1; 2; 3; 4; 5];;
(* int list = [5; 4; 3; 2; 1] *)

reverse [1];;
(* int list = [1] *)

reverse [];;
(* int list = [] *)