let rec geninterval = fun a b ->
    if a = b then 
        [a]
    else 
        a :: geninterval (a + 1) b
;;

List.iter (Printf.printf "%d ") (geninterval 1 10);