(declaim (sb-ext:muffle-conditions cl:warning))

(defun rotate_right (lst)
    (setq reversed_lst (reverse lst))
    (cons (car reversed_lst) (reverse (cdr reversed_lst)))
)


(print
    (rotate_right '(a b c d e))
)