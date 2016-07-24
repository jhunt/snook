#include "cc.h"
#include <stdio.h>

int
main(int argc, char **argv)
{
	symtab_t symbols;
	box_t prog;

	fprintf(stderr, "[[ snook. a lisp that doesn't exist. ]]\n");
	symbols = new_symbol_table();
	while (!feof(stdin)) {
		fprintf(stdout, "s:> ");
		prog = reader(stdin, "<stdin>", symbols);
		format(stdout, eval(prog, symbols));
	}
	return 0;
}
