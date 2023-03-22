#include <iostream>
#include <cmath>

using std::cin;
using std::cout;

inline int min(int a, int b){
	return a>b?b:a;
}

int tile_count(int N, int M, int MAX, int i);

int main()
{
	int MAX;
	int N,M,result = 0;
	cin >> N >> M;
	for (int i = 0; i < min(N,M); i++)
	{
		if ( pow(2,i) > min(N,M))
		{	
			MAX = i; 
			break;
		}
	}
	for (int i = 0; i < MAX; i++)
		result += tile_count(N,M,MAX,i);
		
	cout << result << "\n";

	return 0;
}

int tile_count(int N, int M, int MAX, int i)
{	
	//get area 2^i tile can cover
	int area = (N/(int)pow(2,i))*(M/(int)pow(2,i))*pow(2,2*i);

	if( i < MAX - 1 )
	{
		for (int j=i+1; j <MAX;j++)
		//	susbstract area occupied by bigger tile
			area -= tile_count(N,M,MAX,j) * pow(2,2*j);
	}	

	return area/pow(2,2*i);
}
