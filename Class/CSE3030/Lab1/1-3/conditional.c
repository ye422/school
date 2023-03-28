#include "conditional.h"

/*
 * conditional(x, y, z): same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 */
int conditional(int x, int y, int z) {

	int result;
	int t_f;
	t_f = !x;
	t_f += 0xFF;
	result = (t_f & y) | ( ~t_f & z );
	

	return result;
}
