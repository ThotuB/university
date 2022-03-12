;; ((A B) ((B A A B) (A B) A B) (B A) (B A) A B B A A B)

(defvar L '(A B))
(defvar R (reverse L))

(print 
    (append (list L (append (list (append R L) L) L)) (list R) (list L) L R L)
)