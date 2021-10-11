(defmacro do_times (head &rest body)
    (let (
        (var (car head))
        (cnt (cadr head))
        (res (caddr head))
    )
        `(do (
            (,var 0 (1+ ,var))
        )(
            (>= ,var ,cnt)
            ,res
        )
            ,@body
        )
    )
)

(format t "~%return: ~a~%" (do_times (num 5 10)
    (format t "~a " num)
))

(format t "~%return: ~a~%"  (do_times (num 2)
    (format t "~a " num)
))


(format t "~%return: ~a~%"  (dotimes (num 5 10)
    (format t "~a " num)
))

(format t "~%return: ~a~%"  (dotimes (num 2)
    (format t "~a " num)
))