(defun count_atoms (lst)
    (let (
        (head (car lst))
        (tail (cdr lst))
    )
        (if (null lst)
            0
            (+
                (if (atom head)
                    1
                    (count_atoms head)
                )
                (count_atoms tail)
            )
        )
    )
)

(print (count_atoms '(1 2 nil (three 4) 5 (6 (seven 8) nine) 10)))
; 11

(print (count_atoms nil))
; 0

(print (count_atoms '(1 2 3)))
; 3