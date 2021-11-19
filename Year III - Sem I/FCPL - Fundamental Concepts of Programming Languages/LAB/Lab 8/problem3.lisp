; TODO

;(defun rev (lst)
;     (do (
;         (left 0 (1+ left))
;         (right (length lst) (1- right))
;     )(
;         (>= left right)
;     )
;         (let (
;             (tmp (nth left lst))
;         )
;             (print (nth left lst))
;         )
;     )
; )

(defun rev (lst)
    (cond 
        ((null lst) 
            nil
        )
        (t 
            (nconc (rev (cdr lst)) (list (car lst)))
        )
    )
)

(defvar lst '(1 2 3 4 5))

(rev lst)

(print lst)