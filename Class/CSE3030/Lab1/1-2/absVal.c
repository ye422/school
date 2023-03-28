#include "absVal.h"

/*
 * absVal(x): return the absolute value of x
 *   Example: absVal(-1) = 1
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 */
int absVal(int x) {
	int sign = x >> (31);  
	
	x = sign + x;
	x = x ^ sign;
	
	return x;
}
