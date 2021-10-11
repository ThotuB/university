let rotate_left list = match list with
    | head::tail -> tail @ [head]
    | [] -> []
;;

let rotate_right = fun list ->
    List.rev (rotate_left (List.rev list))
;;

Printf.printf "rotate_left: ";;
List.iter (Printf.printf "%d ") (rotate_left [1; 2; 3; 4; 5]);;
Printf.printf "\nrotate_right: ";;
List.iter (Printf.printf "%d ") (rotate_right [1; 2; 3; 4; 5]);;