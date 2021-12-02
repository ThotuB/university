(defun factorial (num)
    (if (= 0 num)
        1
        (* num (factorial (- num 1)))
    )
)

(print
    (factorial 10)
)