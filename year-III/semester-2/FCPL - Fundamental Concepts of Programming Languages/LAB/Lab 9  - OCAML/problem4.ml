let rec fib = fun n ->
    if n <= 1 then 
        n
    else 
        fib (n - 1) + fib (n - 2)
;;

let rec fib_seq = fun n ->
    if n <= 1 then 
        [n]
    else 
        fib_seq (n - 1) @ [fib n]
;;

fib 13;;
(* int = 10946 *)
fib 5;;
(* int = 5 *)

fib_seq 13;;
(* int list = [1; 1; 2; 3; 5; 8; 13; 21; 34; 55; 89; 144; 233] *)
fib_seq 5;;
(* int list = [1; 1; 2; 3; 5] *)
