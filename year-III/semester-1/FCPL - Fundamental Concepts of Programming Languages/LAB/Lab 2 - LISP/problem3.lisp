(print 
    (car '(P H W))
)

(print 
    (cdr '(B K H P))
)

(print 
    (car '((A B) (C D)))
)

(print 
    (cdr '((A B) (C D)))
)

(print 
    (car 
        (cdr '((A B) (C D)))
    )
)

(print 
    (cdr 
        (car '((A B) (C D)))
    )
)

(print 
    (cdr 
        (car 
            (cdr '((A B) (C D)))
        )
    )
)

(print 
    (car 
        (cdr 
            (car '((A B) (C D)))
        )
    )
)
