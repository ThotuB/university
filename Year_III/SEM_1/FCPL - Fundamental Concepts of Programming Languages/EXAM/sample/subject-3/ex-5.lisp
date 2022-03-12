;; (((A B A B) (A B)) (A B) A B (A B A B) (B A) A B B A)

(defvar L '(A B))
(defvar R (reverse L))

(print 
    (append (list (list (append L L) L)) (list L) L (list (append L L)) (list R) L R)
)