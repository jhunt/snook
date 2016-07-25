#include "cc.h"
#include <stdlib.h>
#include <string.h>

symtab_t
new_symbol_table()
{
	symtab_t t;

	t = malloc(sizeof(struct __symtab));
	if (!t) {
		perror("malloc");
		abort();
	}

	t->first = NULL;
	return t;
}

sym_t
intern(symtab_t table, const char *name)
{
	sym_t s;
	struct __syment *ent;

	s = lookup(table, name);
	if (s) {
		return s;
	}

	s = malloc(sizeof(struct __sym));
	if (!s) {
		perror("malloc");
		abort();
	}
	s->name = strdup(name);
	s->value = UNDEF;
	if (strcmp(name, "t")   == 0) s->value = TRUE;
	if (strcmp(name, "f")   == 0) s->value = FALSE;
	if (strcmp(name, "nil") == 0) s->value = NIL;

	ent = malloc(sizeof(struct __syment));
	if (!ent) {
		perror("malloc");
		abort();
	}
	ent->symbol = s;
	ent->next = table->first;
	table->first = ent;
	return s;
}

sym_t
lookup(symtab_t table, const char *name)
{
	struct __syment *ent;

	for (ent = table->first; ent; ent = ent->next)
		if (strcmp(ent->symbol->name, name) == 0)
			return ent->symbol;
	return NULL;
}
