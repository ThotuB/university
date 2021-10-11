; OPERATIONS
; (not x)   -> (nand x x)
; (and x y) -> (nand (nand x y) true)
; (or x y)  -> (nand (not x) (not y)) -> (nand (nand x x) (nand y y))
; ALTERNATE AND
; (and x y) -> (not (nand x y))       -> (nand (nand x y) (nand x y))

(defun DeMorgan (lst)
    (if (atom lst)
        lst
        (let (
            (operation  (car lst))
            (ops (cdr lst))
        )
            (cond
                ((equal operation 'nand) ; NAND
                    (cons 'nand (mapcar 'DeMorgan ops))
                )
                ((equal operation 'not)  ; NOT
                    (list 'nand (DeMorgan (car ops)) (DeMorgan (car ops)))
                )
                ((equal operation 'and)  ; AND
                    (list 'nand (DeMorgan (cons 'nand ops)) 'true )
                )
                ((equal operation 'or)   ; OR
                    (DeMorgan (cons 'nand (mapcar (lambda (o) (list 'not o)) ops)))
                )
            )
        )
    )
)

; ALTERNATE AND
; ((equal op 'and)
;     (DeMorgan (list 'not (cons 'nand ops)))
; )

(print (DeMorgan '(and a (not b)) ))
(print (DeMorgan '(or a b c) ))
(print (DeMorgan '(and a (or c d) (not e)) ))