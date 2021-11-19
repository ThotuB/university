(defun fetch (key assoc_list)
    (if (assoc key assoc_list)
        (cdr (assoc key assoc_list))
        '?
    )
)

(defvar bob '(
    (temperature 100)
    (pressure (120 60))
    (pulse 72)
))

(print
    (fetch temperature bob)
)
; 100

(print 
    (fetch 'pressure bob)
)
; (120 60)

(print
    (fetch 'complaints bob)
)
; ?