#include "cc.h"
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
	symtab_t symbols;
	box_t prog, last;

	fprintf(stderr, "[[ snook. a lisp that doesn't exist. ]]\n");
	symbols = new_symbol_table();
	prog = NIL;
	while (!feof(stdin)) {
		if (isatty(fileno(stdin)))
			fprintf(stdout, "s:> ");
		prog = reader(stdin, "<stdin>", symbols);
		if (prog == EOS)
			break;
		last = eval(prog, symbols);
		if (isatty(fileno(stdin)))
			format(stdout, last);
	}
	if (!isatty(fileno(stdin)))
		format(stdout, last);
	return 0;
}
