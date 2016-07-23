#include "cc.h"
#include <stdlib.h>

static int
s_verify(box_t t)
{
	int i;
	if (t == NIL)
		return 1;

	switch (t->type) {
	case TRUE_T:
	case FALSE_T:
	case FIXNUM_T:
	case SYM_T:
	case CONS_T:
		return 1;

#if 0
	case LIST_T:
		if (t->value.list->length > 0) {
			/* check the calling position */
			switch (t->value.list->things[0]->type) {
			case SYM_T:
			case LIST_T:
				break;

			default:
				fprintf(stderr, "non-functor in calling position\n");
				return 0;
			}
		}
		for (i = 0; i < t->value.list->length; i++)
			if (!s_verify(t->value.list->things[i]))
				return 0;
		return 1;
#endif

	default:
		fprintf(stderr, "unexpected type %1$d (%1$#02x)\n", t->type);
		return 0;
	}
}

int
snook_verify(cons_t s)
{
	box_t t;

	while (s != NIL) {
		if (!s_verify(car(s)))
			return 0;
		t = cdr(s);
		if (t == NIL)
			break;
		if (t->type != CONS_T) {
			fprintf(stderr, "verify: non-cons top-level cdr (%1$d / %1$#02x)\n", t->type);
			abort();
		}
		s = t->value.cons;
	}
	return 1;
}
