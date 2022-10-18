(defun cond_not (u)
    (cond
        ((null u) t)
        (t nil)
    )
)

(defun cond_or (x y z)
    (cond
        ((not (null x)) x)
        ((not (null y)) y)
        ((not (null z)) z)
        (t z)
    )
)

(defun cond_and (x y z)
    (cond
        ((null x) nil)
        ((null y) nil)
        ((null z) nil)
        (t z)
    )
)

(print 
    (cond_not 2)
)

(print 
    (cond_not nil)
)


(print
    (cond_or 1 2 3)
)

(print
    (cond_or nil 2 3)
)

(print
    (cond_or nil nil nil)
)


(print
    (cond_and 1 2 3)
)

(print
    (cond_and nil 2 3)
)