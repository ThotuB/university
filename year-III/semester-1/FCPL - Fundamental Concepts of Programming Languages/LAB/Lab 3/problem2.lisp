(defun rotate_left (lst)
    (append (cdr lst) (list (car lst)))
)


(print
    (rotate_left '(a b c d e))
)