(defun my_reverse (lst)
    (cond 
        ((null lst) 
            nil
        )
        (t 
            (append (my_reverse (cdr lst)) (list (car lst)))
        )
    )
)

(print (my_reverse nil))
; nil

(print (my_reverse '(1 2 3 4 5)))
; (5 4 3 2 1)

(print (my_reverse '(1 2 (3 4) 5)))
; (5 (3 4) 2 1)