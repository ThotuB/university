(declaim (sb-ext:muffle-conditions cl:warning))

(defun median1 (a b c)
    (if (> a b)
        (if (> b c)
            b
            (if (> a c)
                c
                a))
        (if (> b c)
            (if (> a c)
                a
                c)
            b
        )
    )
)

(defun median2 (a b c)
    (setq minimum (min a b c))
    (setq maximum (max a b c))
    (setq lst (list minimum maximum))
    
    (cond 
        ((not (member a lst)) a)
        ((not (member b lst)) b)
        (t c)
    )
)


(print
    (median2 1 2 3)
)
(print
    (median2 1 3 2)
)
(print
    (median2 2 1 3)
)
(print
    (median2 2 3 1)
)
(print
    (median2 3 1 2)
)
(print
    (median2 3 2 1)
)