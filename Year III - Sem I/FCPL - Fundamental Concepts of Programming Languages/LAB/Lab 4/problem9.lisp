(defun is_present (elem lst)
    (cond
        ((null lst)
            nil
        )
        ((equal (car lst) elem) 
            t
        )
        (t 
            (is_present elem (cdr lst))
        )
    )
)

(print (is_present 'c '(a b c d)))
(print (is_present 'e '(a b c d)))