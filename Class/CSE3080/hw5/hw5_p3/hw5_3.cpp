#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using std::cout;
using std::cin;

const int MAX_SIZE = 24;
const int NAMELEN = 20;

typedef struct node *node_pointer;
struct node {
		node_pointer link;
		char name[NAMELEN];

};

bool out[MAX_SIZE];
node *head[MAX_SIZE] = {nullptr, };

void friendnode(int idx, char name[NAMELEN]);
void name(int idx, char name[NAMELEN]);
void printnode(int idx, FILE* outfile);
void deleteNode(int idx, char name[NAMELEN]);
bool findNode(int idx, char name[NAMELEN]);
bool push(int & item);
int pop();
int stack[MAX_SIZE];
int stack_top = -1;
int stack_num = 0;


int main()
{
	int stk1 = 0;
	int stk2 = 0, stk3 =0;
	bool found_flag3 = false;
	bool found_flag1 = false;
	bool found_flag2 = false;
	bool exit_flag = true;
	char tempchar1[NAMELEN];
	char tempchar2[NAMELEN];
	char input = 'a';

	std::ifstream infile("input.txt");
	if(infile.fail()) {
		std::cerr << "Can't read file\n";
		exit(3);
	}

	FILE * outfile = fopen("output.txt", "w");
	if(fopen == nullptr) {
		std::cerr << "Can't open output file.\n";
		exit(4);
	}



	while(exit_flag) {
		infile >> input;
		switch(input) {
			case 'P' :
				infile >> tempchar1;
				name(stack_num, tempchar1);
				stack_num++;
				break;

			case 'F' :
				infile >> tempchar1 >> tempchar2;
				for(int i=0; i<stack_num; i++) {
					if ( !strcmp(head[i]->name, tempchar1)) {
						stk1 = i;
						found_flag1 = true;
						break;
					}
				}
				
				for(int i=0; i<stack_num; i++) {
					if ( !strcmp(head[i]->name, tempchar2)) {
						stk2 = i;
						found_flag2 = true;
						break;
					}
				}

				if (found_flag1 && found_flag2) {
					friendnode(stk1, tempchar2);
					friendnode(stk2, tempchar1);
				} else std::cerr << "Error! cant find name\n"; 
				break;

			case 'L' :
				infile >> tempchar1;
				for(int i=0; i<stack_num; i++) {
					if ( !strcmp(head[i]->name, tempchar1)) {
						stk3 = i;
						found_flag3 = true;
						break;
					}
				}
				if(found_flag3 == false ) std::cerr << "Error! cant find name\n";
				printnode(stk3, outfile);
				break;

			case 'U' :
				found_flag1 = false;
				found_flag2 = false;
				infile >> tempchar1 >> tempchar2;
				for(int i=0; i<stack_num; i++) {
					if ( !strcmp(head[i]->name, tempchar1)) {
						stk1 = i;
						found_flag1 = true;
						break;
					}
				}
				
				for(int i=0; i<stack_num; i++) {
					if ( !strcmp(head[i]->name, tempchar2)) {
						stk2 = i;
						found_flag2 = true;
						break;
					}
				}
				if (found_flag1 && found_flag2) {
					deleteNode(stk1, tempchar2);
					deleteNode(stk2, tempchar1);
				} else std::cerr << "Error! cant find name\n"; 
				break;	

			case 'Q' :
				found_flag1 = false;
				found_flag2 = false;
				infile >> tempchar1 >> tempchar2;
				for(int i=0; i<stack_num; i++) {
					if ( !strcmp(head[i]->name, tempchar1)) {
						stk1 = i;
						found_flag1 = true;
						break;
					}
				}
				
				for(int i=0; i<stack_num; i++) {
					if ( !strcmp(head[i]->name, tempchar2)) {
						stk2 = i;
						found_flag2 = true;
						break;
					}
				}
				if (found_flag1 && found_flag2) {
					if (findNode(stk1, tempchar2) || findNode(stk2, tempchar1) )
						fprintf(outfile, "Yes\n");
					else fprintf(outfile, "No\n");
				} else std::cerr << "Error! cant find name\n"; 
				break;	

			case 'X' :
			case 'x':
				exit_flag = false;
		}


	}
	return 0;
}

void name(int idx, char temp_name[NAMELEN])
{
	node * newnode = new node;
	strncpy(newnode ->name, temp_name, NAMELEN);
	if (head[idx] == nullptr)
	{
		head[idx] = newnode;
		head[idx]->link = nullptr;
	}
	else {	
		std::cerr << "Can't register name.\n";
		exit(1);
	}
}

void friendnode(int idx, char temp_name[NAMELEN])
{
	node * newnode = new node;
	strncpy(newnode ->name, temp_name, NAMELEN);
	 
	if ( head[idx] == nullptr) {
		std::cerr << "Empty stack.\n";
		exit(2);
	}
	else {
		newnode->link = head[idx]->link;
		head[idx]->link = newnode;
	}

}

void printnode(int idx, FILE * outfile)
{
	for(int i=0; i < stack_num; i++)
		out[i] = false;
	int temp = 0;
	bool cont_flag = true;
	bool name_change = false;
	node * finder;
	node * current = head[idx];
	if(current == nullptr)
		return;
	else {
		out[idx] = true;
		current = current -> link;
	}
	
	while ( current != nullptr ) {

		for(int i=0; i<stack_num; i++) {
			if ( !strcmp(head[i]->name, current->name)) {
				idx = i;
				break;
			}
		}
		if( !push(idx) ) { 
			std::cerr << "stack full\n"; 
			return; 
		}
		current = current -> link;		
	}

	while ( temp != -1 )
	{
		temp = pop();
		if ( !out[temp] && temp > -1 ) {
			fprintf(outfile, "%s ", head[temp]->name);
			out[temp] = true;
		}
	}

	fprintf(outfile, "\n");
}

void deleteNode(int idx, char name[NAMELEN])
{
	node * prev = head[idx];
	node * current;
	current = head[idx]->link;
	while ( current != nullptr && prev != nullptr)
	{	
		
		if ( !strcmp(current->name, name) )
		{
			prev->link = current ->link;
			current -> link = nullptr;
			delete current;
			return;	
		}
		else {
		prev = current;
		current = current -> link;
		}
	}
}

bool findNode(int idx, char name[NAMELEN])
{
	node * current = head[idx];
	bool result = false;
	while (current != nullptr )
	{
		if (!strcmp(current->name, name))
			result = true;
		current = current -> link;
	}
	return result;
}

bool push(int & item)
{
	if (stack_top == MAX_SIZE)
		return false;
	else {
		stack_top++;
		stack[stack_top] = item;
		return true;
	}
}

int pop(){
	int result = -1;
	if (stack_top == -1)
		return result;
	else {
		result = stack[stack_top]; 
		stack_top--;
		return result;
	}
}