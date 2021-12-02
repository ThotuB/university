(declaim (sb-ext:muffle-conditions cl:warning))
(setq list1 '(A B C D) )
(setq list2 '((A B) (C D)) )
(setq list3 '(((A) (B) (C) (D))) )
(setq list4 '(A (B) ((C)) (((D)))) )
(setq list5 '((((A))) ((B)) (C) D) )
(setq list6 '((((A) B) C) D) )

(print
    (caddr list1)
)

(print
    (caadr list2)
)

(print
    (car
        (caddar list3)
    )
)

(print
    (car 
        (caaddr list4)
    )
)

(print 
    (caaddr list5)
)

(print
    (cadar list6)
)