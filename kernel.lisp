(quote x)      ; special; returns x
(atom x)       ; normal; returns true if x is an atom
(eq x y)       ; normal; returns true if x and y are the same atom
(car l)        ; normal; returns the head of a list
(cdr l)        ; normal; returns the tail of a list
(cons x y)     ; normal; create a CONStruct of (x . y)
(cond (p1 e1)  ; special
      (p2 e2)
      (pn en))
(lambda (p1 pn) e) ; special?
(label n lambda)   ; special?

;;; derivatives

(label ∧ (p q) ; and
  (cond (p q)
        (t #f)))

(label ∨ (p q) ; or
  (cond (p  #t)
        (#t q)))

(label ¬ (p) ; not
  (cond (p  #f)
        (#t #t)))

(label null (p)
  (∧ (atom p) (eq p #nil)))
