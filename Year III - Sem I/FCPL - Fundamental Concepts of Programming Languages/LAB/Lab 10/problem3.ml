let rec reverse list = match list with
    | [] -> []
    | head::tail -> reverse tail @ [head]
;;

List.iter (Printf.printf "%d ") (reverse [1; 2; 3; 4; 5]);;