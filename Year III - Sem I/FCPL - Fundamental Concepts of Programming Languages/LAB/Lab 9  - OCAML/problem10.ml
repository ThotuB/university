let rec gcd = fun a b ->
    if a = b then
        a
    else if a < b then
        gcd a (b - a)
    else
        gcd (a - b) b
;;

gcd 36 48;;
(* int = 12 *)

gcd 103 4501;;
(* int = 1 *)

gcd 234 24;;
(* int = 6 *)