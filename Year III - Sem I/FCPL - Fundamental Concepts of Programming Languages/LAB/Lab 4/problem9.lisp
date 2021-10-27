(defun is_present (elem lst)
    (cond
        ((null lst)
            nil
        )
        ((eql (car lst) elem) 
            t
        )
        (t 
            (is_present elem (cdr lst))
        )
    )
)

(defun is_present_nested (elem lst)
    (let (
        (head (car lst))
        (tail (cdr lst))
    )
        (cond
            ((null lst)
                nil
            )
            ((listp head)
                (is_present_nested elem head)
            )
            ((eql (car lst) elem) 
                t
            )
            (t 
                (is_present_nested elem (cdr lst))
            )
        )
    )
)

(print (is_present 3 '(1 2 3 4 5)))
(print (is_present 3 '(1 2 (3 4) 5)))
(print (is_present 6 '(1 2 3 4 5)))

(print (is_present_nested 3 '(1 2 3 4 5)))
(print (is_present_nested 3 '(1 2 (3 4) 5)))
(print (is_present_nested 6 '(1 2 3 4 5)))