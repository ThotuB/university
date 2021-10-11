let rec digits = fun num ->
    if num = 0 then 
        []
    else 
        digits (num / 10) @ [(num mod 10)]
;;

List.iter (Printf.printf "%d ") (digits 54281)