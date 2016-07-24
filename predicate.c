#include "cc.h"

int
proper(box_t b)
{
	while (!nil(b)) {
		if (atom(b)) return 0;
		b = cdr(b);
	}
	return 1;
}
