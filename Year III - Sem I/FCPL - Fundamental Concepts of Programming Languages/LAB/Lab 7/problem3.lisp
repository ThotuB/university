(defun grandfather (person)
    (let* (
        (father (get (get person 'parents) 'father))
        (grandfather (get ( get father 'parents) 'father))
    )
        (if (null grandfather)
            nil
            (get grandfather 'name)
        )
    )
)

(defun make_person (name father mother)
    (let (
        (person (gensym "PERSON"))
        (parents (gensym "PARENTS"))
    )
        (setf (get parents 'father) father)
        (setf (get parents 'mother) mother)
        (setf (get person 'parents) parents)
        (setf (get person 'name) name)
        person
    )
)
; Grandparents
(defvar dad_gf (make_person "John" nil nil))
(defvar dad_gm (make_person "Mary" nil nil))
(defvar mom_gf (make_person "Dave" nil nil))
(defvar mom_gm (make_person "Jane" nil nil))

;Parents
(defvar dad (make_person "Dan" dad_gf dad_gm))
(defvar mom (make_person "Theo" mom_gf mom_gm))

; Person
(defvar person (make_person "Gion" dad mom))


(print
    (grandfather person)
)