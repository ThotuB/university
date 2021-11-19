(defun ancestors (person)
    (if (null person)
        nil
        (let (
            (father (get person 'father))
            (mother (get person 'mother))
        )
            (append (list person) (ancestors father) (ancestors mother))
        )
    )
)

(defun make_person (name father mother)
    (setf (get name 'father) father)
    (setf (get name 'mother) mother)
)

; GGG Grandparent
(make_person 'markus nil nil)

; Great Great Grandparents
(make_person 'john 'markus nil)
(make_person 'emi   nil nil)

; Great Grandparents
(make_person 'john_II 'john  nil)
(make_person 'sara     nil   nil)
(make_person 'rich     nil   nil)
(make_person 'cara     nil  'emi)

; Grand Parents
(make_person 'john_III 'john_II 'sara)
(make_person 'ali      'rich    'cara)

;Parents
(make_person 'dan 'john_III 'ali)

; Person
(make_person 'bob 'dan nil)


(print
    (ancestors 'bob)
)
; (BOB DAN JOHN_III JOHN_II JOHN MARKUS SARA ALI RICH CARA EMI) 

(print 
    (ancestors 'ali)
)
; (ALI RICH CARA EMI)  

(print
    (ancestors 'john)
)
; (MARKUS) 