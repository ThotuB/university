(defun is_member (elem lst)
    (cond 
        ((null lst) nil)
        ((eql elem (car lst)) lst)
        (t (is_member elem (cdr lst)))
    )
)

; 4 is 4 -> 4 member
(print
    (member 4 '(1 (2 3) 4 5 6))
)

(print
    (is_member 4 '(1 (2 3) 4 5 6))
)

; 4 is not 4.0 -> 4 is not member
(print
    (member 4 '(1 (2 3) 4.0 5 6))
)

(print
    (is_member 4 '(1 (2 3) 4.0 5 6))
)

; (2 3) does not point to the same object as (2 3) -> (2 3) is not member
(print
    (member '(2 3) '(1 (2 3) 4 5 6))
)

(print
    (is_member '(2 3) '(1 (2 3) 4 5 6))
)

; 7 is not member
(print
    (member 7 '(1 (2 3) 4 5 6))
)

(print
    (is_member 7 '(1 (2 3) 4 5 6))
)