(declaim (sb-ext:muffle-conditions cl:warning))

(defun palindrome (lst)
    (setq reversed_lst (reverse lst))
    (append lst reversed_lst)
)


(print
    (palindrome '(a b c d e))
)