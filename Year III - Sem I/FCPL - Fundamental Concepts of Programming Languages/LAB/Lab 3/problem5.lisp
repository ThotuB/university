(declaim (sb-ext:muffle-conditions cl:warning))

(defun ec2 (a b c)
    (setq delta (sqrt (- (* b b) (* 4 a c))))
    (setq mb (- b))
    (setq x1 (/ (+ mb delta) (* 2 a)))
    (setq x2 (/ (- mb delta) (* 2 a)))
    
    (list x1 x2)
)


(print
    (ec2 6 1 2)
)