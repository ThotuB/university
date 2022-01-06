(defun trim_head (lst n)
    (cond 
        ((null lst) nil)
        ((zerop n) lst)
        (t (trim_head (cdr lst) (- n 1)))
    )
)

(print (trim_head '(1 2 3 4 5 6) 3))
; (4 5 6)

(print (trim_head '(1 2 3) 3))
; NIL

(print (trim_head '(1) 3))
; NIL

(print (trim_head nil 3))
; NIL