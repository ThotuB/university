let rec geninterval = fun a b ->
    if a = b then 
        [a]
    else 
        a :: geninterval (a + 1) b
;;

geninterval 1 10;;
(* int list = [1; 2; 3; 4; 5; 6; 7; 8; 9; 10] *)

geninterval (-2) 2;;
(* int list = [-2; -1; 0; 1; 2] *)