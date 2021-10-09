(defun ancestors (person)
    (if (null person)
        nil
        (let (
            (father (get person 'father))
            (mother (get person 'mother))
            (name (get person 'name))
        )
            (append (list name) (ancestors father) (ancestors mother))
        )
    )
)

(defun make_person (name father mother)
    (let (
        (person (gensym "PERSON"))
    )
        (setf (get person 'father) father)
        (setf (get person 'mother) mother)
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
    (ancestors person)
)