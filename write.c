#include "cc.h"
#include <stdlib.h>

static int
s_write_sub(FILE *out, box_t t)
{
	int i;
	if (t == NIL) {
		fprintf(out, "nil");
		return 0;
	}

	switch (t->type) {
	case TRUE_T:
		fprintf(out, "t");
		break;

	case FALSE_T:
		fprintf(out, "f");
		break;

	case FIXNUM_T:
		fprintf(out, "%d", t->value.fixnum);
		break;

	case SYM_T:
		fprintf(out, "%s", t->value.symbol->name);
		break;

	case CONS_T:
		fprintf(out, "(");
		while (t != NIL) {
			s_write_sub(out, car(t));
			t = cdr(t);
			if (t != NIL) {
				fprintf(out, " ");
			}
		}
		fprintf(out, ")");
		break;

	default:
		fprintf(stderr, "print(): UNHANDLED TYPE %1$d (%1$#02x)\n", t->type);
		return -1;
	}

	return 0;
}

int
format(FILE *out, box_t s)
{
	box_t t;

	while (s != NIL) {
		s_write_sub(out, car(s));
		fprintf(out, "\n");
		s = cdr(s);
	}
	return 0;
}
