(quote x)      ; special; returns x
(atom x)       ; normal; returns true if x is an atom
(eq x y)       ; normal; returns true if x and y are the same atom
(car l)        ; normal; returns the head of a list
(cdr l)        ; normal; returns the tail of a list
(cons x y)     ; normal; create a CONStruct of (x . y)
(cond (p1 e1)  ; special
      (p2 e2)
      (pn en))
(fn (p1 pn) e) ; special?
(define ...)   ; special?
(macro (form)
  expansion)

;;; derivatives

(define (∧ p q) ; and
  (cond (p q)
        (t #f)))

(define (∨ p q) ; or
  (cond (p  #t)
        (#t q)))

(define (¬ p) ; not
  (cond (p  #f)
        (#t #t)))

(define (null p)
  (∧ (atom p) (eq p #nil)))

(macro (if test conseq alt)
  `(cond (,test ,conseq)
         ('t    ,alt)))
