#include <ncurses.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int menu();
char** createMaze(int);
void fill_maze(char**, int, int, int);
void random_maze(char**,int,int,int,int,int);
void print_maze(char**, int);
void delete_maze(char***,int);
void inobject(char**,int,int,int,int);

int main(int argc,char** argv){
	
	initscr();
	
	srand(time(0));

	int option=0;
	int const size=30;
	char** maze =NULL;
	maze=createMaze(size);
	int open=1+rand()%size;
	int close=1+rand()%size;
	int object=1+rand()%5;
	int wall=0;
	int wall2=0;
	int numbomb=0;
	
	do{
		option=menu();
		switch(option){
			case 1:{
				numbomb=1+rand()%6;
				fill_maze(maze,size,open,close);
				random_maze(maze,size,open,close,wall,wall2);
				inobject(maze,size,object,wall,wall2);
				
				print_maze(maze,size);
			}
			break;
		}
	}while(option<2);
	refresh();
	endwin();
	delete_maze(&maze,size);
	return 0;
}//end main

///////////////////////////////////////////Functions//////////////////////////////////////////////////////////

int menu(){
	int opt=0;
	printw("%s","-----Menu-----\n"
		    "1.Play Game (The Maze)\n"
		    "2.Exit\n");
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
	int wall=0;
	int wall2=0;
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
	maze[close][size-1]=' ';
}//fin fill_maze

void random_maze(char** maze,int size,int open,int close,int wall,int wall2){
	int a=0;
	for(int i=0;i<=size;i++){
		for(int j=0;j<=size;j++){
			
			if(a<350){
			wall=2+rand()%size;
			wall2=rand()%size;
			maze[wall2][wall]='|';
			a++;
			}
		}
	}
	maze[open][0]=' ';
	maze[close][size-1]=' ';
	maze[close][size-2]=' ';
	maze[close+1][size-2]=' ';
	maze[close-1][size-2]=' ';
}

void print_maze(char** maze, int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			printw("%c",maze[i][j]);
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
	for(int i=0;i<=size;i++){
		for(int j=0;j<=size;j++){
			if(counter<=object){
				wall=2+rand()%(size-2);
				wall2=2+rand()%(size-2);
				maze[wall][wall2]='?';
				counter++;
			}
		}
	}
}//fin inobject


