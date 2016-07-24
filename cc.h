#ifndef SNOOK_CC_H
#define SNOOK_CC_H

#include <stdio.h>

/* how deep can we nest expressions (((( ... )))) */
#define SNOOK_MAX_EXPR_NESTING_DEPTH  8
/* how large can a single source language token get (in octets) */
#define SNOOK_MAX_TOKEN_SIZE         64

#define NIL NULL

typedef enum {
	TRUE_T,     /* boolean true  */
	FALSE_T,    /* boolean false */
	FIXNUM_T,
	SYM_T,      /* a symbol */
	CONS_T,
} type_t;

typedef struct __cons  *cons_t;
typedef struct __sym   *sym_t;
typedef struct __box   *box_t;

struct __box {
	type_t type;
	union {
		char     character;
		int      fixnum;
		float    float32;
		double   float64;
		sym_t    symbol;
		char    *string;
		cons_t   cons;
	} value;
};

struct __cons {
	box_t car;
	box_t cdr;
};

struct __sym {
	char *name;
};

struct __syment {
	sym_t            symbol;
	struct __syment *next;
};
typedef struct __symtab *symtab_t;
struct __symtab {
	struct __syment *first;
};

symtab_t
new_symbol_table();
sym_t
intern(symtab_t table, const char *name);
sym_t
lookup(symtab_t table, const char *name);

box_t box(type_t type);
box_t box_cons(cons_t c);
box_t box_fixnum(int x);
box_t box_sym(sym_t s);
cons_t unboxed_cons(box_t b);

cons_t cons(box_t a, box_t d);
box_t car(box_t c);
box_t cdr(box_t c);
void append(box_t *c, box_t a);

#define nil(b) ((b) == NIL)
#define atom(b) (!nil(b) && ((b)->type != CONS_T))
int proper(box_t b);

box_t reader (FILE *io, const char *name, symtab_t symbols);

int format(FILE *out, box_t s);

int verify(box_t s);

box_t eval(box_t expr, symtab_t env);

#endif
