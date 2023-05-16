#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
const int MAZE_MAX = 30;

struct offsets {
    int vert;
    int horiz; 
};

struct element{
    int row;
    int col;
    int dir;
    element * prev;
    element * next;
};

void path(int **, int **, int &, int &);
void setmark(int **, int &, int &);
void printResult(int frow, int fcol, bool found);
void push(element & item);
element pop();

element * head = nullptr;
element * tail = nullptr;

offsets move[8] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };

int main()
{
    int row=10, col=10;
    int EXIT_ROW = 8;
    int EXIT_COL = 8;
    std::ifstream infile;
    infile.open("input.txt");   
    if (!infile) {
        std::cerr << "Error! Can't open file.\n";
        exit(1);
    }
    int ** maze = new int* [row];
    int ** mark = new int* [row];
    for(int i = 0; i < row; i++)
    {   
        maze[i] = new int[col];
        mark[i] = new int[col];
    }

    for(int i=0; i < row; i++)
        for(int j=0; j < col; j++)
            infile >> maze[i][j];
    

    setmark(mark,row,col);
    path(maze, mark, EXIT_ROW, EXIT_COL);
    for(int i =0; i < row; i++)
    {    
        delete [] maze[i];
        delete [] mark[i];
    }    
    delete [] maze;
    delete [] mark;
    infile.close();
    return 0;
}

void setmark(int** mark, int & row, int &col)
{
    for(int i =0; i < row ; i++)
        for(int j = 0; j < col; j++)
            mark[i][j] = 0;
    return;
}

void path(int **maze, int **mark, int & EXIT_ROW, int & EXIT_COL )
{
 	int i, row, col, nextRow, nextCol, dir;
    bool found = false;
	element position, initial;
	mark[1][1] = 1; 
	initial.row = 1; initial.col = 1; initial.dir = 1; 
    push(initial);
	while (head != nullptr && !found)  
    {
		position = pop();
		row = position.row;  col = position.col, dir = position.dir;  
		while (dir < 8 && !found)  
        {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
				found = true;
			else if  (!maze[nextRow][nextCol] && !mark [nextRow][nextCol])  	
            {
			  mark [nextRow][nextCol] = 1;
			  position.row = row;  position.col = col;
			  position.dir = ++dir;
			  push(position);
			  row = nextRow;  
              col = nextCol;  
              dir = 0;
			}
			else  ++dir;
        }
	}
    printResult(row,col, found);
        
}

void push(element& item)
{
    element * newelement = new element;

    newelement->dir = item.dir;
    newelement->row = item.row;
    newelement->col = item.col;
    newelement->prev = nullptr;
    newelement->next = nullptr;
    if (head == nullptr && tail == nullptr)
    {    
        tail = newelement;
        head = newelement;
    }
    else
    {
        newelement -> prev = tail;
        tail->next = newelement;
        tail = newelement;
    }
}

element pop()
{
    element result;
    if ( tail != nullptr)
    {    
        result.dir = tail->dir;
        result.col = tail->col;
        result.row = tail->row;
    }

    else 
    {
        cout << "Empty stack\n";
        result.dir = 0;
        result.col = 0;
        result.row = 0;
        return result;
    }
    element * temp = tail;
    if (tail == head) {
        head = nullptr;
        tail = nullptr;
    }

    else {
        tail = tail -> prev;
        tail->next = nullptr;
    }
    delete temp;
    
    return result;
}

void printResult(int frow, int fcol, bool found)
{
    int EXIT_ROW = 8;
    int EXIT_COL = 8;
    std::ofstream outfile("path.txt");

    if (outfile.fail())
    {
        std::cerr << "Error! Can't make path.txt";
        exit(2);
    }

    if (found) {
    element * temp = head;
	for( ; temp != nullptr; temp = temp -> next)
        outfile << temp->row << ' ' << temp->col << "\n";
	outfile << frow << ' ' << fcol << "\n";
	outfile << EXIT_ROW << ' ' << EXIT_COL << std::endl;
    }
	else  outfile << "경로를 찾을 수 없습니다!\n";
}