#include <iostream>

using std::cout;
using std::cin;

long long int count_num(int n, int s);

int main()
{
	int n,s;
	long long int result;
	cin >> n >> s; 
		
	result = count_num(n,s);
	cout << result << "\n";
	
	return 0;
}


long long int count_num(int n,int s)
{
	long long int result;
	if (n == 1 || s == 0) 
		result = 1;
	
	else
	{	result = 0; 
		for(int i =s; i >= 0; i--)
			result += count_num(n-1,i);
	}
	return result;
}



