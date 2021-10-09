(declaim (sb-ext:muffle-conditions cl:warning))
(SETQ L '(A B))

(print (LENGTH '(A B)))
(print (LENGTH '((A B) (C D))))
(print (LENGTH L))
(print (LENGTH (APPEND L L)))

(print (REVERSE '(A B)))
(print (REVERSE '((A B) (C D))))

(print (SUBST 'A 'B '(A B C)))

(print (LAST '(A B C)))
(print (LAST '((A B) (C D))))