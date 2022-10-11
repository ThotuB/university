(print (car nil)) ; head of () -> nil
(print (cdr nil)) ; tail of () -> nil

(print
    (cons (car nil) (cdr nil)) ; cons of nil nil -> (nil . nil) -> (nil)
)

(print (cons nil nil)) ; same as above