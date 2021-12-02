(defun cond_abs (x)
    (cond 
        ((> x 0) x)
        (t (- x))
    )
)

(defun cond_min (a b)
    (cond 
        ((> a b) b)
        (t a)
    )
)

(defun cond_max (a b)
    (cond 
        ((> a b) a)
        (t b)
    )
)


(print 
    (cond_abs -1)
)

(print 
    (cond_abs 2)
)

(print
    (cond_min 1 2)
)

(print
    (cond_max 1 2)
)