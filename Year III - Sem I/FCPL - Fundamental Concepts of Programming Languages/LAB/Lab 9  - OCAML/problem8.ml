let rec digits = fun num ->
    if num = 0 then 
        []
    else 
        digits (num / 10) @ [(num mod 10)]
;;

List.iter (Printf.printf "%d ") (digits 54281);;
(* int list = [5; 4; 2; 8; 1] *)

List.iter (Printf.printf "%d ") (digits 1001);;
(* int list = [1; 0; 0; 1] *)