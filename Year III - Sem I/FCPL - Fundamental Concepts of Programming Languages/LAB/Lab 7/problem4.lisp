(defun adam (person)
    (let (
        (father (get person 'father))
    )
        (if (null father)
            person
            (adam father)
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

; GGG Grandparent
(defvar jon (make_person "Jon" nil nil))

; Great Great Grandparents
(defvar john (make_person "John" jon nil))
(defvar emi  (make_person "Emi"  nil nil))

; Great Grandparents
(defvar john2 (make_person "John II" john nil))
(defvar sara  (make_person "Sara"    nil  nil))
(defvar rich  (make_person "John II" nil  nil))
(defvar cara  (make_person "Cara"    nil  emi))

; Grand Parents
(defvar jonh3 (make_person "John III" john2 sara))
(defvar ali   (make_person "Ali"      rich  cara))

;Parents
(defvar dad (make_person "Dan" jonh3 ali))

; Person
(defvar person (make_person "Gion" dad nil))


(print
    (get (adam person) 'name)
)
; "Jon" 

(print
    (get (adam dad) 'name)
)
; "Jon" 

(print
    (get (adam rich) 'name)
)
; "John II"

(print
    (get (adam jon) 'name)
)
; "Jon" 
