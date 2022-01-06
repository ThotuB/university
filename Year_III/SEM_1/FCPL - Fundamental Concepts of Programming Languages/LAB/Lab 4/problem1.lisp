(defun factorial (num)
    (if (= 0 num)
        1
        (* num (factorial (- num 1)))
    )
)

(print (factorial 1))
; 1

(print (factorial 10))
; 3628800

(print (factorial 15))
; 1307674368000