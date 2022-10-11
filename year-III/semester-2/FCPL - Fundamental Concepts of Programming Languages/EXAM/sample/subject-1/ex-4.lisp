;; ((((M) ((A R) (L B))) (O R)) (O)) -> 1st B

(print 
    (cadadr (cadaar '((((M) ((A R) (L B))) (O R)) (O))))
)