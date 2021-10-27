; (declaim (sb-ext:muffle-conditions cl:warning)) ; suppress compiler warnings

(defun is_not_real (a b c)
    (setq delta (- (* b b) (* 4 a c)))
    (> 0 delta)
)


(print
    (is_not_real 6 13 6)
)