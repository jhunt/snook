#include "cc.h"
#include <stdio.h>

int
main(int argc, char **argv)
{
	fprintf(stderr, "[[ snook. a lisp that doesn't exist. ]]\n");
	symtab_t symbols = new_symbol_table();
	snook_write(stdout, snook_read(stdin, "<stdin>", symbols));
	return 0;
}
