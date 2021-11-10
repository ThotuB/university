(defun my_union (lst1 lst2) 
    (append 
        (mapcan 
            (lambda (elem)
                (if (member elem lst2)
                    nil
                    (list elem)
                )
            )
            lst1
        )
        lst2
    )
)

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

(defun my_difference (lst1 lst2)
    (defun diff (lst1 lst2)
        (mapcan 
            (lambda (elem)
                (if (member elem lst1)
                    nil
                    (list elem)
                )
            )
            lst2
        )
    )

    (append 
        (diff lst2 lst1)
        (diff lst1 lst2)
    )
)

(defun my_equal (lst1 lst2)
    (let (
        (res t)
    )
        (mapcan (lambda (elem)
                (cond 
                    ((member elem lst1)
                        (setq res (and res t))
                    )
                    (t
                        (setq res nil)
                    )
                )
            )
            lst2
        )
        (mapcan (lambda (elem)
                (cond 
                    ((member elem lst2)
                        (setq res (and res t))
                    )
                    (t
                        (setq res nil)
                    )
                )
            )
            lst1
        )
        res
    )
)

(print
    (my_union '(1 2 3 4 5) '(4 5 6 7 8))
)

(print
    (my_intersection '(1 2 3 4 5) '(4 nil 5 6 7 8))
)

(print
    (my_intersection nil '(4 5 6))
)

(print
    (my_difference '(1 2 3 nil 4 5) '(4 nil 5 6 7 8))
)

(print
    (my_difference '(1 2 3) '(4 5 6))
)

(print
    (my_equal '(1 a b 3 4 5) '(1 a b 3 4 5))
)

(print
    (my_equal '(3 2 1) '(1 2 3))
)

(print
    (my_equal '(1 2 3 4 5) '(4 5 6 7 8))
)