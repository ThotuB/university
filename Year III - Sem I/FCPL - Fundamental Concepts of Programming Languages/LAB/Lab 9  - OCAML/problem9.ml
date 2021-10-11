let rec maximum = fun list ->
    if List.length list = 1 then
        List.hd list
    else
        (max (List.hd list) (maximum (List.tl list)))
;;

Printf.printf "Maximum: %d\n" (maximum [1; 2; 3; 4; 5; 2; 3; 1])