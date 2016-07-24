#include "cc.h"
#include <stdlib.h>

box_t
cons(box_t a, box_t d)
{
	box_t t = box(CONS_T);
	t->value.cons = malloc(2 * sizeof(box_t));
	if (!t->value.cons) {
		perror("malloc");
		abort();
	}

	t->value.cons[0] = a;
	t->value.cons[1] = d;
	return t;
}

box_t
car(box_t c)
{
	if (c == NIL)
		return NIL;
	return c->value.cons[0];
}

box_t
cdr(box_t c)
{
	if (c == NIL)
		return NIL;
	return c->value.cons[1];
}

void
append(box_t *c, box_t a)
{
	box_t t;

	if (*c == NIL) {
		*c = cons(a, NIL);
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
	(*c)->value.cons[1] = cons(a, NIL);
	return;
}
