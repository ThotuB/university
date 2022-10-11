(defmacro rev (lst)
    (defun rev_helper (lst)
        (if (null lst) 
            nil 
            (nconc (rev_helper (cdr lst)) (rplacd lst nil))
        )
    )
    `(setf ,lst (rev_helper ,lst))
)

(defvar lst1 '(1 2 3 4 5))
(rev lst1)
(rev lst1)
(print lst1)
; (5 4 3 2 1)

; (defvar lst2 '(one 2 three))
; (rev lst2)
; (print lst2)
; ; (three 2 one)

; (defvar lst3 nil)
; (rev lst3)
; (print lst3)
; ; nil