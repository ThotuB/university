(defun trim_tail (lst n)
    (defun trim_head (lst n)
        (cond 
            ((null lst) nil)
            ((= 0 n) lst)
            (t (trim_head (cdr lst) (- n 1)))
        )
    )
    (reverse (trim_head (reverse lst) n))
)

(print
    (trim_tail '(1 2 3 4 5 6) 3)
)

(print
    (trim_tail '(1 2 3) 3)
)

(print
    (trim_tail '(1) 3)
)

(print
    (trim_tail nil 3)
)