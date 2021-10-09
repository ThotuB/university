; TODO

(defun trim_tail (lst n)
    (defun trim_head (lst n)
        (cond 
            ((null lst) nil)
            ((zerop n) lst)
            (t (trim_head (cdr lst) (- n 1)))
        )
    )
    (reverse (trim_head (reverse lst) n))
)

(print
    (trim_tail '(1 2 3 4 5 6) 3)
)