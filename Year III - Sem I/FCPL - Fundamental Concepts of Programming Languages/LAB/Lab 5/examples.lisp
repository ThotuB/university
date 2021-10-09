(defun count-deep-div (div nums)
    (if (atom nums) ; stopping condition: nums =/= list
        (if (zerop (rem nums div))
            1
            0
        )
        (apply '+
            (mapcar 
                (lambda (lst) (count-deep-div div lst))
                nums
            )
        )
    )
)

(defun depth (lst)
   (cond 
        ((null lst) 
            1
        )
        ((atom lst) 
            0
        )
        (t 
            (+ 1 (apply 'max (mapcar 'depth lst)))
        )
    )
)

(print
    (depth '(1 ((2) 3 (4 5 6)) (7 (8)) 9))
)