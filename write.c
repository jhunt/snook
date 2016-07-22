#include "cc.h"

static int
s_write_sub(FILE *out, thing_t t)
{
	int i;

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

	case NIL_T:
		fprintf(out, "nil");
		break;

	case SYM_T:
		fprintf(out, "%s", t->value.symbol->name);
		break;

	case LIST_T:
		fprintf(out, "(");
		for (i = 0; i < t->value.list->length; i++) {
			if (i != 0) fprintf(out, " ");
			s_write_sub(out, t->value.list->things[i]);
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
snook_write(FILE *out, sexpr_t s)
{
	int i;

	for (i = 0; i < s->length; i++) {
		s_write_sub(out, s->things[i]);
		fprintf(out, "\n");
	}

	return 0;
}
