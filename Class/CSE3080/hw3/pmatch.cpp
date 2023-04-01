#include <iostream>
#include <cstring>
#include <cstdlib>

using std::cin;
using std::cout;

char* pmatch(char * string, char *pat, int * failure);
void fail(char *pat, int * failure);
#define MAX 31

int main () 
{
	int i = 0;
	int j = 0;
	char base_str[MAX];	
	char pattern_str[MAX - 1];
	char * modified_str;
	int failure[MAX];

	while( cin.get(base_str[i]) )
	{	
		if ( i == MAX )
		{	
			cout << "Error, Too long input.\n";
			exit(1);		
		}

		if(base_str[i] == '\n')
			break;
  		i++;	
	}
	
		
	base_str[i] = '\0';
	
	if( i < 1) 
	{	cout << "No input!\n";
		exit(1);
	}
	while( cin.get(pattern_str[j]) )
	{	
		if ( j == i)
		{
			cout << "Error, pattern must be shorter than string.\n";
			exit(1);
		}
		if(pattern_str[j] == '\n')
			break;
  		j++;	
	}
	pattern_str[j] = '\0';

	if( j < 1) 
	{	
		cout << "No input!\n";
		exit(1);
	}

	fail(pattern_str, failure);
	modified_str = pmatch(base_str, pattern_str, failure);		
	int modlen = strlen(modified_str);
	for(int i =0; i < modlen; i++)
		cout << modified_str[i]; 	
	cout << "\n";
	return 0;
}

char* pmatch(char * string, char *pat, int * failure)
{
	int i = 0;
	int j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	int matched = 0;
	int cont_flag = 0;
	char* new_str = new char [MAX];
	while ( i < lens)
	{
		if (string[i] == pat[j])
		{
			i++;
			j++;
			matched++;
			cont_flag = 1;
		}
		else if ( j == 0) 
		{
			i++;
			cont_flag = 0;
		}
		else 
		{
			j = failure[j-1] + 1;
			cont_flag = 0;
		}
	
 		if ( matched  == lenp )
		{
			for(int k = i - matched; k < i; k++)
				string[k] = ' ';
			j = 0;
			matched = 0;
		}
	
		else if ( cont_flag == 0 && matched > 1)
		{	
			for(int k = i - matched; k < i; k++)
				string[k]= ' ';
			j = 0;
			matched = 0;		 
		}
		else if ( cont_flag == 0 && matched <= 1)
			matched = 0;
	}	

	int idx = 0;
	for(int i = 0; i < lens; i++)
	{
		if( string[i] != ' ')
		{
			new_str[idx] = string[i];
			idx++;
		}
	}
	new_str[idx] = '\0';
	return new_str;
}

void fail (char *pat, int * failure)
{
	int i, j;
	int n = strlen(pat);
	failure[0] = -1;
	for (j = 1; j < n; j++)
	{
		i = failure[j-1];
		while((pat[j] != pat[i+1]) && (i >= 0) )
			i = failure[i];
		if (pat[j] == pat[i+1] )
			failure[j] = i+1;
		else 
			failure[j] = -1;
	}  
}




