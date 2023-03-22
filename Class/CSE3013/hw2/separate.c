#include "head.h"

int separate_number(int * n_array, int n)		// n_array의 주소와 반복횟수 분리할 숫자 n을 매개변수로 한다.
{
	int i = 0;		// n_array의 index i
	while(n > 0) 		// n 이 0보다 클때 while
	{
		*(n_array+i) = n%10;		// i번째 n_array에 n을 10으로 나눈 나머지 대입
		n = n/10;		//	n에 n/10 대입 (몫)
		i++; 			// i 1 증가
	}

	return i;		// 마지막 index i 리턴
}
