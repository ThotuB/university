(defmacro if_1 (test success &optional failure)
    (subst test 'test
    (subst success 'success
    (subst failure 'failure
        '(cond (test success) (t failure))
    )))
)

(defmacro if_2 (test success &optional failure)
    `(cond (,test ,success) (t ,failure))
)


(if_1 (> 3 2)
    (print "success")
    (print "failure")
)

(if_1 (> 2 3)
    (print "success")
    (print "failure")
)

(if_2 (> 3 2)
    (print "success")
    (print "failure")
)

(if_2 (> 2 3)
    (print "success")
    (print "failure")
)