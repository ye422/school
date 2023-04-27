#include <iostream>
#include <cstring>
using std::cout;
using std::cin;

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand, negative } precedence; 

char printToken(precedence token);
precedence getToken(char *symbol, char * expr ,int * n, int & op_check);
precedence pop(precedence *stack, int &top);
int pop(int * stack_2, int & top);
void push(precedence *stack, precedence item, int & top);
void push(int * stack_2, int item, int & top);
void postfix(precedence *stack, char * expr, int & top, char * post_expr);
int eval(int *stack_2, char * post_expr, int & top);

const int MAX_LEN = 21;

int main()
{
    int top = 0;
    precedence stack[MAX_LEN];
	int stack_2[MAX_LEN];
    char expression[MAX_LEN];
    cin.getline(expression, MAX_LEN);
	char *postfix_expr = new char[strlen(expression)];
    postfix(stack, expression, top, postfix_expr);

	cout << "Postfix : ";
	for(int i = 0; i < strlen(expression); i++)
		cout << postfix_expr[i];
	cout << "\n" << "Result : " << eval(stack_2, postfix_expr, top) << "\n";

	delete [] postfix_expr;
    return 0;
}


precedence getToken(char *symbol, char * expr ,int *n, int & op_check)
{
	*symbol = expr[(*n)++];
	switch  (*symbol)   {
		case '(' : return lparen;
		case ')' : return rparen;
		case '+' : return plus;
		case '-' : 
				if(op_check == 1) return minus;
				else return negative;
		case '/' : return divide;
		case '*' : return times;
		case '%' : return mod;
		case '\0' : return eos;
		case '#' : return negative;
		default : return  operand;  
	 }
}

void postfix(precedence *stack, char * expr, int &top, char * post_expr)
{
	char symbol;
	int count = 0, n = 0;
	precedence token;
	int op_check = 0;
    int isp[] = {0, 19, 12, 12, 13, 13, 13, 0, 15};
	int icp[] = {20, 19, 12, 12, 13, 13, 13, 0, 15};

	stack[0] = eos;
	for  (token = getToken(&symbol, expr ,&n, op_check); token != eos; token = getToken(&symbol, expr, &n, op_check))  
    {
		if (token == operand)	
		{	
			post_expr[count++] = symbol;
			op_check = 1;
		}
		else if (token == rparen)  
        {
			while (stack[top] != lparen)
				post_expr[count++] = printToken(pop(stack,top));
			pop(stack, top); 
			op_check = 1;
		}
        else 
        {
		   	while (isp[stack[top]] >= icp[token])
			 	post_expr[count++] = printToken(pop(stack, top));
			push(stack, token, top);
			op_check = 0;
		}
	}
	while ( (token = pop(stack, top)) != eos)
		post_expr[count++] = printToken(token);
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

char printToken(precedence token)
{
    char result;
    switch (token)   
    {
		case plus : result = '+'; break;
		case minus : result = '-'; break;
		case divide : result = '/'; break;
		case times : result ='*'; break;
		case mod : result = '%'; break;
		case negative : result = '#'; break;
		case eos : result ='\0'; 
    }
    return result;
}

int eval(int *stack, char * post_expr, int & top)
{
	precedence token;
	char symbol;
	int op1, op2, set_op = 1;
	top = -1;
	int n = 0; 
	token = getToken(&symbol, post_expr ,&n, set_op);
	while (token != eos)	  
	{
		if (token == operand)
			push(stack, symbol - '0' , top);   
		else    {

			op2 = pop(stack, top);  
			op1 = pop(stack, top);
			switch (token)   {
				case plus : push(stack, op1+op2, top);	break;
				case minus : push(stack, op1-op2, top);	break;
				case times : push(stack, op1*op2, top);	break;
				case divide: push(stack, op1/op2, top);	break;
				case mod : push(stack,op1%op2, top); break;
				case negative :
					push(stack, op1, top); 
					push(stack, op2 * (-1), top);
			}
		}
		token = getToken(&symbol,post_expr ,&n, set_op);
	}
	return pop(stack, top);     
}

void push(int * stack, int item ,int & top)
{
    if(top < MAX_LEN - 1)
        stack[++top] = item;

    else     
        cout << "Full"; 
    return;
}

int pop(int * stack, int & top )
{
    int result;
    if(top > -1)
    {
        result = stack[top];
        top--;
    }
    else result = 0;
    return result;
}