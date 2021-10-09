(defun to_matrix (ll)
    (let* (
        (rows (length ll))
        (cols (length (car ll)))
        (matrix (make-array (list rows cols)))
    )
        (do ((i 0 (1+ i))) ((= i rows))
            (do ((j 0 (1+ j))) ((= j cols))
                (setf (aref matrix i j) (nth j (nth i ll)))
            )
        )
        matrix
    )
)

(defvar mat '(
    (1 2)
    (3 4)
    (5 6)
))

(print (to_matrix mat))