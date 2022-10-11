; (declaim (sb-ext:muffle-conditions cl:warning)) ; suppress compiler warnings

(defun is_palindrome (lst)
    (setq rev_lst (reverse lst))
    (equal lst rev_lst)
)

(print
    (is_palindrome '(1 2 3 3 2 1))
)

(print
    (is_palindrome '(1 2 3 2 1))
)

(print
    (is_palindrome '(1 2 3 2 2))
)