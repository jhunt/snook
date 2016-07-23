#include "cc.h"
#include <stdlib.h>

static int
s_write_sub(FILE *out, thing_t t)
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
			s_write_sub(out, car(t->value.cons));
			t = cdr(t->value.cons);
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
snook_write(FILE *out, cons_t s)
{
	thing_t t;

	while (s != NIL) {
		s_write_sub(out, car(s));
		t = cdr(s);
		if (t == NIL)
			break;
		if (t->type != CONS_T) {
			fprintf(stderr, "write: non-cons top-level cdr (%1$d / %1$#02x)\n", t->type);
			abort();
		}
		s = t->value.cons;
		fprintf(out, "\n");
	}
	return 0;
}
