#include "conditional.h"
/*
 * conditional(x, y, z): same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 */
int conditional(int x, int y, int z) {

	int result;
	int t_f = !x;
	int mask = 0xFF << 8;
	mask += 0xFF;
	t_f += mask;
	result = (t_f & y) | ( ~t_f & z );
	return result;
}
