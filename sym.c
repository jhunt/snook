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
	sym_t s;
	struct __syment *ent;

	for (ent = table->first; ent; ent = ent->next)
		if (strcmp(s->name, name) == 0)
			return s;
	return NULL;
}
