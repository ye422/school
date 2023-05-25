#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;
	createRankList();
	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_REC: recommendPlay = 1; recommendedPlay(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}
	writeRankFile();
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
	for(i=0; i<VISIBLE_BLOCK;i++)
		nextBlock[i]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;	
	modified_recommend(root);
	DrawOutline();
	DrawField();
	if ( recommendPlay = 1) {
		DrawBlock(blockY, blockX, nextBlock[0], blockRotate, ' ');
		DrawRecommend(blockY,blockX, nextBlock[0],blockRotate);
	}
	else DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate, tile);
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

	//move(9,WIDTH+10);
	DrawBox(9,WIDTH+10,4,8);

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
		move(10+i,WIDTH+13);
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
	if (tile != '.')
		DrawRecommend(y,x, blockID,blockRotate);
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
			newRank(score);
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

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){

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
				recommend(root);
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
					f[k][l] = f[k - 1][l];
					
			for( m =0; m< WIDTH;m++)
				f[0][m] = 0;
		} 	
	}
	return deleted_line * deleted_line * 100;
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID, int blockRotate, char tile)
{
	int shadow_y = 0;
	shadow_y = y;
	int drop_flag = 0;
	int draw_flag = 0; 
	int i,j;

	while( !drop_flag )
	{
		if( !CheckToMove(field, blockID, blockRotate, shadow_y + 1,x) )
		{
			draw_flag = 1;
			drop_flag = 1;
		}
		else shadow_y++;
	}

	if ( y < shadow_y )
		DrawBlock(shadow_y, x, blockID, blockRotate, tile);
}


void createRankList(){
	// 목적: Input파일인 "rank.txt"에서 랭킹 정보를 읽어들임, 읽어들인 정보로 랭킹 목록 생성
	// 1. "rank.txt"열기
	// 2. 파일에서 랭킹정보 읽어오기
	// 3. LinkedList로 저장
	// 4. 파일 닫기
	FILE *fp;
	int i, j;
	int tempval;
	int temp_score;
	char temp_char[NAMELEN+1];
	//1. 파일 열기
	fp = fopen("rank.txt", "r");
	if(fp == NULL )
		fp = fopen("rank.txt", "w");
	// 2. 정보읽어오기
	/* int fscanf(FILE* stream, const char* format, ...);
	stream:데이터를 읽어올 스트림의 FILE 객체를 가리키는 파일포인터
	format: 형식지정자 등등
	변수의 주소: 포인터
	return: 성공할 경우, fscanf 함수는 읽어들인 데이터의 수를 리턴, 실패하면 EOF리턴 */
	// EOF(End Of File): 실제로 이 값은 -1을 나타냄, EOF가 나타날때까지 입력받아오는 if문
	if (fscanf(fp, "%d", &tempval ) != EOF) {
		
		if (tempval > 0)
			score_number = tempval;
		for(i=0; i < score_number; i++)
		{
			fscanf(fp, "%s", temp_char);
			fscanf(fp, "%d", &temp_score);
			CreateNode(temp_score, temp_char);
		}
	}
	else 
		score_number = 0;
	
	// 4. 파일닫기
	fclose(fp);
}

void CreateNode(int temp_score, char temp_char[NAMELEN])
{
	
	RankNode* newnode = (RankNode*)malloc(sizeof(RankNode));
	RankNode* current_node = Head;
	strcpy( newnode->rank_name, temp_char );
	newnode->rank_score = temp_score;
	newnode->link = NULL;
	
	if (Head == NULL)
		Head = newnode;
	else 
	{
		if( current_node-> rank_score < temp_score )
		{
			newnode->link = current_node;
			Head = newnode;
		}
		else 
		{
			while ( current_node->link != NULL && current_node->rank_score > temp_score )
			{
				if ( (current_node->link)->rank_score <= temp_score )
				{
					newnode->link = current_node->link;
					current_node->link = newnode;
					return;
				}
				current_node = current_node -> link;
			}
			
			if ( current_node-> link == NULL)
				current_node->link = newnode;
			else 
			{
				newnode->link = current_node->link;
				current_node->link = newnode;
			}	
		}
	}
	
}

void DeleteNode(int rank)
{

	RankNode * current_node = Head;
	RankNode * prev_node = NULL;

	int i;
	int error_flag = 0;
	score_number--;
	modified = 1;
	if (rank == 1)
	{
		Head = current_node->link;
		current_node->link = NULL;
	}
	else
	{
		for (i=1; i<rank; i++)
		{
			prev_node = current_node;
			current_node = current_node->link;
			if ( current_node == NULL )
				error_flag = 1;
		}
		if ( error_flag )
			printw("Can'root->c Delete Rank; Invaild Rank");
		else
		{
			prev_node->link = current_node->link;
			current_node->link = NULL;
		}
	}
	free(current_node);
}

void PrintNode(int rank, int mod, FILE* output)
{
	int i;
	RankNode* current_node = Head;
	if(mod)
	{
		if(rank == 1)
		{	
			printw("%-18s",current_node->rank_name);
			printw("| ");
			printw("%d\n", current_node->rank_score);
		}
		else
		{
			for(i=0; i< rank - 1; i++)
				current_node = current_node -> link;
			printw("%-18s",current_node->rank_name);
			printw("| ");
			printw("%d\n", current_node->rank_score);
		}
	}
	else 
	{
		if(rank == 1)
		{	
			fprintf(output, "%s ",current_node->rank_name);
			fprintf( output, "%d\n", current_node->rank_score);
		}
		
		else
		{
			for(i=0; i< rank - 1; i++)
				current_node = current_node -> link;
			fprintf(output, "%s ",current_node->rank_name);
			fprintf(output,"%d\n", current_node->rank_score);
		}
	}
}


void rank(){
	//목적: rank 메뉴를 출력하고 점수 순으로 X부터~Y까지 출력함
	//1. 문자열 초기화
	int blockX=1, blockY=score_number;
	char ch;
	char tempx, tempy;
	int i, j;
	clear();

	//2. printw()로 3개의 메뉴출력	
	printw("1. list rank from X to Y\n");
	printw("2. list ranks by specific name\n");
	printw("3. delete specific rank\n");

	//3. wgetch()를 사용하여 변수 ch에 입력받은 메뉴번호 저장
	ch = wgetch(stdscr);
	//4. 각 메뉴에 따라 입력받을 값을 변수에 저장
	//4-1. 메뉴1: blockX, Y를 입력받고 적절한 input인지 확인 후(blockX<=blockY), X와 Y사이의 rank 출력
	if (ch == '1') 
	{
		echo();
		printw("X: ");
		scanw("%d",&blockX);
		printw("Y: ");
		scanw("%d",&blockY);
		noecho();

		if ( blockX <= 0 || blockY <= 0) {
			printw("Search failure : no rank\n");
			return;
		}

		else if ( blockX > score_number || blockY > score_number) {
			printw("Search failure : no rank\n");
			return;
		}

		if ( blockX <= blockY )
		{
			printw("%11s%8c%8s\n","name",'|',"score");
			printw("------------------------------\n");
			for(i = blockX; i < blockY + 1;i++)
				PrintNode(i,1,NULL);
		}
		else 
			printw("Search failure : no rank\n");
	}

	//4-2. 메뉴2: 문자열을 받아 저장된 이름과 비교하고 이름에 해당하는 리스트를 출력
	else if ( ch == '2') {
		char str[NAMELEN+1];
		int check = 0;
		RankNode * finder = Head;

		echo();
		printw("Input the name: ");
		getstr(str);
		noecho();
		printw("%11s%8c%8s\n","name",'|',"score");
		printw("------------------------------\n");
		while( finder != NULL )
		{
			if ( !strcmp(finder->rank_name, str) )
			{
				check = 1;
				printw("%-18s", finder->rank_name );
				printw("%c ",'|');
				printw("%d\n", finder->rank_score);
			}
			finder = finder -> link;
		}
		if (!check)
			printw("search failure: no name in the list\n");

	}

	//4-3. 메뉴3: rank번호를 입력받아 리스트에서 삭제
	else if ( ch == '3') 
	{
		int num;
		printw("Input the rank: ");
		echo();
		scanw("%d",&num);
		noecho();
		if( num <= score_number && num > 0 )
		{
			DeleteNode(num);
			printw("result: the rank deleted\n");
		}
		else printw("search failure: the rank not in the list\n");
	}
	getch();

}

void writeRankFile(){
	// 목적: 추가된 랭킹 정보가 있으면 새로운 정보를 "rank.txt"에 쓰고 없으면 종료
	int sn, i;
	//1. "rank.txt" 연다
	if (modified)
	{	

		FILE *fp = fopen("rank.txt", "w");

		//2. 랭킹 정보들의 수를 "rank.txt"에 기록s
		if ( fp == NULL )
		{
			printw("Error!\n");
			exit(1);
		}
	
		else 
		{
			fprintf(fp, "%d\n", score_number);
			for(i=1; i< score_number + 1; i++)
				PrintNode(i,0,fp);
			fclose(fp);
		}
		
	}
	for ( i= 1; i < score_number+1 ; i++) DeleteNode(1);
}

void newRank(int score){
	// 목적: GameOver시 호출되어 사용자 이름을 입력받고 score와 함께 리스트의 적절한 위치에 저장
	char str[NAMELEN+1];
	int i, j;
	modified = 1;
	clear();
	//1. 사용자 이름을 입력받음
	echo();
	printw("Your Name: ");
	getstr(str);
	noecho();
	//2. 새로운 노드를 생성해 이름과 점수를 저장, score_number가
	if (strlen(str) != 0)
	{	
		CreateNode(score, str);
		score_number++;
	}
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
	//if(CheckToMove(field, nextBlock[0], recommendR, recommendY, recommendX)) 
	DrawBlock(recommendY, recommendX, nextBlock[0], recommendR, 'R');
}


int recommend(RecNode *root){
	int max = 0; 
	int i, j = 0, r, h, w, temp_score, temp_y;
	int start_x, end_x;
	int rec_flag = 0, blockX, blockY, blockR;
	
	if (root == NULL) {
		root = (RecNode *)malloc(sizeof(RecNode));
		root->score = 0;
		root->lv = -1;
		root->f = (char (*)[WIDTH])malloc(sizeof(char) * HEIGHT * WIDTH);
		for(j=0;j< HEIGHT;j++)
			for(i=0;i<WIDTH;i++)
				root->f[j][i] = field[j][i];
	}

	int lv = root->lv + 1;

	root->c = (RecNode**)malloc(sizeof(RecNode*)*CHILDREN_MAX);

	j = 0;

	for(r = 0; r < NUM_OF_ROTATE ;r++) {

		start_x = 3;
		for(h = 0;h < 4;h++){
			for(w = 0;w < 4;w++) {
				if(block[nextBlock[lv]][r][h][w])
					break;
			}
			if(w < start_x)
				start_x = w;
		}
		start_x = 0 - start_x;

		end_x = 0;
		for(h = 0;h < 4;h++) {
			for(w = 3;w >= 0;w--) {
				if(block[nextBlock[lv]][r][h][w])
					break;
			}
			if(w > end_x)
				end_x = w;
		}
		end_x = WIDTH - end_x - 1;
		
		for(i = start_x;i < end_x + 1;i++) {
			root->c[j] = (RecNode*)malloc(sizeof(RecNode));
			root->c[j]->f = (char (*)[WIDTH])malloc(sizeof(char) * HEIGHT * WIDTH);
			for(h = 0;h < HEIGHT;h++){
				for(w = 0;w < WIDTH;w++)
					root->c[j]->f[h][w] = root->f[h][w];
			}
			root->c[j]->lv = lv;
			temp_y = -1; 
			
			while(CheckToMove(root->c[j]->f, nextBlock[lv], r, temp_y, i)) temp_y++;
			temp_y--;
			
			root->c[j]->score = root->score;
		   	root->c[j]->score += AddBlockToField(root->c[j]->f, nextBlock[lv], r, temp_y, i);
			root->c[j]->score += DeleteLine(root->c[j]->f);
			
			if(lv < VISIBLE_BLOCK - 1)
				temp_score = recommend(root->c[j]);
			else temp_score = root->c[j]->score;

			if(max < temp_score )
			{
				rec_flag = 1;
				blockX = i;
				blockY = temp_y;
				blockR = r;
				max = temp_score;
			}
			//free(root->c[j]->f);
			free(root->c[j]);
			j++;
		}
	}
	
	if(!lv && rec_flag) {

		recommendR = blockR;
		recommendX = blockX;
		recommendY = blockY;
		free(root);
		root = NULL;
	}
	
	return max;
}

int modified_recommend(RecNode * root) {
	int max = 0;
	
	int i, j, r, h, w, temp_score, temp_y=0;
	int k,m;
	int start_x, end_x;
	int rec_flag = 0, blockX, blockY, blockR=0;
	
	if (root == NULL) {
		root = (RecNode *)malloc(sizeof(RecNode));
		root->score = 0;
		root->weightedscore = 0;
		root->lv = -1;
		root->f = (char (*)[WIDTH])malloc(sizeof(char) * HEIGHT * WIDTH);
		for(j=0;j< HEIGHT;j++)
			for(i=0;i<WIDTH;i++)
				root->f[j][i] = field[j][i];
	}

	int lv = root->lv + 1;

	root->c = (RecNode**)malloc(sizeof(RecNode*)*CHILDREN_MAX);
	j=0;
	for(r = 0; r < NUM_OF_ROTATE ;r++) {

		start_x = 3;
		for(h = 0;h < 4;h++){
			for(w = 0;w < 4;w++) {
				if(block[nextBlock[lv]][r][h][w])
					break;
			}
			if(w < start_x)
				start_x = w;
		}
		start_x = 0 - start_x;

		end_x = 0;
		for(h = 0;h < 4;h++) {
			for(w = 3;w >= 0;w--) {
				if(block[nextBlock[lv]][r][h][w])
					break;
			}
			if(w > end_x)
				end_x = w;
		}
		end_x = WIDTH - end_x - 1;
		
		for(i = start_x; i < end_x + 1; i++) {
			root->c[j] = (RecNode*)malloc(sizeof(RecNode));
			root->c[j]->f = (char (*)[WIDTH])malloc(sizeof(char) * HEIGHT * WIDTH);
			for(h = 0;h < HEIGHT;h++){
				for(w = 0;w < WIDTH;w++)
					root->c[j]->f[h][w] = root->f[h][w];
			}
			root->c[j]->lv = lv;
			temp_y = -1; 
			while(CheckToMove(root->f, nextBlock[lv], r, temp_y, i)) temp_y++;
			temp_y--;
			

			root->c[j]->weightedscore = root->weightedscore; 
			
			int addscore = AddBlockToField(root->c[j]->f, nextBlock[lv], r, temp_y, i);
			int deletescore = DeleteLine(root->c[j]->f);
			root->c[j]->score += addscore;
			root->c[j]->weightedscore += addscore; 
			root->c[j]->score += deletescore;
			root->c[j]->weightedscore += 100 * deletescore;
			root->c[j]->weightedscore += evaluateField(root->c[j]->f); 
			root->c[j]->score = root->score;
		   	
			
			
			scorearr[j] = root->c[j]->weightedscore;
	 		root->c[j]->rblockRot = r;
			root->c[j]->rblockX = i;
			root->c[j]->rblockY = temp_y;
			j++;
		}
	}

	int cnt = j;
	k = 0;
	int idx[TEST_NUM] = {0,};
	quicksort(scorearr, 0, cnt - 1);
	for(k=0; k<TEST_NUM;k++)
	{
		m = 0;
		while( m < cnt)
		{
			if( scorearr[k] == root->c[m]->weightedscore) 		
			{	
				if ( k > 0 ) {
					if (idx[k-1] == m ) m++;
					else idx[k] = m;
				}
				else {
					idx[k] = m;
				}
			}
			m++;
		}	
	}

	for(k=0; k<TEST_NUM;k++) 	
	{	if(lv < VISIBLE_BLOCK - 1)
			temp_score = modified_recommend(root->c[idx[k]]);

		else temp_score = root->c[idx[k]]->weightedscore;

		if(max < temp_score )
		{
			rec_flag = 1;
			blockX = root->c[idx[k]]->rblockX;
			blockY = root->c[idx[k]]->rblockY;
			blockR = root->c[idx[k]]->rblockRot;
			max = temp_score;
		}
		else if (max == temp_score && root->c[idx[k]]->rblockY > blockY)
		{
			rec_flag = 1;
			blockX = root->c[idx[k]]->rblockX;
			blockY = root->c[idx[k]]->rblockY;
			blockR = root->c[idx[k]]->rblockRot;
		}
	}

	if(!lv && rec_flag) {

		recommendR = blockR;
		recommendX = blockX;
		recommendY = blockY;
		datasize = evalSize(root);
		//free(root);
		root = NULL;
	}
	
	return max;
}


void recommendedPlay(){
	clear();
	time_t start = clock();
	act.sa_handler = recommendBlockDown;
	sigaction(SIGALRM, &act, &oact);
	InitTetris();

	double end;
	int command;
	
	do{
		//datasize = evalSize(root);
		end = ((double)(clock() - start) / CLOCKS_PER_SEC);
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}
		command = wgetch(stdscr);
		switch(command){
			case 'q':
				command = QUIT;
				gameOver = 1;
				break;
			case 'Q':
				command = QUIT;
				gameOver = 1;
				break;
			default:
				command = NOTHING;
				break;
		}

	}while(!gameOver);

	alarm(0);
	DrawBox(HEIGHT / 2 - 1, WIDTH / 2 - 5, 1, 10);
	move(HEIGHT / 2, WIDTH / 2 - 4);
	printw("Good-bye!!");
	getch();
	exit_rec(end,datasize);
	recommendPlay = 0;
}

void recommendBlockDown(int sig){
	int i;
	blockX = recommendX;
	blockY = recommendY;
	blockRotate = recommendR;
	
	if( recommendY < -1)
		gameOver = TRUE;
	else
	{
		score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		score += DeleteLine(field);

		for (i=0; i<VISIBLE_BLOCK-1; i++)
			nextBlock[i] = nextBlock[i+1];
		nextBlock[VISIBLE_BLOCK-1] = rand()%7;
		
		modified_recommend(root);
		blockY = -1;
		blockX = WIDTH/2-2;
		blockRotate = 0;
		
		DrawNextBlock(nextBlock);
		PrintScore(score);
	}
	DrawField();
	DrawBlock(blockY, blockX, nextBlock[0], blockRotate, ' ');
	DrawRecommend(blockY,blockX, nextBlock[0],blockRotate);
	timed_out = 0;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] >= pivot) {  
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quicksort(int arr[], int low, int high) {
    if (low < high) {
   
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

int evaluateField(char (*field)[WIDTH] ) {
	int h,w,i,j;
	int wscore = 0;
	int blockcount = 0;
	int wall = 0;	
	int check_flag;
	int deleted_line = 0;
	int baseline = 0;
	int blank = 0;
	int top = 0;
	for (h=HEIGHT - 1 ;h >= 0; h--) {
		for(w=0; w<WIDTH;w++)
		{
			if ( field[h][w] == 1) 
				blockcount++;	
			
			if ( field[h][w] == 1 && ( w == 0 || w == WIDTH -1 ))
				wall++;
		
			if ( field[h][w] == 1 && h > HEIGHT - 2)
				baseline++;
			else if ( field[h][w] == 1 && (h < HEIGHT - 2 && h > HEIGHT/2 ) )
				blockcount++;
			else if ( field[h][w] == 1 && h < 5 )
				top++;
			if ( w > 0 && w < HEIGHT )
			{	
				if ( field[h][w] == 1 && field[h][w+1] == 0 && field[h][w-1]) {
					blank++;
				}
			}
		}	
	}
	wscore -= blank * 10;
	wscore -= top * 10;
	wscore += blockcount;
	wscore += baseline * 10;
	wscore += wall * 2;
	return wscore;
}

long evalSize(RecNode* head) {
	int i, result = 0;
	
	if (head == NULL) return 0;
	if ( head ->c == NULL) return sizeof(RecNode) + sizeof(int)*7 + sizeof(char (*)[WIDTH]);
	if (head->lv == VISIBLE_BLOCK - 2)
		return sizeof(RecNode) + sizeof(int)*7 + sizeof(char (*)[WIDTH]) + sizeof(RecNode**);
	else  {
		for (i=0; i<CHILDREN_MAX; i++) 
			result += evalSize(head->c[i]);
	}
	return result + sizeof(RecNode) + sizeof(int)*7 + sizeof(char (*)[WIDTH]) + sizeof(RecNode**);
	
}

void exit_rec(double end, long datasize) {
	clear();
	printw("Time\n");
	printw("%7.3lf\n", end);
	//DrawBox(21, WIDTH + 10, 1, 8);
	printw("Score | Time\n");
	printw("%7.0lf\n", (double)score / end); 
	printw("Data | Time\n");
	printw("%3.0ld\n",  (long)(datasize / end));	
	getch();
}