#include "cc.h"
#include <stdio.h>

int
main(int argc, char **argv)
{
	symtab_t symbols;
	box_t prog;

	fprintf(stderr, "[[ snook. a lisp that doesn't exist. ]]\n");
	symbols = new_symbol_table();
	prog = reader(stdin, "<stdin>", symbols);
	if (!proper(prog)) {
		fprintf(stderr, "invalid program (top-level is not a proper list)\n");
		return 1;
	}
	if (!verify(prog)) {
		fprintf(stderr, "invalid program\n");
		return 1;
	}
	format(stdout, prog);
	return 0;
}
