#include "head.h"

void print_line(int * each_number)
{
	int i;		//for 의 index i
	for(i=0;i< MAX; i++)		// i 는 0에서 9까지 증가
		printf("%d ", *(each_number + i));		// i번째 each_number, 즉 이때까지 사용된 숫자 i의 개수 출력
	printf("\n");		// 줄바꿈 출력
	

	return;
}
