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
            ((listp head)
                (append (squash head) (squash tail))
            )
            (t
                (squash tail)
            )
        )
    )
)

(print (squash '(1 nil (two 3) 4 (5 (6 7) 8) 9 nil)))
; (1 nil two 3 4 5 6 7 8 9 nil)