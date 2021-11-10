(defun print_spaces (indent)
    (cond 
        ((> indent 0)
            (princ '|  |)
            (print_spaces (- indent 1))
        )
    )
)

(defun pretty_print (lst)
    (defun print_elem (elem indent)
        (if (atom elem)
            (princ elem)
            (print_list elem indent)
        )
    )

    (defun print_list (lst indent)
        (setq indent (1+ indent))

        (princ '|( |)
        (print_elem (car lst) indent)
        (mapcan (lambda (elem)
                (terpri)
                (print_spaces indent)
                (print_elem elem indent)
            )
            (cdr lst)
        )
        (princ '| )|)
    )

    (print_elem lst 0)
    (terpri)
)

; (pretty_print '(a ( (b c) d e) nil () f (g h) (i)) )
; ( A
;   ( ( B
;       C )
;     D
;     E )
;   NIL
;   F
;   ( G
;     H )
;   ( I ) )

; (pretty_print '(a b c) )
; ( A
;   B
;   C )

; (pretty_print '((a b c)) )
; ( ( A
;     B
;     C ) )

; (pretty_print 'a)
; A

; (pretty_print nil)
; NIL

(defun my_pretty_print (lst)
    (defun my_print_elem (elem indent)
        (if (atom elem)
            (princ elem)
            (my_print_list elem indent)
        )
    )

    (defun my_print_list (lst indent)
        (setq indent (1+ indent))

        (princ '|(|)
        (mapcan (lambda (elem)
                (terpri)
                (print_spaces indent)
                (my_print_elem elem indent)
            )
            lst
        )
        (terpri)
        (print_spaces (1- indent))
        (princ '|)|)
    )

    (my_print_elem lst 0)
    (terpri)
)

(my_pretty_print '(a ( (b c) d e) nil f (g h) (i)) )
; (
;   A
;   (
;     (
;       B
;       C
;     )
;     D
;     E
;   )
;   NIL
;   F
;   (
;     G
;     H
;   )
;   (
;     I
;   )
; )

(my_pretty_print '(a b c) )
; (
;   A
;   B
;   C
; )

(my_pretty_print '((a b c)) )
; (
;   (
;     A
;     B
;     C
;   )
; )

(my_pretty_print 'a)
; A

(my_pretty_print nil)
; NIL