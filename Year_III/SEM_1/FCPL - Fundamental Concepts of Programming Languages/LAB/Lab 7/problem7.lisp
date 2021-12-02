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

; (defun to_matrix_2 (lst2d)
;     (let* (
;         (rows (length lst2d))
;         (cols (length (car lst2d)))
;         (matrix (make-array (list rows cols)))
;         (row 0)
;         (col 0)
;     )
;         (mapcar (lambda (lst) 
;                 (mapcar (lambda (elem)
;                         (setf (aref matrix row col) elem)
;                         (setq col (1+ col))
;                     )
;                     lst
;                 )
;                 (setq row (1+ row))
;                 (setq col 0)
;             )
;             lst2d
;         )
;         matrix
;     )
; )

(defun print_matrix (matrix)
    (if (null matrix)
        nil
        (let (
            (rows (array-dimension matrix 0))
            (cols (array-dimension matrix 1))
        )
            (do ((i 0 (1+ i))) ((= i rows))
                (do ((j 0 (1+ j))) ((= j cols))
                    (princ (aref matrix i j))
                    (princ " ")
                )
                (terpri)
            )
        )
    ) 
)

(print_matrix (to_matrix_1 '(
    (1 2)
    (3 4)
    (5 6)
)))
; 1 2
; 3 4
; 5 6

(print_matrix (to_matrix_1 '(
    (1)
    (2)
    (3)
)))
; 1
; 2
; 3

(print_matrix (to_matrix_1 '(
    (1)
)))
; 1

(print_matrix (to_matrix_1 '(
    ()
)))
; 

(print_matrix (to_matrix_1 '(
    
)))
