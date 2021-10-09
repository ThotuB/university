(defun count_atoms (lst)
    (if (null lst) 
        0
        (+ 
            (if (atom (car lst)) 
                1
                0
            )
            (count_atoms (cdr lst))
        )
    )
)

(print
    (count_atoms '(1 2 'three 4 5 6 'seven 8 'nine 10))
)