(defun fibonacci (num)
    (cond
        ((= num 0) 0)
        ((= num 1) 1)
        (t (+ (fibonacci (- num 1)) (fibonacci (- num 2))))
    )
)

(print
    (fibonacci 23)
)