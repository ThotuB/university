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

(print (my_reverse '(1 2 3 4 5)))
    