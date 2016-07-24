#ifndef SNOOK_CC_H
#define SNOOK_CC_H

#include <stdio.h>

/* how deep can we nest expressions (((( ... )))) */
#define SNOOK_MAX_EXPR_NESTING_DEPTH  8
/* how large can a single source language token get (in octets) */
#define SNOOK_MAX_TOKEN_SIZE         64

#define NIL   ((box_t)0x0)
#define TRUE  ((box_t)0x01)
#define FALSE ((box_t)0x02)
#define BOOL(q) ((q) ? TRUE : FALSE)

typedef enum {
	FIXNUM_T,
	SYM_T,      /* a symbol */
	CONS_T,
} type_t;

typedef struct __sym   *sym_t;
typedef struct __box   *box_t;

struct __box {
	type_t type;
	union {
		int      fixnum;
		sym_t    symbol;
		box_t   *cons;
	} value;
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
box_t box_fixnum(int x);
box_t box_sym(sym_t s);

box_t cons(box_t a, box_t d);
box_t car(box_t c);
box_t cdr(box_t c);
void append(box_t *c, box_t a);

#define nil(b) ((b) == NIL)
#define atom(b) (!nil(b) && ((b)->type != CONS_T))
int proper(box_t b);
int sym(box_t b, symtab_t symbols, const char *name);

box_t reader (FILE *io, const char *name, symtab_t symbols);

int format(FILE *out, box_t s);

box_t eval(box_t expr, symtab_t env);

#endif
