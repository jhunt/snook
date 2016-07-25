#include "cc.h"
#include <stdlib.h>

static int INIT = 0;

static box_t
builtin_add(box_t a, box_t b)
{
	if (a == NIL || a == TRUE || a == FALSE
	 || b == NIL || b == TRUE || b == FALSE) {
		perror("add");
		abort();
	}

	if (a->type != b->type && a->type != FIXNUM_T) {
		perror("add");
		abort();
	}

	return box_fixnum(a->value.fixnum + b->value.fixnum);
}

static box_t
builtin_subtract(box_t a, box_t b)
{
	if (a == NIL || a == TRUE || a == FALSE
	 || b == NIL || b == TRUE || b == FALSE) {
		perror("subtract");
		abort();
	}

	if (a->type != b->type && a->type != FIXNUM_T) {
		perror("subtract");
		abort();
	}

	return box_fixnum(a->value.fixnum - b->value.fixnum);
}

static box_t
builtin_cmp_lt(box_t a, box_t b)
{
	if (a == NIL || a == TRUE || a == FALSE
	 || b == NIL || b == TRUE || b == FALSE) {
		perror("cmp_lt");
		abort();
	}

	if (a->type != b->type && a->type != FIXNUM_T) {
		perror("cmp_lt");
		abort();
	}

	return BOOL(a->value.fixnum < b->value.fixnum);
}

static box_t
builtin_cmp_gt(box_t a, box_t b)
{
	if (a == NIL || a == TRUE || a == FALSE
	 || b == NIL || b == TRUE || b == FALSE) {
		perror("cmp_gt");
		abort();
	}

	if (a->type != b->type && a->type != FIXNUM_T) {
		perror("cmp_gt");
		abort();
	}

	return BOOL(a->value.fixnum > b->value.fixnum);
}

static void
s_init(symtab_t env)
{
	sym_t s;

	s = intern(env, "+"); s->value = box_builtin(builtin_add);
	s = intern(env, "-"); s->value = box_builtin(builtin_subtract);

	s = intern(env, "<"); s->value = box_builtin(builtin_cmp_lt);
	s = intern(env, ">"); s->value = box_builtin(builtin_cmp_gt);

	INIT = 1;
}

box_t
eval(box_t expr, symtab_t env)
{
	box_t b;
	sym_t s;

	if (!INIT)
		s_init(env);

	if (expr == NIL || expr == TRUE || expr == FALSE)
		return expr;

	switch (expr->type) {
	case FIXNUM_T:
	case BUILTIN_T:
		return expr;

	case SYM_T:
		if (!expr->value.symbol->value)
			return expr;
		return expr->value.symbol->value;

	case CONS_T:
		/* special forms */
		if (sym(car(expr), env, "quote"))
			return cadr(expr);

		if (sym(car(expr), env, "atom"))
			return BOOL(atom(eval(cadr(expr), env)));

		if (sym(car(expr), env, "eq"))
			return BOOL(eq(
				eval(cadr(expr),  env),
				eval(caddr(expr), env)));

		if (sym(car(expr), env, "car"))
			return car(eval(cadr(expr), env));

		if (sym(car(expr), env, "cdr"))
			return cdr(eval(cadr((expr)), env));

		if (sym(car(expr), env, "cons"))
			return cons(
				eval(cadr(expr),  env),
				eval(caddr(expr), env));

		if (sym(car(expr), env, "cond")) {
			box_t rest;
			for (rest = cdr(expr); rest != NIL; rest = cdr(rest))
				if (eval(caar(rest), env) == TRUE)
					return eval(cadar(rest), env);
			return NIL;
		}

		/* symbol function dispatch */
		b = eval(car(expr), env);
		if (b != NIL && b->type == BUILTIN_T)
			return (*b->value.builtin)(
				eval(cadr(expr), env),
				eval(caddr(expr), env));

		if (b != NIL && b->type == SYM_T) {
			fprintf(stderr, "undefined function '%s'\n", b->value.symbol->name);
			return NIL;
		}

		perror("unfinished");
		abort();
	}
}
