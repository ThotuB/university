; TODO

; (defun union (lst1 lst2)

; )

(defun my_intersection (lst1 lst2)
    (mapcan
        (lambda (elem) 
            (if (member elem lst2)
                (list elem)
                nil
            )
        )
        lst1
    )
)

(defun difference (lst1 lst2)
    (do (
            (x 0 (1+ x))
        )
        (
            ()
        )
    )
)

(defun equality (lst1 lst2)

)

(print
    (my_intersection '(1 2 3 4 5) '(4 5 6 7 8))
)