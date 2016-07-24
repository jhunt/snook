#include "cc.h"

int
proper(box_t b)
{
	while (!nil(b)) {
		if (atom(b)) return 0;
		b = cdr(b);
	}
	return 1;
}

int
sym(box_t b, symtab_t symbols, const char *name)
{
	sym_t s;

	if (b == NIL || b->type != SYM_T)
		return 0;

	s = intern(symbols, name);
	return s && s == b->value.symbol;
}
