let rec gcd = fun a b ->
    if a = b then
        a
    else if a < b then
        gcd a (b - a)
    else
        gcd (a - b) b
;;

let a = 32
and b = 52;;

Printf.printf "gcd(%d, %d): %d" a b (gcd a b);;