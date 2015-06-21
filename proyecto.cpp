#include <ncurses.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int menu();
char** createMaze(int);
void fill_maze(char**, int, int, int);
void random_maze(char**,int,int,int,int,int,int);
void print_maze(char**, int);
void delete_maze(char***,int);
void inobject(char**,int,int,int,int);
void finish(char**,int,int,int);

int main(int argc,char** argv){
	
	initscr();
	
	srand(time(0));

	start_color();
	init_pair(1,COLOR_BLUE,COLOR_BLACK);
	attron(COLOR_PAIR(1));
	int option=0;
	int const size=30;
	char** maze =NULL;
	maze=createMaze(size);
	int open=1+rand()%size;
	int close=1+rand()%size;
	int object=1+rand()%5;
	int wall=0;
	int wall2=0;
	int numbomb=1+rand()%3;
	bool lol=false;
	do{
		
		refresh();
		option=menu();
		clear();
		switch(option){
			case 1:{
				numbomb=1+rand()%6;
				fill_maze(maze,size,open,close);
				random_maze(maze,size,open,close,wall,wall2,numbomb);
				inobject(maze,size,object,wall,wall2);
				while(true){ 	
				print_maze(maze,size);
				finish(maze,size,object,close);
				}
			}
			break;
		}
	}while(option<2);
	attroff(COLOR_PAIR(1));
	refresh();
	endwin();
	delete_maze(&maze,size);
	return 0;
}//end main

///////////////////////////////////////////Functions//////////////////////////////////////////////////////////

int menu(){
	int opt=0;
	start_color();
	init_pair(1,COLOR_BLUE,COLOR_BLACK);
	attron(COLOR_PAIR(1));
	printw("%s","-----Menu-----\n"
		    "1.Play Game (The Maze)\n"
		    "2.Exit\n");
	attroff(COLOR_PAIR(1));
	scanw("%d",&opt);
	return opt;
}//fin menu

char** createMaze(int size){
	char** returnVal=NULL;
	returnVal=new char*[size];
	for(int i=0;i<size;i++){
		returnVal[i]=new char[size];
	}
	return returnVal;
}//fin createMaze

void fill_maze(char** maze, int size, int open, int close){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){

			if(i==0){
				maze[i][j]='|';
			}else if (i==size-1){
				maze[i][j]='|';	
			}else if(j==0){
				maze[i][j]='|';
			}else if(j==size-1){
				maze[i][j]='|';
			}else{
				maze[i][j]=' ';
			}
		}
	}
	maze[open][0]=' ';
	//maze[close][size-1]=' ';
}//fin fill_maze

void random_maze(char** maze,int size,int open,int close,int wall,int wall2,int numbomb){
	int conta=0;
	for(int i=1;i<size;i++){
		for(int j=1;j<size;j++){
	
			if(conta<250){
				wall=2+rand()%size;
				wall2=rand()%size;
				maze[wall2][wall]='|';
			
			if(numbomb!=0){
				maze[(wall2)][(wall)]='!';
				numbomb--;
			}			
				conta++;
			}
		}
	}
	maze[open][0]='M';
	
	maze[close+1][size-2]=' ';
	maze[close-1][size-2]=' ';
}//fin random_maze

void print_maze(char** maze, int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			//if(maze[i][j]!='!'){
				printw("%c",maze[i][j]);
			//}else{
			//	printw("%c",'|');
			//}
		}
		printw("\n");
	}
}//fin print_maze

void delete_maze(char*** maze, int size){
	for (int i = 0; i < size; i++){
		delete[] (*maze)[i];
	}
	delete[] *maze;
	*maze=NULL;
}//fin delete_maze

void inobject(char** maze ,int size,int object,int wall,int wall2){
	int counter=0;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(counter<=object){
				wall=2+rand()%(size-2);
				wall2=2+rand()%(size-2);
				maze[wall][wall2]='?';
				counter++;
			}
		}
	}
}//fin inobject

void finish(char** maze,int size,int object,int close){
	int col=0;
	int row=0;
	int move;
	int counter=0;
	bool live=true;
	int fin=0;
	int boomb=0;
	//do{
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if(maze[i][j]=='?'){
				counter++;
			}
			if(maze[i][j]=='M'){
				fin=1;
				col=i;
				row=j;
			}
		}
	}
	printw("%d='?'",counter);
	
	if(counter==0){
		maze[close][size-1]=' ';
		maze[close][size-2]=' ';
	}
	counter=0;
printw("%d",boomb);
	if(boomb==1){
		refresh();
		clear();
		live=false;
		printw("You Loose!!!");
	}
	if(fin==0){
		printw("You Win!!!!!");
	}
	//print_maze(maze,size);
	move=getch();
	do{
		switch(move){
		case 'D':{
			if(maze[col][row-1]=='|'){
				refresh();
				print_maze(maze,size);
				clear(); 
			}else if (maze[col][row-1]=='?'){
				maze[col][row]=' ';
				maze[col][row-1]='M';
				refresh();
				print_maze(maze,size);
				clear();
			}else if(maze[col][row-1]=='!'){
				boomb=1;
				live=false;
				clear();
			}else if(maze[col][row-1]==' '){
				maze[col][row]=' ';
				maze[col][row-1]='M';
				refresh();
				print_maze(maze,size);
				clear();
			}
		}
		break;
		case 'C':{
			if(maze[col][row+1]=='|'){
				refresh();
				print_maze(maze,size);
				clear(); 
			}else if (maze[col][row+1]=='?'){
				maze[col][row]=' ';
				maze[col][row+1]='M';
				refresh();
				print_maze(maze,size);
				clear();
			}else if(maze[col][row+1]=='!'){
				boomb=1;
				live=false;
				clear();
			}else if(maze[col][row+1]==' '){
				maze[col][row]=' ';
				maze[col][row+1]='M';
				refresh();
				print_maze(maze,size);
				clear();
			}
		}
		break;
		case 'A':{
			if(maze[col-1][row]=='|'){
				refresh();
				print_maze(maze,size);
				clear(); 
			}else if (maze[col-1][row]=='?'){
				maze[col][row]=' ';
				maze[col-1][row]='M';
				refresh();
				print_maze(maze,size);
				clear();
			}else if(maze[col-1][row]=='!'){
				boomb=1;
				live=false;
				clear();
			}else if(maze[col-1][row]==' '){
				maze[col][row]=' ';
				maze[col-1][row]='M';
				refresh();
				print_maze(maze,size);
				clear();
			}
		}
		break;
		case 'B':{
			if(maze[col+1][row]=='|'){
				refresh();
				print_maze(maze,size);
				clear(); 
			}else if (maze[col+1][row]=='?'){
				maze[col][row]=' ';
				maze[col+1][row]='M';
				refresh();
				print_maze(maze,size);
				clear();
			}else if(maze[col+1][row]=='!'){
				boomb=1;
				live=false;
				clear();
			}else if(maze[col+1][row]==' '){
				maze[col][row]=' ';
				maze[col+1][row]='M';
				refresh();
				print_maze(maze,size);
				clear();
			}
		}
		break;
		}			
	}while(live!=true);
}//fin finish