(defun add (num1 num2)
    (if (= 0 num2)
        num1
        (add (1+ num1) (1- num2))
    )
)

(print (add 5 7))
; 12

(print (add 7 5))
; 12