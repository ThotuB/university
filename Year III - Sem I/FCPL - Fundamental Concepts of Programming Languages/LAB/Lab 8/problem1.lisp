(defmacro define (func &rest body)
    (let (
        (name (car func))
        (params (cdr func))
    )
        `(defun ,name ,params
            ,@body
        )
    )
)

(define (add a b c)
    (+ a b c)
)

(print (add 1 2 3))