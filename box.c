#include "cc.h"
#include <stdlib.h>

box_t
box(type_t type)
{
	box_t t = malloc(sizeof(struct __box));
	if (!t) {
		perror("malloc");
		abort();
	}
	t->type = type;
	return t;
}

box_t
box_fixnum(int x)
{
	box_t t = box(FIXNUM_T);
	t->value.fixnum = x;
	return t;
}

box_t
box_sym(sym_t s)
{
	box_t t = box(SYM_T);
	t->value.symbol = s;
	return t;
}

box_t
box_builtin(opfn_t f)
{
	box_t t = box(BUILTIN_T);
	t->value.builtin = f;
	return t;
}
