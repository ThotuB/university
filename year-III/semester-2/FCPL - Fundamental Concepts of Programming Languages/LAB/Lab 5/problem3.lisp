(defun count_atom (elem nums)
    (if (atom nums)
        (if (eq elem nums)
            1
            0
        )
        (apply '+
            (mapcar 
                (lambda (lst) (count_atom elem lst))
                nums
            )
        )
    )
)

(print
    (count_atom nil '(2 b () a (4 nil nil c v a (a) 3) a))
)
; 3