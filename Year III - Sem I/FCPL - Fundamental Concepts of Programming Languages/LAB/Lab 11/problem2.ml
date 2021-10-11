type expression = 
    | Value of float
    | Add of (expression * expression)
    | Sub of (expression * expression)
    | Mul of (expression * expression)
    | Div of (expression * expression)
    | Fn1 of ((float -> float) * expression)                        (* function (float) -> float *)
    | Fn2 of ((float -> float -> float) * expression * expression)  (* function (float, float) -> float *)
;;

let rec evaluate expr = match expr with
    | Value x -> x
    | Add (x, y) -> evaluate x +. evaluate y
    | Sub (x, y) -> evaluate x -. evaluate y
    | Mul (x, y) -> evaluate x *. evaluate y
    | Div (x, y) -> evaluate x /. evaluate y
    | Fn1 (f, x) -> f (evaluate x)
    | Fn2 (f, x, y) -> f (evaluate x) (evaluate y)
;;

(* 6/2 - 2^3 + cos(2*asin(1)) *)
let eq = 
Add(
    Sub(
        Div(
            Value(6.0), 
            Value(2.0)
        ), 
        Fn2(
            Float.pow, 
            Value(2.0), 
            Value(3.0)
        )
    ), 
    Fn1(
        Float.cos, 
        Mul(
            Value(2.0), 
            Fn1(
                Float.asin,  
                Value(1.0)
            )
        )
    )
);;

Printf.printf "Expression = %.2f\n" (evaluate eq);;