let rec digits = fun num ->
    if num = 0 then 
        []
    else 
        digits (num / 10) @ [(num mod 10)]
;;

digits 54281;;
(* int list = [5; 4; 2; 8; 1] *)

digits 1001;;
(* int list = [1; 0; 0; 1] *)

digits 1234567890123456789;; (* 19 digits *)
(* int list = [1; 2; 3; 4; 5; 6; 7; 8; 9; 0; 1; 2; 3; 4; 5; 6; 7; 8; 9] *)

digits 12345678901234567890;; (* 20 digits *)
(* Error *)