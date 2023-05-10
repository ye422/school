#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;
	char tile = ' ';
	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate, tile);
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);

	move(9,WIDTH+10);
	DrawBox(10,WIDTH+10,4,8);

	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(16,WIDTH+10);
	printw("SCORE");
	DrawBox(17,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(18,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
	for( i = 0; i < 4; i++ ){
		move(11+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[2]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i = 0; i<4; i++)
		for(j = 0 ; j<4; j++){
			if( block[blockID][blockRotate][i][j] == 1 && i+y>=0 )
			{
				move(i+y+1,j+x+1);
				if(tile !='.')
					attron(A_REVERSE);
				printw("%c",tile);
				if (tile != '.')
					attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate, char tile)
{
	char shadow_tile = '/';
	if ( tile == '.')
		shadow_tile = '.';
	DrawShadow(y, x, blockID, blockRotate, shadow_tile);
	DrawBlock(y, x, blockID, blockRotate, tile);

}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT)
		{
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	} while (!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	/***********************************************************
 *	테트리스에서 command에 의해 바뀐 부분만 다시 그려준다.
 *	input	: (char[][]) command의해 바뀐 블럭을 확인할 필드
 *		  (int) 바뀌기 전 모양을 알기 위해 command를 입력으로 받는다.
 *		  (int) 현재 블럭의 모양 ID
 *		  (int) 블럭의 회전 횟수
 *		  (int) 블럭의 Y좌표
 *		  (int) 블럭의 X좌표
 *	return	: none
 ***********************************************************/
	int i,j;
	int result = 1;
	for(i=0; i< 4; i++)
	{
		for(j=0; j < 4;j++)
		{
			if( block[currentBlock][blockRotate][i][j] == 1)	
			{
				if ( blockY + i >= HEIGHT)
				{	
					result = 0;
					return result;
				}
				else if (blockX + j < 0 || blockX + j >= WIDTH)
				{
					result = 0;
					return result;
				}
				else if ( f[blockY + i][blockX + j] == 1)
				{	result = 0;
					return result;
				}
			}
		}
	}
	return result;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int i, j;
	int prev_Y = blockY;
	int prev_X = blockX;
	int prev_rotate = blockRotate;
	
	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
	//2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
	//3. 새로운 블록 정보를 그린다. 
	switch(command){
	case KEY_UP:
		prev_rotate = (blockRotate + 3)%4;
		break;
	case KEY_DOWN:
		

		prev_Y = blockY - 1;
		break;
	case KEY_RIGHT:
		
		prev_X = blockX - 1;
		break;
	case KEY_LEFT:
		
		prev_X = blockX + 1;
		break;
	default :
		break;
	}
	
	DrawBlockWithFeatures(prev_Y, prev_X, nextBlock[0], prev_rotate, '.');
	
	DrawBlockWithFeatures(blockY, blockX, nextBlock[0], blockRotate, ' ');
	move(HEIGHT + 3, WIDTH + 3);
}

void BlockDown(int sig){
	// user code

	//강의자료 p26-27의 플로우차트를 참고한다.
	
	if( CheckToMove(field, nextBlock[0], blockRotate, blockY + 1, blockX ) )
	{
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
	}
	else 
	{
		if( blockY == -1)
			gameOver = TRUE;
		else
		{
			score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
			score += DeleteLine(field);
			nextBlock[0] = nextBlock[1];
			nextBlock[1] = nextBlock[2];
			nextBlock[2] = rand()%7;
			blockY = -1;
			blockX = WIDTH/2-2;
			blockRotate = 0;
			DrawNextBlock(nextBlock);
			PrintScore(score);
		}
		DrawField();
	}
	timed_out = 0;
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code

	//Block이 추가된 영역의 필드값을 바꾼다.
	// 블록과 맞닿는 필드가 1이면 touched 늘린다.
	int i,j,k;
	int touched =0;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if( block[currentBlock][blockRotate][i][j] == 1)
			{	
				f[blockY + i][blockX + j] = 1;
				if ( f[blockY + i + 1][blockX + j] == 1 || blockY + i == HEIGHT - 1 )
					touched++;
			}
		}
	}
	return touched * 10;
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	// user code

	//1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
	//2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
	int i, j;
	int k,l,m;
	int check_flag;
	int deleted_line = 0;
	
	for(i=0; i < HEIGHT; i++)	
	{	
		check_flag = 1;
		for(j=0; j < WIDTH; j++)
		{
			if( f[i][j] == 0 )
				check_flag = 0;  
		}
		if ( check_flag )
		{
			deleted_line++;
			for(k = i; k > 0 ; k--)
				for(l = 0; l < WIDTH; l++)	
				{	
					f[k][l] = f[k - 1][l];
					
				}
			for( m =0; m< WIDTH;m++)
				f[0][l] = 0;

		} 	
	}
	
	
	return deleted_line * deleted_line * 100;
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID, int blockRotate, char tile)
{
	// user code
	int shadow_y = y;
	int drop_flag = 0;

	int draw_flag = 0; 
	int i,j;

	// y에서 height 까지 인덱스를 증가시키면서 checktomove를 한다.
	while( !drop_flag )
	{
		if( !CheckToMove(field, blockID, blockRotate, shadow_y + 1,x) )
		{
			draw_flag = 1;
			drop_flag = 1;
		}
		else shadow_y++;
	}
	//그래서 checktomove가 0이면 그 위치 1칸 아래에서 /로 블록을 그린다.
	//그림자가 지금 블록이랑 겹치면 안그린다. 
	
	if ( y < shadow_y )
		DrawBlock(shadow_y, x, blockID, blockRotate, tile);
}

void createRankList(){
	// user code
}

void rank(){
	// user code
}

void writeRankFile(){
	// user code
}

void newRank(int score){
	// user code
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
}

int recommend(RecNode *root){
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

	// user code

	return max;
}

void recommendedPlay(){
	// user code
}
