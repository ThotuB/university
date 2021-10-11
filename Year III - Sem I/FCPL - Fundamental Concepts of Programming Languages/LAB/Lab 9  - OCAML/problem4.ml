let rec fib = fun n ->
    if n <= 1 then 
        n
    else 
        fib (n - 1) + fib (n - 2)
;;

let n = 21;;
Printf.printf "fib %d: %d\n" n (fib n)