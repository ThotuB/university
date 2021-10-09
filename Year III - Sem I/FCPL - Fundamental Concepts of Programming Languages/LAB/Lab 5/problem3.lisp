(defun count_atom (elem nums)
    (if (atom nums) ; stopping condition: nums =/= list
        (if (equal elem nums)
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
    (count_atom 3 '(2 2 3 (4 2 4 (3) 3) 4))
)