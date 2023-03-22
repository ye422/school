#include <stdio.h>
#include <stdlib.h>
#define MAX 10		// 0-9까지의 숫자를 다룰때 MAX 사용

int separate_number(int * n_array, int n);		// n을 자릿수별로 쪼개 n_array 배열에 저장
void count_number(int * n_array, int * each_number, int n_index); 		// 0에서 n_index 까지 n_array 배열을 검사해 각 자릿수의 숫자의 개수를 each_number 배열에 추가 
void print_line(int * each_number);		// each_number 배열 출력
