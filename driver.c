#include "cc.h"
#include <stdio.h>

int
main(int argc, char **argv)
{
	fprintf(stderr, "[[ snook. a lisp that doesn't exist. ]]\n");
	snook_write(stdout, snook_read(stdin, "<stdin>"));
	return 0;
}
