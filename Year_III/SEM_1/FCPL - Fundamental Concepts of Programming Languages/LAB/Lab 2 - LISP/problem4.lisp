(declaim (sb-ext:muffle-conditions cl:warning))
(setq list1 '((A B) (C D) (E F)))
(setq list2 '((A B) (C D) (E F)))
(setq list3 '(CDR ((A B) (C D) (E F))))
(setq list4 '(CAR (CDR (CDR ((A B) (C D) (E F))))))
(setq list5 '(CAR (CAR (CDR (CDR ((A B) (C D) (E F)))))))

; ((A B) (C D) (E F))
(print 
    (CAR ; D
        (CDR ; (D)
            (CAR ; (C D)
                (CDR list1) ; ((C D) (E F))
            )
        )
    )
)

; ((A B) (C D) (E F))
(print 
    (CAR ; E
        (CAR ; (E F)
            (CDR ; ((E F))
                (CDR list2) ; ((C D) (E F))
            )
        )
    )
)

; (CDR ((A B) (C D) (E F)))
(print 
    (CAR ; (A B)
        (CAR ; ((A B) (C D) (E F))
            (CDR list3) ; (((A B) (C D) (E F)))
        )
    )
)

; (CDR (CDR ((A B) (C D) (E F))))
; (print 
;    (CAR ; TYPE ERROR
;        (CAR '(CDR (CDR ((A B) (C D) (E F))))) ; CDR
;    )
; ) 

; (CAR (CDR (CDR ((A B) (C D) (E F))))
(print 
    (CAR list4) ; CAR
)

; (CAR (CAR (CDR (CDR ((A B) (C D) (E F)))))
(print list5)
