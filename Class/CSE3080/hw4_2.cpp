#include <iostream>

using std::cout;
using std::cin;

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence; 

void printToken(precedence token);
precedence getToken(char *symbol, char * expr ,int * n);
precedence pop(precedence *stack, int &top);
void push(precedence *stack, precedence item, int & top);
void postfix(precedence *stack, char * expr, int & top);

const int MAX_LEN = 100;

int main()
{
    int top = 0;
    precedence stack[MAX_LEN];
    char expression[MAX_LEN];
    cin.getline(expression, MAX_LEN - 1);

    postfix(stack, expression, top);
    return 0;
}


precedence getToken(char *symbol, char * expr ,int *n)
{
/*  get the next token, symbol is the character representation, which is returned, the token is represented by its enumerated value, which is returned in the function name  */
	*symbol = expr[(*n)++];
	switch  (*symbol)   {
		case '(' : return  lparen;
		case ')' : return  rparen;
		case '+' : return  plus;
		case '-' : return  minus;
		case '/' : return  divide;
		case '*' : return  times;
		case '%' : return  mod;
		case '\0' : return eos;
		default : return  operand;  /* no error checking, default is operand */
	 }
}

void postfix(precedence *stack, char * expr, int &top)
{
/*  output the postfix of the expression. The expression string, stack, and the top are global  */
	char symbol;
	int n = 0;
	precedence token;

    int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
	int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

	stack[0] = eos;
	for  (token = getToken(&symbol, expr ,&n); token != eos; token = getToken(&symbol, expr, &n))  
    {
		if (token == operand)
			cout << symbol;
		else if (token == rparen)  
        {
			/*  unstack tokens until left parenthesis  */
			while (stack[top] != lparen)
				printToken(pop(stack,top));
			pop(stack, top);  /* discard the left parenthesis  */
		}
        else 
        {
		   	while (isp[stack[top]] >= icp[token])
			 	printToken(pop(stack, top));
			push(stack, token, top);
		}
	}
	while ( (token = pop(stack, top)) != eos)
		printToken(token);
	cout << std::endl;
    return;
  }

void push(precedence * stack, precedence item ,int & top)
{
    if(top < MAX_LEN - 1)
        stack[++top] = item;

    else     
        cout << "Full"; 
    return;
}

precedence pop(precedence * stack, int & top )
{
    precedence result;
    if(top > -1)
    {
        result = stack[top];
        top--;
    }
    else result = eos;
    return result;
}

void printToken(precedence token)
{
    char result;
    switch (token)   
    {
		case plus : result = '+'; break;
		case minus : result = '-'; break;
		case divide : result = '/'; break;
		case times : result ='*'; break;
		case mod : result = '%'; break;
		case eos : result ='\0'; 
    }
    cout << result;
}