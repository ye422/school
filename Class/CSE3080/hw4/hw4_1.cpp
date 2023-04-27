#include <iostream>

using std::cout;
using std::cin;
const int STACK_SIZE = 100;
const int MAZE_MAX = 100;

struct offsets {
    int vert;
    int horiz; 
};

struct element{
    int row;
    int col;
    int dir;
};

void path(int **, int **, int &, int &);
void set(int ** , int **, int &, int &);
void push(element & item);
element pop();

element stack[STACK_SIZE];
offsets move[8] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };
int top;

int main()
{
    int n,m;    
    cin >> n >> m;
    if(n <= 0 || m <= 0 )
    {
        cout << "Invaild input\n";
        exit(1);
    }
    int EXIT_ROW = n;
    int EXIT_COL = m;
    int ** maze = new int* [n+2];
    int ** mark = new int* [n+2];
    for(int i = 0; i < n + 2; i++)
    {   
        maze[i] = new int[m+2];
        mark[i] = new int[m+2];
    }

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {    
            cin >> maze[i][j];
            if( maze[i][j] < 0)
            {
                cout << "Invaild input\n";
                exit(1);
            }
        }

    if(cin.fail())
    {
        cout << "Invaild input\n";
        exit(2);
    }
    set(maze,mark, n,m);
    path(maze, mark, EXIT_ROW, EXIT_COL);
    for(int i =0; i < n; i++)
    {    
        delete [] maze[i];
        delete [] mark[i];
    }    
    delete [] maze;
    delete [] mark;
    return 0;
}

void set(int **maze, int** mark, int & row, int & col)
{
    for(int i = 0; i <= row + 1; i++)
        for(int j = 0; j <= col + 1; j++)
        {
            if(i == 0 || i == row + 1)
                maze[i][j] = 1;
            if ( j == 0 || j == col + 1)
                maze[i][j] = 1;
        }    

    for(int i =0; i <= row + 1; i++)
        for(int j = 0; j <= col + 1; j++)
            mark[i][j] = 0;
    return;
}

void path(int **maze, int **mark, int & EXIT_ROW, int & EXIT_COL )
{
 	int i, row, col, nextRow, nextCol, dir;
    bool found = false;
	element position;
	mark[1][1] = 1;  top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1; 
	while (top > -1 && !found)  
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
	if (found)  
    {
		cout << "The path is\n";
		cout << "Row Col\n";
		for  (i = 0; i <= top; i++)
		      cout << stack[i].row << "    " << stack[i].col << "\n"; 
	 	cout << row << "    " << col << "\n";
	 	cout << EXIT_ROW << "    " << EXIT_COL << std::endl;
	}
	else  cout << "경로를 찾을 수 없습니다!\n";
}

void push(element& item)
{
    top++;
    stack[top].dir = item.dir;
    stack[top].row = item.row;
    stack[top].col = item.col;
    return;
}

element pop()
{
    element result;
    result.dir = stack[top].dir;
    result.col = stack[top].col;
    result.row = stack[top].row;
    top--; 
    return result;
}