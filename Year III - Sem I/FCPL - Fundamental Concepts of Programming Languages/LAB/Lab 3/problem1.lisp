(defun my_first (lst)
    (car lst)
)

(defun my_second (lst)
    (cadr lst)
)

(defun my_third (lst)
    (caddr lst)
)

(defun my_rest (lst)
    (cdr lst)
)

(defun construct (lst1 lst2)
    (cons lst1 lst2)
)


(print
    (my_first '(1 2 3 4 5))
)

(print
    (my_second '(1 2 3 4 5))
)

(print
    (my_third '(1 2 3 4 5))
)

(print
    (my_rest '(1 2 3 4 5))
)

(print 
    (construct 'a '(b c d e))
)