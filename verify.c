#include "cc.h"

static int
s_verify(thing_t t)
{
	int i;

	switch (t->type) {
	case TRUE_T:
	case FALSE_T:
	case FIXNUM_T:
	case NIL_T:
	case SYM_T:
		return 1;

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

	default:
		return 0;
	}
}

int
snook_verify(sexpr_t s)
{
	int i;
	for (i = 0; i < s->length; i++)
		if (!s_verify(s->things[i]))
			return 0;
	return 1;
}
