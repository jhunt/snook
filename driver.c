#include "cc.h"
#include <stdio.h>

int
main(int argc, char **argv)
{
	symtab_t symbols;
	cons_t prog;

	fprintf(stderr, "[[ snook. a lisp that doesn't exist. ]]\n");
	symbols = new_symbol_table();
	prog = snook_read(stdin, "<stdin>", symbols);
	if (!snook_verify(prog)) {
		fprintf(stderr, "invalid program\n");
		return 1;
	}
	snook_write(stdout, prog);
	return 0;
}
