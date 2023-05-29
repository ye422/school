#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

int **maze;
int group = 1;
int max_height;

void makeMaze (int &n, int &m);
void printMaze(int &n, int &m);
void vertical(int &n, int &m);
void horizontal(int &n, int &m);
void merge(int &n, int &m);
void printcurrent(int & walls);
int min(int a, int b);

int main() {
    srand(time(NULL));
    int n,m;
    cin >> n >>m;
    max_height = 2*m+1;
    makeMaze(n,m);
    printMaze(n,m);
    for(int i=0; i<2*m+1;i++) 
        delete maze[i];
    delete [] maze;
    return 0;
}

void makeMaze(int &n, int &m) {
    int j=0;
    int walls_v = 2 * m + 1;
    int walls_h = 2 * n + 1;

    maze = new int*[walls_v];
    for(int i=0; i < walls_v;i++) {
        maze[i] = new int[walls_h];
    }
    
    for (int i=0; i<walls_v ; i++) {
        for (int j=0; j<walls_h;j++ ) 
            maze[i][j] = 0;
    }

    for (int i=0; i<walls_h; i++) {
        maze[0][i] = -1;
        maze[walls_v-1][i] = -1;
    }
    for (int i=1;i<walls_v-1; i++ ) {
        maze[i][0] = -1;
        maze[i][walls_h-1] = -1;
    }

    for(int i=0; i<m; i++) {     
        horizontal(n,i);
        if ( i != 0) merge(n,i);
        if ( i != m-1 ) vertical(n,i);   
    }

    /*for (int i=0; i<walls_v ; i++) {
        for (int j=0; j<walls_h;j++ ) {
            if (maze[i][j] > 1) maze[i][j] = 1;
        }
    }*/
}

void printMaze(int &n, int &m) {

    int walls_h = 2 * n + 1;
    int walls_v = 2 * m + 1;
    std::ofstream outfile;
    outfile.open("output.maz");

    for (int i=0; i<walls_v;i++) {
        for(int j=0; j<walls_h; j++) {
            if (maze[i][j] == -1 && ((i%2 == 0) && (j%2 == 0)) ) {
                outfile << '+';
            }
            else if (maze[i][j] == -1  && i%2 == 0 ) outfile << '-'; 
            else if (maze[i][j] < 0 && i%2 == 1) outfile << '|';
            else outfile << ' ';
        }
        outfile << '\n'; 
    }
        
}

void horizontal(int &n, int &m) {
    int walls = 2 * n + 1;
    int height = 2 * m + 1;
    
    if (height == 1) {
        for(int i=0; i<walls-1; i++) {
        
            if (i%2 == 1) {   
                maze[height][i] = group;
                group++;
            }
            else maze[height][i] = -1;
        }
    }
    else  {
        for (int i=0; i<walls; i++) {
            if (i%2 == 0) maze[height][i] = -1;
            else  {
                if( maze[height - 1][i] == 0) 
                    maze[height][i] = maze[height-2][i]; 
            }
        }
    }


    for(int i=0; i<walls-3; i++) {
        if ( i%2 == 1 ) {   
            if( maze[height][i] != maze[height][i+2] && height != max_height-2) {   
            
                if (rand()%2 == 1) {
                    maze[height][i+1] = 0;
                    maze[height][i+2] = min(maze[height][i], maze[height][i+2]);
                    maze[height][i] = min(maze[height][i],maze[height][i+2]); 
                }

                
            }
            else if (maze[height][i] == maze[height][i+2] && maze[height][i+1] == -1 && height != max_height - 2 ) {
                maze[height][i+1] = 0; 
            }
            else if( maze[height][i] != maze[height][i+2] && height == max_height - 2 ) {
                maze[height][i+1] = 0;
                maze[height][i+2] = min(maze[height][i],maze[height][i+2]);
                maze[height][i] = maze[height][i+2];
                merge(n,m);
            }
        }
    }
    
    for (int i=0; i<walls; i++) 
        maze[height+1][i] = -1;

}

void vertical(int &n, int &m) {
    
    int i = 1;
    int down = 0;
    int walls = 2*n+1;
    int height = 2*m + 1;
    bool double_flag = false;
    
    while (i < walls) {
        double_flag = true;
        if ( i > 1) {
            if ( maze[height][i] == maze[height][i-2] && maze[height+1][i-2] == 0 )
                double_flag = false;
        }    

        if ( maze[height][i] != maze[height][i+2] && down == 0 && double_flag) {
            maze[height + 1][i] = 0;
            if ( maze[height+2][i] == 0) maze[height + 2][i] = maze[height][i];
            else {
                maze[height+2][i] = min(maze[height+2][i],maze[height][i]);
                maze[height][i] = min(maze[height+2][i],maze[height][i]); 
            }
        }
        
        else if (double_flag) {
            if(rand()%2) {
                maze[height+1][i] = 0;
                if (maze[height+2][i] == 0)
                    maze[height + 2][i] = maze[height][i];
                else {
                    maze[height+2][i] = min(maze[height+2][i],maze[height][i]);
                    maze[height][i] = min(maze[height+2][i],maze[height][i]);
                }
                down = 1;
            }
        }   
        
        if ( maze[height][i] != maze[height][i+2] ) 
            down = 0;
        i = i+2;
    }

    for(int i=0; i<walls; i++) {

        if (i%2 == 1 && maze[height+1][i] < 0) 
        {    
            maze[height+2][i] = group;
            group++;
        }
        else if (i%2 == 0) maze[height+2][i] = -1;
    }

    
}

int min(int a, int b) {
    if (a > b ) return b;
    else return a;
}

void merge(int &n,int &m) {
    int width = 2*n+1;
    int height = 2*m+1;
    for(int i= height; i>1; i=i - 2) {
        for(int j=1; j<width-1; j=j+2) {
            if(maze[i-1][j] == 0 ) 
            {
                maze[i][j] = min (maze[i][j], maze[i-2][j]);
                maze[i-2][j] = maze[i][j];
            }
            else if (maze[i][j+1] == 0) {
                maze[i][j+2] = min(maze[i][j], maze[i][j+2]);
                maze[i][j] = maze[i][j+2];
            }
        }
    }
}

/*void printcurrent(int &walls) {
    for (int i=0; i<max_height ; i++) {
        for (int j=0; j<walls;j++ ) 
            cout << setw(2) << right << maze[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n'; 
}*/