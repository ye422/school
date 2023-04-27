#include <iostream>

using std::cout;
using std::cin;

long long int count_num(int n, int s);
long long int ** memo;
int main()
{
	int n,s;
	long long int result;
	cin >> n >> s;
	
	try {
	if ( !cin )
		throw std::out_of_range("Not a integer ");
	else if ( n < 0 ) 
		throw std::out_of_range("Negative Number ");
	else if ( s < 0 )
		throw std::out_of_range("Negative Number ");
	}	
	catch (std::out_of_range& e)
	{
		cout << "Error. " << e.what() << "\n";
		exit(1);
	}

	memo = new long long int*[n+1];	

	for(int i =0; i <=n; i++)
		memo[i] = new long long int[s+1];

	for (int i=0; i <= n; i++)
		for( int j=0; j <=s;j++)
			memo[i][j] = -1;	

	result = count_num(n,s);
	cout << result << "\n";
	
	for(int i =0; i <= n;i++)
		delete [] memo[i];
	delete [] memo;

	return 0;
}


long long int count_num(int n,int s)
{
	long long int result;

	if (memo[n][s] != -1)
		result = memo[n][s];

	else if ( n == 1 || s == 0)
		result = 1;	

	else 
	{	result = 0; 
		for(int i =s; i >= 0; i--)
			result += count_num(n-1,i);
	}
	memo[n][s] =  result;

	return result;
}



