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

let to_string num = match num with
    | {re; im} -> Printf.sprintf "%.2f + i * %.2f" re im
;;

let num1 = {re = 1.2; im = 2.3};;
let num2 = {re = 3.5; im = 4.25};;

Printf.printf "%s\n" (to_string (add num1 num2));;
Printf.printf "%s\n" (to_string (mult num1 num2));;