(defun to_matrix_1 (lst2d)
    (defun elem_to_matrix (lst row col matrix)
        (cond
            ((null lst) matrix)
            (t 
                (setf (aref matrix row col) (car lst))
                (elem_to_matrix (cdr lst) row (1+ col) matrix)
            )
        )
    )

    (defun row_to_matrix (lst2d row matrix)
        (cond
            ((null lst2d) matrix)
            (t
                (elem_to_matrix (car lst2d) row 0 matrix)
                (row_to_matrix (cdr lst2d) (1+ row) matrix)
            )
        )
    )

    (let* (
        (rows (length lst2d))
        (cols (length (car lst2d)))
        (matrix (make-array (list rows cols)))
    )
        (row_to_matrix lst2d 0 matrix)
    )
)

(defun to_matrix_2 (lst2d)
    (let* (
        (rows (length lst2d))
        (cols (length (car lst2d)))
        (matrix (make-array (list rows cols)))
        (row 0)
        (col 0)
    )
        (mapcar (lambda (lst) 
                (mapcar (lambda (elem)
                        (setf (aref matrix row col) elem)
                        (setq col (1+ col))
                    )
                    lst
                )
                (setq row (1+ row))
                (setq col 0)
            )
            lst2d
        )
        matrix
    )
)

(print (to_matrix_2 '(
    (1 2)
    (3 4)
    (5 6)
)))

(print (to_matrix_1 '(
    (1)
    (2)
    (3)
)))

(print (to_matrix_1 '(
    (1)
)))

(print (to_matrix_1 '(
    ()
)))

(print (to_matrix_1 '(
    
)))
