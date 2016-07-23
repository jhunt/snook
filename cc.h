#ifndef SNOOK_CC_H
#define SNOOK_CC_H

#include <stdio.h>

/* how deep can we nest expressions (((( ... )))) */
#define SNOOK_MAX_EXPR_NESTING_DEPTH  8
/* how large can a single source language token get (in octets) */
#define SNOOK_MAX_TOKEN_SIZE         64

typedef enum {
	TRUE_T,     /* boolean true  */
	FALSE_T,    /* boolean false */
	FIXNUM_T,
	NIL_T,      /* nil */
	SYM_T,      /* a symbol */
	LIST_T,
	PROC_T,
	PRIMOP_T,   /* primitive operation */
} type_t;

typedef struct __sym *sym_t;
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

typedef struct __thing *thing_t;
typedef struct __sexpr *sexpr_t;

struct __thing {
	type_t type;
	union {
		char     character;
		int      fixnum;
		float    float32;
		double   float64;
		sym_t    symbol;
		char    *string;
		sexpr_t  list;
	} value;
};

struct __sexpr {
	int      length;
	thing_t *things;
};

sexpr_t
snook_read(FILE *io, const char *name, symtab_t symbols);

int
snook_write(FILE *out, sexpr_t s);

int
snook_verify(sexpr_t s);

#endif
