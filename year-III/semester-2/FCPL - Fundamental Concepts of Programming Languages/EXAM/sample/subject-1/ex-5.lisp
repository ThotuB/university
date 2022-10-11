;; ((A B A B A B) ((A B) (A B)) B A (A B) ((A B) (A B A B)))

(defvar L '(A B))
(defvar R (reverse L))

(print 
    (append
        (list (append L L L)
            (list L L)
        )
        R (list L) (list (list L) (list L L))
    )
)