#include <iostream>

using std::cin;
using std::cout;

void go_down(int x, int y, int max_x, int max_y, int ** food ,int food_cnt);
void go_right(int x, int y, int max_x, int max_y,int ** food ,int food_cnt);

int MAX = 0;

int main()
{
	int n;
	
	cin >> n;
	int * x_size = new int [n] {};
	int * y_size = new int [n] {};
	int * result = new int [n];

	
	for(int i = 0; i < n;i++)
	{	
		int room_cnt = 0;
		cin >> y_size[i] >> x_size[i];
		if ( !y_size[i] || !x_size[i] )
		{
			cout << "Wrong Input.\n";
			return 0;
		}
		
		int ** food = new int * [ x_size[i] ];

		for(int k = 0; k < y_size[i] ; k++)
			food[k] = new int [ y_size[i] ];
	
		for(int k = 0; k < y_size[i]; k++)
			for(int j = 0; j < x_size[i]; j++)
				cin >> food[k][j];			
			
		go_down(0,0,y_size[i],x_size[i],food ,0 );
		go_right(0,0,y_size[i],x_size[i],food, 0);
		result[i] = MAX;
		MAX = 0;	

		for(int k = 0; k < y_size[i];k++)
			delete [] food[k];
		delete [] food;

	}

	for(int j = 0; j <n;j++)
		cout << result[j] << "\n";

	delete [] result;
	delete [] x_size;
	delete [] y_size;
	
	return 0;
}	
	

void go_down(int y,int x, int y_size, int x_size,int ** food,int food_cnt)
{
    food_cnt += food[y][x];

	if ( x == x_size - 1 && y == y_size - 1)
	{
		if( food_cnt > MAX) 
			MAX = food_cnt;
	}
	else if ( x < x_size &&  y == y_size - 1 ) 
		go_right( y, x + 1, y_size, x_size, food, food_cnt);

	else if ( y < y_size && x == x_size - 1 )
		go_down(y + 1, x, y_size, x_size,food ,food_cnt);
	else if ( y < y_size - 1 && x < x_size - 1 )
	{
		go_right( y, x + 1, y_size, x_size, food, food_cnt);
		go_down(y + 1, x, y_size, x_size,food ,food_cnt);
	}
}

void go_right(int y, int x, int y_size, int x_size,int ** food ,int food_cnt)
{
	food_cnt += food[y][x];
	if ( x == x_size - 1 && y == y_size - 1 )
	{
		
		if( food_cnt > MAX) 
			MAX = food_cnt;
	}
	else if ( x < x_size &&  y == y_size - 1 ) 
		go_right( y, x + 1, y_size, x_size, food, food_cnt);

	else if ( y < y_size && x == x_size - 1 )
		go_down(y + 1, x, y_size, x_size,food ,food_cnt);
	else if ( y < y_size - 1 && x < x_size - 1 )
	{
		go_right( y, x + 1, y_size, x_size, food, food_cnt);
		go_down(y + 1, x, y_size, x_size,food ,food_cnt);
	}
}
