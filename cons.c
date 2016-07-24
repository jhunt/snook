#include "cc.h"
#include <stdlib.h>

cons_t
cons(box_t a, box_t d)
{
	cons_t c = malloc(sizeof(struct __cons));
	if (!c) {
		perror("malloc");
		abort();
	}

	c->car = a;
	c->cdr = d;
	return c;
}

box_t
car(box_t c)
{
	if (c == NIL)
		return NIL;
	return c->value.cons->car;
}

box_t
cdr(box_t c)
{
	if (c == NIL)
		return NIL;
	return c->value.cons->cdr;
}

void
append(box_t *c, box_t a)
{
	box_t t;

	if (*c == NIL) {
		*c = box_cons(cons(a, NIL));
		return;
	}
	while (cdr(*c) != NIL) {
		t = cdr(*c);
		if (t->type != CONS_T) {
			perror("non-cons cdr");
			abort();
		}
		c = &t;
	}
	(*c)->value.cons->cdr = box_cons(cons(a, NIL));
	return;
}
