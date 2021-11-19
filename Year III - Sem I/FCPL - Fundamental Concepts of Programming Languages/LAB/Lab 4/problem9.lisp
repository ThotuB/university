(defun is_present (elem lst)
    (let (
        (head (car lst))
        (tail (cdr lst))
    )
        (cond
            ((null lst)
                nil
            )
            ((listp head)
                (is_present elem head)
            )
            ((eql (car lst) elem) 
                t
            )
            (t 
                (is_present elem (cdr lst))
            )
        )
    )
)

(print (is_present 3 '(1 2 3 4 5)))
(print (is_present 3 '(1 2 (3 4) 5)))
(print (is_present 6 '(1 2 3 4 5)))