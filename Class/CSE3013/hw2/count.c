#include "head.h"

void count_number(int * n_array, int * each_number, int n_index)
{
	int i;		// for loop의 index i
	int add_index;		// 개수를 추가할 숫자를 임시로 저장하는 add_index 
	for(i=0; i< n_index ;i++)		// n_index 전까지 i++
	{
		add_index = *(n_array + i);		// n_array의 i번째 수를 add_index에 대입
		*(each_number + add_index) += 1; 		// each_number 의 add_index 번째 숫자를 1개 추가
	
	}	
	return;
}
