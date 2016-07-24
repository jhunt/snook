#include "cc.h"
#include <stdlib.h>

box_t
eval(box_t expr, symtab_t env)
{
	if (expr == NIL || expr == TRUE || expr == FALSE)
		return expr;

	switch (expr->type) {
	case FIXNUM_T:
		return expr;

	case SYM_T:
		return expr; /* FIXME */

	case CONS_T:
		/* special forms */
		if (sym(car(expr), env, "quote"))
			return car(cdr(expr));

		if (sym(car(expr), env, "atom"))
			return BOOL(atom(eval(car(cdr(expr)), env)));

		if (sym(car(expr), env, "eq"))
			return BOOL(
				eval(car(cdr(expr)),      env) ==
				eval(car(cdr(cdr(expr))), env));

		if (sym(car(expr), env, "car"))
			return car(eval(car(cdr(expr)), env));

		if (sym(car(expr), env, "cdr"))
			return cdr(eval(car(cdr(expr)), env));

		if (sym(car(expr), env, "cons"))
			return cons(
				eval(car(cdr(expr)),      env),
				eval(car(cdr(cdr(expr))), env));

		if (sym(car(expr), env, "cond")) {
			box_t rest = cdr(expr);
			while (rest != NIL)
				if (eval(car(car(rest)), env) == TRUE)
					return eval(car(cdr(car(rest))), env);
			return NIL;
		}

		/* symbol function dispatch */
		perror("unfinished");
		abort();
	}
}
