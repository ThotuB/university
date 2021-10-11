let rec ack = fun x y ->
    if x = 0 then 
        (y + 1)
    else if y > 0 then
        ack (x - 1) (ack x (y - 1))
    else 
        ack (x - 1) 1
;;

Printf.printf "%d\n" (ack 3 2)