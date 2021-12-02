(defmacro define ((name &rest params) &rest body)
    `(defun ,name ,params
        ,@body
    )
)

(define (add a b c)
    (+ a b c)
)

(print (add 1 2 3))
; 6

(define (hello_world)
    (print 'hello_world)
    (print 'goodbye_world)
)

(hello_world)
; HELLO_WORLD
; GOODBYE_WORLD