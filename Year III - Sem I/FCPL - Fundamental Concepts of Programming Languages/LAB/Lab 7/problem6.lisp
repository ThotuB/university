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

(defvar mat (make-array '(5 8)))

(print_matrix mat)
(print_matrix nil)