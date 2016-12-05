#include <iostream>
#include <math.h>
#include <vector>
#include <stdbool.h>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include "Pacman.h"
#include <conio.h>
#include <Windows.h>
using namespace std;

int edibleCounter = 0;
int counter;
int live = 3;
int level = 1;
int direction = -1;
int score, ghostTimer;
bool gameOver = false;
bool leavegame = false;
bool validInput;
bool canDie = true;
bool ghostEdibleMode = false;
char input;

//CODES IN COMMENTS ARE FOR BUG TESTING ****KEEP****

/*
	Struct for Pac-Man that allows public access to 
	Player data	(location)
*/
	struct Player
	{
		int locationRow, locationCol, lives;
		double movementTimer;

	//Constructor sets spawn location for Pac-Man
		Player()
		{
			locationRow = 16;
			locationCol = 9;
		//lives = 3;
		}
	};

/*
	Method to generate fruit at random places on GameBoard.
	Generates random coordinates and checks if the location
	on the GameBoard is valid. Uses a loop to make sure a
	fruit spawns.
*/
	void generateFruit(){
		bool validLoc= false;
		while(validLoc == false){
			int locFruitRow = rand() % 22;
			int locFruitCol = rand() % 19;
			int element = GameBoard[locFruitRow][locFruitCol];
			if (element==WALL || element==PACMAN || element==INKY || element==PINKY || element==CLYDE  || element==BLINKY || element == SPECIAL_DOT){
				validLoc = false;
			}
		//Empty voids above and below tunnel
			else if((locFruitRow == 8 || locFruitRow == 12) && ((locFruitCol >= 0 && locFruitCol <= 2) || (locFruitCol >= 16 && locFruitCol <= 18))){
				validLoc = false;
			}
		//Safe space around ghost room
			else if (locFruitCol >= 5 && locFruitCol <= 13 && locFruitRow >= 7 && locFruitRow <= 13) {
				validLoc = false;
			}
			else{
				GameBoard[locFruitRow][locFruitCol] = FRUIT;
				validLoc = true;
			}
		}
	}


/*
	Method to move player to desired position on GameBoard and deal with score.
	Takes in Player, desired x coordinate, and desired y coordinate.
	If there is a wall or ghost, player cannot move there.
	If there is a dot or fruit, score is increased.
	If there is a special dot, score is increased and ghosts are made edible.
*/
	bool movePlayer(Player player, int x, int y)
	{
	int element = GameBoard[x][y];		//element at desired position in GameBoard

	if (element == WALL) {
		return false;
	}
	else if ((element == BLINKY) || (element == PINKY) || (element == INKY) || (element == CLYDE)) {
		return false;
	}
	else if (element == DOT) {
		score += 10;
	}
	else if (element == SPECIAL_DOT) {
		score += 50;
		ghostEdibleMode = true;
	}
	else if (element == FRUIT) {
		score += 100;
	}

	GameBoard[player.locationRow][player.locationCol] = EMPTY;   //current position in GameBoard becomes empty
	player.locationRow = x; player.locationCol = y;				 //changes player's position to desired position
	GameBoard[player.locationRow][player.locationCol] = PACMAN;  //desired position in GameBoard becomes player
	return true;
}


int solve(int starty, int startx, int endx, int endy, int boardold[22][19]) 
{
	int board[22][19];


	//1,1 3,1 1,20
	int temp=starty;
	starty=18-startx;
	startx=temp;

	//9,16 16,9
	temp=endy;
	endy=18-endx;
	endx=temp;

	for (int i = 0; i < 22; i++)
		for (int j = 0; j < 19; j++)
			if (boardold[i][j] > 0)
				board[i][j] = 1;
			else
				board[i][j] = 0;

			queue<int> Xloc;
			queue<int> Yloc;
			queue<int> Xdes;
			queue<int> Ydes;
	//vector<int> moves;
			int sizex=22;
			int sizey=19;
	//int startx=0;
	//int starty=0;
	//int endx=sizex-1;
	//int endy=sizey-1;
			int i;
			int j;
			int X;
			int Y;
	//int board[sizex][sizey];
			Xloc.push(startx);
			Yloc.push(starty);
			board[startx][starty]=2;
	//board[endx][endy]=9;
	/*
	for(int j=0; j<19; j++) {
		for(int i=0; i<22; i++) {
			if (i==endx && j==endy){
				cout<<"9 ";
			}else
				cout<<board[i][j]<<" ";
			}
		cout<<endl;
		}
	*/
		while(!Xloc.empty()){
			bool nott = true;
			X = Xloc.front();
			Xloc.pop();
			Y = Yloc.front();
			Yloc.pop();
		//left
		// cout<<X<<" "<<Y<<" ";
			if (X-1>=0 && board[X-1][Y]==1 )
			{
			//cout<<"got left ";
				board [X-1][Y] =board[X][Y]+1;
				if (!(X-1==endx && Y==endy)){
					Xloc.push(X-1);
					Yloc.push(Y);
				}
				nott = false;
			}
			//up
			if (Y-1>=0 && board[X][Y-1]==1){
				//cout<<"got up ";
				board [X][Y-1] =board[X][Y]+1;
				if (!(X==endx && Y-1==endy)){
					Xloc.push(X);
					Yloc.push(Y-1);
				}
				nott = false;
			}
			//right
			if (X+1<sizex && board[X+1][Y]==1){
				//cout<<"got right ";
				board [X+1][Y] =board[X][Y]+1;
				if (!(X+1==endx && Y==endy)){
					Xloc.push(X+1);
					Yloc.push(Y);
				}
				nott = false;
			}
			//down
			if (Y+1<sizey && board[X][Y+1]==1){
				board [X][Y+1] =board[X][Y]+1;
				//cout<<"got down ";
				if (!(X==endx && Y+1==endy)){
					//cout<<Y+1<<endl;
					Xloc.push(X);
					Yloc.push(Y+1);
				}
				nott = false;
			}
			//cout<<endl;
			if (nott){
				Xdes.push(X);
				Ydes.push(Y);
			}else{
				/*
				 for (i=0;i<sizex;i++){
				 for (j=0;j<sizey;j++)
				 cout<<board[j][i]<<" ";
				 cout<<endl;
				 }
				 cout<<endl;
				 */
				}
			// cout<< Xloc.front()<<" "<<Yloc.front()<<endl;

			}
		/*
		cout<<endl;
		for(int j=0; j<19; j++) {
			for(int i=0; i<22; i++) {
				if (board[i][j]<10){
					cout<< board[i][j]<<"  ";
				}else
				cout<<board[i][j]<<" ";
			}
			cout<<endl;
		}
		 cout<<endl;
	  
		 while (!Xdes.empty()){
			int XD = Xdes.front();
			Xdes.pop();
			int YD = Ydes.front();
			Ydes.pop();
			cout<<XD<<" "<<YD<<" "<<board[XD][YD]<<endl;
		}
		*/
		while (!Xdes.empty()){
			int XD = Xdes.front();
			Xdes.pop();
			int YD = Ydes.front();
			Ydes.pop();
			bool kill = true;
			//left
			if (XD-1>=0 && board[XD-1][YD]>board[XD][YD] ){
				kill=false;
			}
			//up
			if (YD-1>=0 && board[XD][YD-1]>board[XD][YD] ){
				kill=false;
			}
			//right
			if (XD+1<sizex && board[XD+1][YD]>board[XD][YD] ){
				kill=false;
			}
			//down
			if (YD+1<sizey && board[XD][YD+1]>board[XD][YD] ){
				kill=false;
			}
			if (!(XD==endx && YD==endy) ){
				if (kill){
				//cout<<XD<<" "<<YD<<" "<<board[XD][YD]<<endl;
					board[XD][YD]=0;
					
					if (XD-1>=0 && board[XD-1][YD]!=0){
						Xdes.push(XD-1);
						Ydes.push(YD);
					}
					if (YD-1>=0 && board[XD][YD-1]!=0){
						Xdes.push(XD);
						Ydes.push(YD-1);
					}
					if (XD+1<sizex && board[XD+1][YD]!=0){
						Xdes.push(XD+1);
						Ydes.push(YD);
					}
					if (YD+1<sizey && board[XD][YD+1]!=0){
						Xdes.push(XD);
						Ydes.push(YD+1);
					}
				}
			}
			/*
			for(int j=0; j<19; j++) {
				for(int i=0; i<22; i++) {
					if (board[i][j]<10){
					cout<< board[i][j]<<"  ";
					}else
						cout<<board[i][j]<<" ";
				}
				cout<<endl;
			}
			Sleep(250);
			system("cls");
		
		}
				for(int j=0; j<19; j++) {
			for(int i=0; i<22; i++) {
				if (board[i][j]<10){
					cout<< board[i][j]<<"  ";
				}else
				cout<<board[i][j]<<" ";
			}
			cout<<endl;
		*/

		}

		vector <int>moves ;
		int curx=startx;
		int cury=starty;
		//left=0
		if (curx-1>=0 && board[curx-1][cury]>board[curx][cury] ){
			curx-=1;
		   // cout<<"left";
			return 0;
		}
		//up=1
		else if (cury-1>=0 && board[curx][cury-1]>board[curx][cury] ){
			cury-=1;
		   // cout<<"up";
			return 1;
		}
		//right=2
		else if (curx+1<sizex && board[curx+1][cury]>board[curx][cury] ){
			curx+=1;
		   // cout<<"right";
			return 2;
		}
		//down=3
		else if (cury+1<sizey && board[curx][cury+1]>board[curx][cury] ){
			cury+=1;
		   // cout<<"down";
			return 3;
		}
		else
		{
			return -1;
		}
		while(curx!=endx || cury!=endy){
			//left=0
			//cout<< curx <<" "<<cury<<endl;
			if (curx-1>=0 && board[curx-1][cury]>board[curx][cury] ){
				board[curx][cury]=-1;
				curx-=1;
			  //  cout<<"left";
				moves.push_back(0);
			}
			//up=1
			else if (cury-1>=0 && board[curx][cury-1]>board[curx][cury] ){
				board[curx][cury]=-1;
				cury-=1;
				//cout<<"up";
				moves.push_back(1);
			}
			//right=2
			else if (curx+1<sizex && board[curx+1][cury]>board[curx][cury] ){
				board[curx][cury]=-1;
				curx+=1;
			   // cout<<"right";
				moves.push_back(2);
			}
			//down=3
			else if (cury+1<sizey && board[curx][cury+1]>board[curx][cury] ){
				board[curx][cury]=-1;
				cury+=1;
			   // cout<<"down";
				moves.push_back(3);
			}else{
				//cout<<"error in path"<<endl;
				break;

			}


		}
		//cout<<"Finished solve";
		/*
		 while(true){
		 repaint();
		 try{
		 t1.sleep(50);
		 }
		 catch(InterruptedException e){}
		 }
		 */

		 return moves.at(0);
		}

/*
	Moves cursor to top left of screen in order to prepare for next Draw call
*/
	void clearScreen()
	{
		HANDLE hOut;
		COORD Position;

		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		Position.X = 0;
		Position.Y = 0;
		SetConsoleCursorPosition(hOut, Position);
	}

	Player pacman;

	struct Ghost
	{

		int speed, pointValue, locationX, locationY, style, dir;
		bool isEdible;
		Ghost()
		{
			isEdible = false;
			pointValue = 100;
		}

		bool inColRow(){
			for (int i=locationX;i<22;i++){
				if (GameBoard[i][locationY] == PACMAN)
					return true;
				else if(GameBoard[i][locationY] == WALL)
					break;
			}
			for (int i=locationX;i>=0;i--){
				if (GameBoard[i][locationY] == PACMAN)
					return true;
				else if(GameBoard[i][locationY] == WALL)
					break;
			}
			for (int i=locationY;i<19;i++){
				if (GameBoard[locationX][i] == PACMAN)
					return true;
				else if (GameBoard[locationX][i] == WALL)
					break;
			}
			for (int i=locationY;i>=0;i--){
				if (GameBoard[locationX][i] == PACMAN)
					return true;
				else if (GameBoard[locationX][i] == WALL)
					break;
			}
			return false;
		}

		void	*mover(int endx, int endy){
			if (canDie)
				die(*this);
			int board[22][19];
			for (int i=0;i<22;i++)
				for (int j=0;j<19;j++)
					board[i][j]=GameBoard[i][j];
				vector<int> ways;
				ways.clear();
				if (dir!=RIGHT && locationY-1>=0 && GameBoard[locationX][locationY-1]!=WALL && (!isEdible || locationY <= pacman.locationCol || !inColRow())){
					ways.push_back(LEFT);
				}
				if (dir!=LEFT && locationY+1<19 && GameBoard[locationX][locationY+1]!=WALL && (!isEdible || locationY >= pacman.locationCol || !inColRow())){
					ways.push_back(RIGHT);
				}
				if (dir!=DOWN && locationX-1>=0 && GameBoard[locationX-1][locationY]!=WALL && (!isEdible || locationX <= pacman.locationRow || !inColRow())){
					ways.push_back(UP);
				}	
				if (dir!=UP && locationX+1<22 && GameBoard[locationX+1][locationY]!=WALL&& (!isEdible || locationX >= pacman.locationRow || !inColRow())){
					ways.push_back(DOWN);
				}
				int move;
				srand(time(NULL));
				if (ways.empty()){
					move=(dir+2)%4;
				}else
				move = ways.at(rand()%ways.size());

				if (!isEdible){
					if (style  == 0){
						if (sqrt(pow(pacman.locationRow - locationX,2) + pow(pacman.locationCol - locationY,2) ) < 5+level)
							move = solve(locationX, locationY, endx, endy, board);
						else if (inColRow())
							move = solve(locationX, locationY, endx, endy, board);
					}else if (style == 1){
						if (inColRow() )
							move = solve(locationX, locationY, endx, endy, board);
					}
				}
		//cout<<move<<endl;
		//up
				if(move==0){
					dir=0;
					locationX--;
				}
		//right
				else if(move==1){
					dir=1;
					locationY++;
				}
		//down
				else if(move==2){
					dir=2;
					locationX++;
				}
		//left
				else if(move==3){
					dir=3;
					locationY--;
				}
				if (canDie)
					die(*this);
			}


		};


		Ghost Blinky;
		Ghost Pinky;
		Ghost Inky;
		Ghost Clyde;

		void die(Ghost temp){

			if(temp.locationX == pacman.locationRow && temp.locationY == pacman.locationCol && temp.isEdible == false){
			//Draw();
				Sleep(1000);
				live--;
				GameBoard[pacman.locationRow][pacman.locationCol] = EMPTY;
				pacman.locationRow = 16;
				pacman.locationCol = 9;
				GameBoard[pacman.locationRow][pacman.locationCol] = PACMAN;
				ghostTimer=0;
				Blinky.locationX = 9;
				Blinky.locationY = 9;
				Pinky.locationX = 10;
				Pinky.locationY = 8;
				Inky.locationX = 10;
				Inky.locationY = 9;
				Clyde.locationX = 10;
				Clyde.locationY = 10;
				pacman.locationRow = 16;
				pacman.locationCol = 9;
				direction = -1;
				if (live == 0)
					gameOver=true;
			//direction = HOLD;
			//Sleep(1000);
			}

			else if(temp.locationX == pacman.locationRow && temp.locationY == pacman.locationCol && temp.isEdible == true){
				temp.locationX=9;
				temp.locationY=9;
				temp.isEdible = false;
			}
		}

		void Setup() {
	//score = 0;
			ghostTimer=0;
			Blinky.locationX = 9;
			Blinky.locationY = 9;
			Blinky.style = 0;
			Pinky.locationX = 10;
			Pinky.locationY = 8;
			Pinky.style = 1;
			Inky.locationX = 10;
			Inky.locationY = 9;
			Inky.style = 1;
			Clyde.locationX = 10;
			Clyde.locationY = 10;
			Clyde.style = 2;
			pacman.locationRow = 16;
			pacman.locationCol = 9;

			GameBoard[16][9] = PACMAN;
			GameBoard[3][1] = SPECIAL_DOT;
			GameBoard[3][17] = SPECIAL_DOT;
			GameBoard[16][1] = SPECIAL_DOT;
			GameBoard[16][17] = SPECIAL_DOT;

	//GameBoard[Blinky.locationX][Blinky.locationY] = BLINKY;
	//GameBoard[Pinky.locationX][Pinky.locationY] = PINKY;
	//GameBoard[Inky.locationX][Inky.locationY] = INKY;
	//GameBoard[Clyde.locationX][Clyde.locationY] = CLYDE;
			GameBoard[pacman.locationRow][pacman.locationCol] = PACMAN;

			for (int i = 0; i < 22; i++) {
				for (int j = 0; j < 19; j++) {
					if (GameBoard[i][j] == EMPTY) {
						if (j >= 5 && j <= 13 && i >= 7 && i <= 13) {
							GameBoard[i][j] = EMPTY;
						}
						else if ((i == 8 || i == 12) && ((j >= 0 && j <= 2) || (j <= 18 && j >= 16))) {
							GameBoard[i][j] = EMPTY;
						}
						else
							GameBoard[i][j] = DOT;

					}
					else if(GameBoard[i][j] == FRUIT){
						GameBoard[i][j] = EMPTY;
					}
				}
			}


			generateFruit();

		}

		void Draw() {

			bool noDot = true;
			bool noSpecialDot = true;
			bool noFruit = true;
			if (canDie)
				cout << "SCOREs: " << score << endl;
			cout << "LIVES: " << live << endl;
			cout << "LEVEL: " << level << endl;
			if (!canDie)
				cout<< "CHEAT ACTIVE"<<endl;
	//cout << "\t\tCOUNTER: " << counter << endl;
			for (int i = 0; i < 22; i++) {
				for (int j = 0; j < 19; j++) {
					if(Blinky.locationX == i && Blinky.locationY == j){
						if(Blinky.isEdible){
							cout << " \\!/ ";
						}
						else{
							cout << "  " << (char)232 << "  ";
						}
					}
					else if(Pinky.locationX == i && Pinky.locationY == j){
						if(Pinky.isEdible){
							cout << " \\!/ ";
						}
						else{
							cout << "  " << (char)232 << "  ";
						}
					}
					else if(Inky.locationX == i && Inky.locationY == j){
						if(Inky.isEdible){
							cout << " \\!/ ";
						}
						else{
							cout << "  " << (char)232 << "  ";
						}
					}
					else if(Clyde.locationX == i && Clyde.locationY == j){
						if(Clyde.isEdible){
							cout << " \\!/ ";
						}
						else{
							cout << "  " << (char)232 << "  ";
						}
					}
					else{
						if (GameBoard[i][j] == WALL) {
							cout << (char)178 << (char)178 << (char)178 <<(char)178 << (char)178 ;
						}
						else if (GameBoard[i][j] == DOT) {
							cout << "     " ;
							noDot = false;
						}
						else if (GameBoard[i][j] == SPECIAL_DOT){
							cout << "     " ;
							noSpecialDot = false;	
						}
						else if (GameBoard[i][j] == EMPTY) {
							cout << "     ";
						}
			/*else if (GameBoard[i][j] == PINKY || GameBoard[i][j] == INKY || GameBoard[i][j] == BLINKY || GameBoard[i][j] == CLYDE) {
				cout << "GG";
			}*/
				else if (GameBoard[i][j] == PACMAN) {
					cout << " " << (char)92<<(char)32<<(char)47<< " " ;
				}
				else if (GameBoard[i][j] == FRUIT) {
					cout << " " << (char)92<<(char)40<<(char)41<< " " ;
					noFruit = false;
				}
			}
		}


		cout << endl;
		for (int j = 0; j < 19; j++) {
			if(Blinky.locationX == i && Blinky.locationY == j){
				cout << " /B\\ ";
			}
			else if(Pinky.locationX == i && Pinky.locationY == j){
				cout << " /P\\ ";
			}
			else if(Inky.locationX == i && Inky.locationY == j){
				cout << " /I\\ ";
			}
			else if(Clyde.locationX == i && Clyde.locationY == j){
				cout << " /C\\ ";
			}
			else{
				if (GameBoard[i][j] == WALL) {
					cout << (char)178 << (char)178 << (char)178 <<(char)178 << (char)178;
				}
				else if (GameBoard[i][j] == DOT) {
					cout << "  " << (char)248 << "  " ;
				}
				else if (GameBoard[i][j] == SPECIAL_DOT){
					cout << "  " << (char)233 << "  " ;
				}
				else if (GameBoard[i][j] == EMPTY || GameBoard[i][j] == WRAPL || GameBoard[i][j] == WRAPR) {
					cout << "     ";
				}
			/*else if (GameBoard[i][j] == PINKY || GameBoard[i][j] == INKY || GameBoard[i][j] == BLINKY || GameBoard[i][j] == CLYDE) {
				cout << "GG";
			}*/
				else if (GameBoard[i][j] == PACMAN) {
					cout << " " << (char)229<<(char)95<<(char)229<< " " ;
				}
				else if (GameBoard[i][j] == FRUIT) {
					cout << " " << (char)219<<(char)219<<(char)219<< " " ;
					noFruit = false;
				}
			}
		}
		cout << endl;
		for (int j = 0; j < 19; j++) {
			if((Blinky.locationX == i && Blinky.locationY == j)
				||(Pinky.locationX == i && Pinky.locationY == j)
				||(Inky.locationX == i && Inky.locationY == j)
				||(Clyde.locationX == i && Clyde.locationY == j))	{
				cout << " " << (char)32<<(char)32<<(char)32<< " " ;
		}
		else{
			if (GameBoard[i][j] == WALL) {
				cout << (char)178 << (char)178 << (char)178 <<(char)178 << (char)178;
			}
			else if (GameBoard[i][j] == DOT) {
				cout << "     " ;
			}
			else if (GameBoard[i][j] == SPECIAL_DOT){
				cout << "     " ;
			}
			else if (GameBoard[i][j] == EMPTY || GameBoard[i][j] == WRAPL || GameBoard[i][j] == WRAPR) {
				cout << "     ";
			}
			/*else if (GameBoard[i][j] == PINKY || GameBoard[i][j] == INKY || GameBoard[i][j] == BLINKY || GameBoard[i][j] == CLYDE) {
				cout << "GG";
			}*/
				else if (GameBoard[i][j] == PACMAN) {
					cout << " " << (char)62<<(char)61<<(char)60<< " " ;
				}
				else if (GameBoard[i][j] == FRUIT) {
					cout << " " << (char)223<<(char)223<<(char)223<< " " ;
					noFruit = false;
				}
			}
		}
		cout<<endl;
	}
	if (noDot && noSpecialDot /*&& noFruit*/){
	gameOver = true;
	direction = WIN_GAME;
}
if ((direction == LEFT || direction == RIGHT || direction == UP || direction == DOWN) && noFruit==true){
	counter++;
}

if (counter == 20){
	generateFruit();
	counter = 0;
}

if(ghostEdibleMode == true){
	if (edibleCounter == 40){
		Blinky.isEdible = true;
		Inky.isEdible = true;
		Pinky.isEdible = true;
		Clyde.isEdible = true;
	}
	edibleCounter--;
}

if(edibleCounter == 0){
	ghostEdibleMode = false;
	Blinky.isEdible = false;
	Inky.isEdible = false;
	Pinky.isEdible = false;
	Clyde.isEdible = false;
	edibleCounter = 40;
}

}


void Input() {
	if (_kbhit()){
		switch (_getch()) {
			case 'c':
			if (canDie)
				canDie=false;
			else
				canDie=true;
			system("cls");
			break;
			case 'n':
			direction = NEW_GAME;
			validInput = true;
			break;
			case 'p':
			direction = PAUSE;
			validInput = true;
			break;
			case 'q':
			direction = QUIT;
			validInput = true;
			break;
			case 'w':
			direction = UP;
			validInput = true;
			break;
			case 'a':
			direction = LEFT;
			validInput = true;
			break;
			case 's':
			direction = DOWN;
			validInput = true;
			break;
			case 'd':
			direction = RIGHT;
			validInput = true;
			break;
			default:
			validInput = false;
			direction = HOLD;
			break;
		}
	}
	if(direction != -1 && (ghostTimer) % (level+1) != 0)
		Blinky.mover(pacman.locationCol, pacman.locationRow);
	if (ghostTimer>20 && direction != -1 && (ghostTimer) % (level/2+2) != 0)
		Pinky.mover(pacman.locationCol, pacman.locationRow);
	if (ghostTimer>10 && direction != -1 && (ghostTimer) % (level/3+2) != 0)
		Inky.mover(pacman.locationCol, pacman.locationRow);
	if (ghostTimer>30 && direction != -1 && (ghostTimer) % (level/2+2) != 0)
		Clyde.mover(pacman.locationCol, pacman.locationRow);

	if (direction != -1)
		ghostTimer++;

	Sleep(100);

	
}


void Logic() {
	int tempX = pacman.locationRow;
	int tempY = pacman.locationCol;

	bool moved = false;

	switch (direction) {
		case UP:
		if (movePlayer(pacman, --tempX, tempY) == true) {
			//while(GameBoard[pacman.locationRow][pacman.locationCol] != WALL){
			pacman.locationRow--;

			//}
		}
		else {
			//cout << "Need a way to continue in same direction" << endl;
		}
		break;
		case LEFT:
		if (tempX == 10 && tempY == 0){
			GameBoard[tempX][tempY] = EMPTY;
			pacman.locationRow == 10;
			pacman.locationCol = 18;
		}
		else if(movePlayer(pacman, tempX, --tempY) == true) {
			pacman.locationCol--;
		}
		else {
			//cout << "Need a way to continue in same direction" << endl;
		}
		break;
		case DOWN:
		if (movePlayer(pacman, ++tempX, tempY) == true) {
			pacman.locationRow++;
		}
		else {
			//cout << "Need a way to continue in same direction" << endl;
		}
		break;
		case RIGHT:
		if (tempX == 10 && tempY == 18){
			GameBoard[tempX][tempY] = EMPTY;
			pacman.locationRow == 10;
			pacman.locationCol = 0;
		}
		else if (movePlayer(pacman, tempX, ++tempY) == true) {
			pacman.locationCol++;
		}
		else {
			//cout << "Need a way to continue in same direction" << endl;
		}
		break;
		case NEW_GAME:
		gameOver = true;
		break;
		case QUIT:
		gameOver = true;
		break;
		case PAUSE:
		validInput = false;
		cout << "Press r to RESUME" << endl;
		while (validInput == false) {
			cin >> input;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				validInput = false;
				cout << "cin failed" << endl;
			}
			else {
				switch (input) {
					case 'r':
					direction = HOLD;
					validInput = true;
					system("cls");
					break;
					default:
					validInput = false;
					break;
				}
			}
		}
		break;
		case HOLD:
		//cout << "Something went wrong" << endl;
		break;
	}
	if (pacman.locationRow == Blinky.locationX && pacman.locationCol == Blinky.locationY && Blinky.isEdible){
		Blinky.locationX = 10;
		Blinky.locationY = 9;
		Blinky.isEdible = false;
		score+=200;
	}
	if (pacman.locationRow == Pinky.locationX && pacman.locationCol == Pinky.locationY && Pinky.isEdible){
		Pinky.locationX = 10;
		Pinky.locationY = 9;
		Pinky.isEdible = false;
		score+=200;
	}
	if (pacman.locationRow == Inky.locationX && pacman.locationCol == Inky.locationY && Inky.isEdible){
		Inky.locationX = 10;
		Inky.locationY = 9;
		Inky.isEdible = false;
		score+=200;
	}
	if (pacman.locationRow == Clyde.locationX && pacman.locationCol == Clyde.locationY && Clyde.isEdible){
		Clyde.locationX = 10;
		Clyde.locationY = 9;
		Clyde.isEdible = false;
		score+=2;
	}

}

int stoi(string line){
	int sum=0;
	for (int i =0; i<line.length(); i++){
		sum=sum*10;
		sum=sum+(int)line.at(i)-48;
	}
	return sum;

}

int main()
{
	
	score=0;
	string line;
	vector<string> nameVect;
	vector<int> scoreVect;
	ifstream myFile("scoreBoard.txt");
	if (!myFile) {
		cerr << "Input file can not be opened" << endl;
		exit(0);
	}
	string nextLine;
	while (getline(myFile, line, '\n')) {
		  //cout << "*" << line << "*" <<endl;
		nameVect.push_back(line);
		getline(myFile, line, '\n');
		scoreVect.push_back(stoi(line));
	}
	myFile.close();



	char input;
	do {
		Setup();
		while (gameOver == false)
		{

			Input();
			Logic();
			clearScreen();
			Draw();			
			
			if(gameOver == true && direction == WIN_GAME){
				/*
				system("cls");
				cout << "CONGRATULATIONS YOU WIN!" << endl;
				*/
				Sleep(1000);
				level++;
				gameOver=false;
				direction=-1;
				GameBoard[pacman.locationRow][pacman.locationCol] = DOT;
				Setup();

			}
			else if(gameOver == true && direction == QUIT){
				exit(0);
			}
			else if (gameOver == true && direction != NEW_GAME){
				string playername;
				system("cls");
				cout << "GAME OVER!" << endl;
				Sleep(1000);
				cout << "Your Score: "<< score << endl;
				Sleep(1000);
				cout << "Your Name: ";
				cin >> playername;
				Sleep(1000);
				for (int j=0; j<scoreVect.size();++j){
					if (score>scoreVect.at(j)){
						nameVect.insert(nameVect.begin()+j, playername);
						scoreVect.insert(scoreVect.begin()+j, score);
						break;
					}
				}
				// print high score list
				for (int n=0; n<7;++n){
					cout<< nameVect.at(n)<<" "<<scoreVect.at(n)<<endl;
				}
				myFile.close();
				ofstream myOutFile("scoreBoard.txt");
				if (!myOutFile) {
					cerr << "Output file can not be opened" << endl;
					exit(0);
				}
				for (int i=0; i<7; i++) {
					myOutFile << nameVect.at(i)<<endl;
					myOutFile << scoreVect.at(i)<<endl;
				}
				myOutFile.close();

				Sleep(1000);

				cout << endl;
				cout << "Do you want to play another game?" << endl;
				cout << "Press y to play again..." << endl;
				cin >> input;
				if (input == 'y') {
					live = 3;
					direction = -1;
					gameOver = false;
					GameBoard[pacman.locationRow][pacman.locationCol] = DOT;
					score=0;
					Setup();
				}
				else {
					leavegame = true;
				}
			}

			
		}
		

	} while (!leavegame);

	return 0;
}
