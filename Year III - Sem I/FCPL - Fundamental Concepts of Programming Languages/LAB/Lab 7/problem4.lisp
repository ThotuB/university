(defun pretty_print (lst)
    (cond
        ((atom lst)
            (terpri)
            (princ lst)
        )
        (t
            (terpri)
            (princ '|(| )
            (princ (car lst))
            (mapcar
                'pretty_print
                (cdr lst)
            )
            (princ '|)| )
        )
    )
)

(pretty_print '(1 (2 3 (4) 5) 6 7) )