(defun is_member (elem lst)
    (cond 
        ((null lst) nil)
        ((eql elem (car lst)) lst)
        (t (is_member elem (cdr lst)))
    )
)

(print (is_member 4 '(1 (2 3) 4 5 6)))
; (4 5 6)

(print (is_member 4 '(1 (2 3) 4.0 5 6)))
; NIL

(print (is_member '(2 3) '(1 (2 3) 4 5 6)))
; NIL

(print (is_member 7 '(1 (2 3) 4 5 6)))
; NIL