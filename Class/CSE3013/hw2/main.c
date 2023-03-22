#include "head.h"

int main()
{
	int j,i,n;		// for loop을 위한 index i,j 그리고 시행횟수 n
	scanf("%d",&n); 	// 시행횟수 n을 stdin으로 받아들인다
	
	int * target_num = (int*)malloc(n*sizeof(int));		// n 권에 페이지수를 저장할 배열 targer_num 을 동적할당
	int n_array[11];		//페이지 수를 자릿수별로 저장할 n_array[11] ( 1 <= N <= 1000000000 )
	int each_number[MAX] = {0,};		// 0~9 각 숫자의 개수를 저장할 배열 each_number
	int n_index;		// n_array 배열의 마지막 index를 가리키는 n_index

	for(i=0; i < n ; i++)
		scanf("%d", &target_num[i]);		// n번 만큼 페이지 수를 stdin으로 읽는다.

	for(i=0; i < n;i++)		// n번 만큼 반복		
	{
		for(j=1; j < target_num[i] + 1; j++)		// 1에서 페이지 수 까지 j 늘려가며 반복한다.
		{
			n_index = separate_number(n_array, j );		// n_index는 separte_number()로 j를 자릿수 별로 저장한 n_array의 마지막 index가 된다.    
			count_number(n_array, each_number, n_index);		// n_array에 n_index 까지 저장된 각 자릿수를 보고 each_number 배열 조정  
		}
		
    	print_line(each_number);		// each_number 배열 출력
		
		for(j=0; j<10;j++)		
			each_number[j] = 0;		// 다음 반복 이전 each_number 배열 초기화
	}

	free(target_num);		// 동적할당한 메모리 해제
	return 0;
}
