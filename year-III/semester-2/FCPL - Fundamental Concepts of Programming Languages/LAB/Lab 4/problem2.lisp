(defun fibonacci (num)
    (defun fib (num)
        (cond
            ((= num 0) 0)
            ((= num 1) 1)
            (t (+ (fib (- num 1)) (fib (- num 2))))
        )
    )
    (if (= 0 num)
        nil
        (append (fibonacci (- num 1)) (list (fib num)))
    )
)

(print (fibonacci 11))
; (1 1 2 3 5 8 13 21 34 55 89)

(print (fibonacci 3))
; (1 1 2)

(print (fibonacci 21))
; (1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765 10946)