(defun my_union (lst1 lst2)
    (let (
        (res lst2)
    )
        (do* (
            (lst lst1 (cdr lst))
            (head (car lst) (car lst))
        )(
            (null lst)
            res
        )
            (if (member head lst2)
                nil
                (setq res (cons head res))
            )
        )
    )
)

(defun my_intersection (lst1 lst2)
    (mapcan (lambda (elem) 
            (if (member elem lst2)
                (list elem)
                nil
            )
        )
        lst1
    )
)

(defun my_difference (lst1 lst2)
    (let (
        (res 
            (mapcan (lambda (elem) 
                (if (member elem lst2)
                    nil
                    (list elem)
                )
            )
            lst1
        ))
    )
        (setq res 
            (append res
                (mapcan (lambda (elem) 
                        (if (member elem lst1)
                            nil
                            (list elem)
                        )
                    )
                    lst2
                )
            )
        )
        res
    )
    
)

(defun my_equal (lst1 lst2)
    (if (= (length lst1) (length lst2))
        (do* (
            (lst lst1 (cdr lst))
            (head (car lst) (car lst))
            (res t)
        )(
            (or (null res) (null lst))
            res
        )
            (if (member head lst2)
                nil
                (setq res nil)
            )
        )
    )
)

; (print
;     (my_union '(1 2 3 4 5) '(4 5 6 7 8))
; )

; (print
;     (my_intersection '(1 2 3 4 5) '(4 5 6 7 8))
; )

; (print
;     (my_difference '(1 2 3 4 5) '(4 5 6 7 8))
; )

(print
    (my_equal '(1 2 3 4 5) '(1 2 3 4 5))
)

(print
    (my_equal '(1 2 3 4 5) '(4 5 6 7 8))
)