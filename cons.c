#include "cc.h"
#include <stdlib.h>

cons_t
cons(thing_t a, thing_t d)
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

thing_t
car(cons_t c)
{
	if (c == NIL)
		return NIL;
	return c->car;
}

thing_t
cdr(cons_t c)
{
	if (c == NIL)
		return NIL;
	return c->cdr;
}
