type complex = {re: float; im: float};;

let add = fun num1 num2 ->
    {
        re = num1.re +. num2.re; 
        im = num1.im +. num2.im
    }
;;

let mult = fun num1 num2 ->
    {
        re = num1.re *. num2.re -. num1.im *. num2.im;
        im = num1.re *. num2.im +. num1.im *. num2.re;
    }
;;

let num1 = {re = 1.2; im = 2.3};;
let num2 = {re = 3.5; im = 4.25};;

add num1 num2;;
(* complex = {re = 4.7; im = 6.55} *)

mult num1 num2;;
(* complex = {re = -5.575; im = 13.15} *)