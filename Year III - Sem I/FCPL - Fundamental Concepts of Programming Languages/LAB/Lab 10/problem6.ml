let rec apply func init list = match list with
    | [] -> init
    | head::tail -> func head (apply func init tail)
;;

let sum x y = x + y;;
let mult x y = x * y;;

Printf.printf "%d\n" (apply sum 0 [1; 2; 3; 4; 5]);
(* int = 15 *)

Printf.printf "%d\n" (apply mult 1 [1; 2; 3; 4; 5]);
(* int = 120 *)

Printf.printf "%d\n" (apply sum 5 []);
(* int = 5 *)

