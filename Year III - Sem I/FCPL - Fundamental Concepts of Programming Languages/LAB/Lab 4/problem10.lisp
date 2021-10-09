(defun squash (lst)
    (let (
        (head (car lst))
        (tail (cdr lst))
    )
        (cond
            ((null lst)
                nil
            )
            ((atom head)
                (append (list head) (squash tail))
            )
            (t
                (squash tail)
            )
        )
    )
)

(print
    (squash '(1 'two 3 4 'five 6))
)