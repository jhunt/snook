#include "cc.h"
#include <stdlib.h>

int
verify(box_t t)
{
	int i;
	if (t == NIL || t == TRUE || t == FALSE)
		return 1;

	switch (t->type) {
	case FIXNUM_T:
	case SYM_T:
		return 1;

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
