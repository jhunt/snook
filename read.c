#include "cc.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static box_t
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

static box_t
box_cons(cons_t c)
{
	box_t t = box(CONS_T);
	t->value.cons = c;
	return t;
}

static box_t
box_fixnum(int x)
{
	box_t t = box(FIXNUM_T);
	t->value.fixnum = x;
	return t;
}

static box_t
box_sym(sym_t s)
{
	box_t t = box(SYM_T);
	t->value.symbol = s;
	return t;
}

static void
append(cons_t *c, box_t a)
{
	box_t t;

	if (*c == NIL) {
		*c = cons(a, NIL);
		return;
	}
	while (cdr(*c) != NIL) {
		t = cdr(*c);
		if (t->type != CONS_T) {
			perror("non-cons cdr");
			abort();
		}
		c = &t->value.cons;
	}
	(*c)->cdr = box_cons(cons(a, NIL));
	return;
}

cons_t
snook_read(FILE *io, const char *name, symtab_t symbols)
{
//	char parens[SNOOK_MAX_EXPR_NESTING_DEPTH + 1];
	cons_t ancestors[SNOOK_MAX_EXPR_NESTING_DEPTH + 1];
	int depth = 0;

	char token[SNOOK_MAX_TOKEN_SIZE + 1];
	int length = 0;

	int line;
	int col;
	char c;

	ancestors[depth] = NIL;

	line = 1; col = 0;
	c = getc(io);
	while (!feof(io)) {
		while (!feof(io) && isspace(c)) {
			if (c == '\n') {
				line++;
				col = 0;
			} else {
				col++;
			}
			c = getc(io);
		}
		if (feof(io))
			break;

		if (c == ';') {
			while (c != '\n')
				c = getc(io);
			continue;
		}

		if (isdigit(c)) {
			length = 0;
			while (!feof(io) && isdigit(c) && length < SNOOK_MAX_TOKEN_SIZE) {
				token[length++] = c;
				c = getc(io);
				col++;
			}
			token[length] = '\0';

			/* FIXME: no error checking with atoi() */
			append(&ancestors[depth], box_fixnum(atoi(token)));
			continue;
		}

		if (c == '(') {
			ancestors[++depth] = NIL;
			c = getc(io);
			continue;
		}

		if (c == ')') {
			if (depth == 0) {
				fprintf(stderr, "too many closing )'s\n");
				abort();
			}
			append(&ancestors[depth - 1],
			       ancestors[depth] == NIL ? NIL
			                               : box_cons(ancestors[depth]));
			depth--;
			c = getc(io);
			continue;
		}

		if (isalpha(c) || strchr("+-*/%=", c)) {
			length = 0;
			while (!feof(io) && c != '(' && c != ')' && !isspace(c) && length < SNOOK_MAX_TOKEN_SIZE) {
				token[length++] = c;
				c = getc(io);
				col++;
			}
			token[length] = '\0';

			append(&ancestors[depth], box_sym(intern(symbols, token)));
			continue;
		}

		fprintf(stderr, "FAILED at %s:%d:%d '%c' not recognized\n",
				name, line, col, c);
		abort();
	}

	if (depth != 0) {
		fprintf(stderr, "not enough closing )'s [depth %d]\n", depth);
		abort();
	}

	return ancestors[depth];
}
