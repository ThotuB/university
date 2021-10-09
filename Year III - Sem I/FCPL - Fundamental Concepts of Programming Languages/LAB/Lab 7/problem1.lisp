(defun fetch (key assoc_list)
    (if (assoc key assoc_list)
        (cadr (assoc key assoc_list))
        '?
    )
)

(defvar bob '(
    (temperature 100)
    (pressure (120))
    (pulse 72)
))

(print
    (fetch 'temperature bob)
)

(print
    (fetch 'complaints bob)
)