(defun list_keys (assoc_list)
    (mapcar 
        (lambda (kv_pair) (car kv_pair))
        assoc_list
    )
)

(defvar bob '(
    (temperature 100)
    (pressure (120))
    (pulse 72)
))

(print
    (list_keys bob)
)
; (TEMPERATURE PRESSURE PULSE)

(defvar dan nil)

(print
    (list_keys dan)
)
; NIL