(defun is_present (elem lst)
    (let (
        (head (car lst))
        (tail (cdr lst))
    )
        (cond
            ((null lst)
                nil
            )
            ((eql (car lst) elem) 
                t
            )
            ((listp head)
                (is_present elem head)
            )
            (t 
                (is_present elem (cdr lst))
            )
        )
    )
)

(print (is_present nil '(1 2 3 4 5)))
; nil

(print (is_present nil '(1 2 () 3 4 5)))
; T

(print (is_present 3 '(1 2 3 4 5)))
; T

(print (is_present 3 '(1 2 (3 4) 5)))
; T

(print (is_present 6 '(1 2 3 4 5)))
; NIL