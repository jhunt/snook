#include "cc.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static void
s_extend(sexpr_t s, thing_t t)
{
	thing_t *things;

	if (s->length > 10) {
		abort();
	}
	things = realloc(s->things, (s->length + 1) * sizeof(struct __thing));
	if (!things) {
		perror("realloc");
		abort();
	}
	s->things = things;
	s->things[s->length++] = t;
}

static thing_t
s_new_thing(int type)
{
	thing_t t = malloc(sizeof(struct __thing));
	if (!t) {
		perror("malloc");
		abort();
	}
	t->type = type;
	return t;
}

static thing_t
s_new_fixnum_thing(int x)
{
	thing_t t = s_new_thing(FIXNUM_T);
	t->value.fixnum = x;
	return t;
}

static thing_t
s_new_sym_thing(const char *x)
{
	thing_t t = s_new_thing(SYM_T);
	t->value.symbol = malloc(sizeof(struct __sym));
	/* FIXME: no de-duplication of symbols */
	if (!t->value.symbol) {
		perror("malloc");
		abort();
	}
	t->value.symbol->name = strdup(x);
	return t;
}

static sexpr_t
s_new_list(void)
{
	sexpr_t s = malloc(sizeof(struct __sexpr));
	if (!s) {
		perror("malloc");
		abort();
	}
	s->length = 0;
	s->things = NULL;
	return s;
}

static thing_t
s_new_list_thing(void)
{
	thing_t t = s_new_thing(LIST_T);
	t->value.list = s_new_list();
	return t;
}

sexpr_t
snook_read(FILE *io, const char *name)
{
//	char parens[SNOOK_MAX_EXPR_NESTING_DEPTH + 1];
	sexpr_t ancestors[SNOOK_MAX_EXPR_NESTING_DEPTH + 1];
	int depth = 0;

	char token[SNOOK_MAX_TOKEN_SIZE + 1];
	int length = 0;

	int line;
	int col;
	char c;

	thing_t thing;

	ancestors[depth] = s_new_list();

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
			s_extend(ancestors[depth], s_new_fixnum_thing(atoi(token)));
			continue;
		}

		if (c == '(') {
			thing = s_new_list_thing();
			s_extend(ancestors[depth], thing);

			depth++;
			ancestors[depth] = thing->value.list;
			c = getc(io);
			continue;
		}

		if (c == ')') {
			if (depth == 0) {
				fprintf(stderr, "too many closing )'s\n");
				abort();
			}
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

			s_extend(ancestors[depth], s_new_sym_thing(token));
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
