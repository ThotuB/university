(defun is_member (elem lst)
    (cond 
        ((null lst) nil)
        ((= elem (car lst)) lst)
        (t (is_member elem (cdr lst)))
    )
)

(print
    (member 3 '(1 2 3 4 5 6))
)