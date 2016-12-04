//FIXED SCORE
//FIXED PAUSE
//FIXED NEW GAME
//ADDED FRUIT
//ADDED SPECIAL DOTS
//FIXED WRAP OMFG
//FIXED Flicker

/*  TO_DO
fruit repawn - done
ghost characters - done
special dot - done
pacman characters - done
ghost speed = done
edible fixed


score board
*/

#include "Pacman.h"
#include <conio.h>
#include <Windows.h>
using namespace std;

int edibleCounter = 0;
int counter;
bool gameOver = false;
bool leavegame = false;
bool validInput;
char input;
int direction = -1;


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
	for (int i=locationX;i<22-locationX;i++){
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
	for (int i=locationY;i<19-locationY;i++){
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
 				if (sqrt(pow(pacman.locationRow - locationX,2) + pow(pacman.locationCol - locationY,2) ) < 5)
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

		if(locationX == pacman.locationRow && locationY == pacman.locationCol && isEdible == false){
			//Draw();
			gameOver=true;
			direction = HOLD;
			Sleep(1000);
		}

		else if(locationX == pacman.locationRow && locationY == pacman.locationCol && isEdible == true){
			locationX=9;
			locationY=9;
			isEdible = false;
		}

	}


};


Ghost Blinky;
Ghost Pinky;
Ghost Inky;
Ghost Clyde;

void Setup() {
	score = 0;
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
	cout << "SCORE: " << score << endl;
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
		if(direction != -1 && (ghostTimer*2)%3 != 0){
			Blinky.mover(pacman.locationCol, pacman.locationRow);
			if (ghostTimer>20)
				Pinky.mover(pacman.locationCol, pacman.locationRow);
			if (ghostTimer>10)
				Inky.mover(pacman.locationCol, pacman.locationRow);
			if (ghostTimer>30)
				Clyde.mover(pacman.locationCol, pacman.locationRow);
		}
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
					system("clsx");
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
		score+=100;
	}
	if (pacman.locationRow == Pinky.locationX && pacman.locationCol == Pinky.locationY && Pinky.isEdible){
		Pinky.locationX = 10;
		Pinky.locationY = 9;
		Pinky.isEdible = false;
		score+=100;
	}
		if (pacman.locationRow == Inky.locationX && pacman.locationCol == Inky.locationY && Inky.isEdible){
		Inky.locationX = 10;
		Inky.locationY = 9;
		Inky.isEdible = false;
		score+=100;
	}
		if (pacman.locationRow == Clyde.locationX && pacman.locationCol == Clyde.locationY && Clyde.isEdible){
		Clyde.locationX = 10;
		Clyde.locationY = 9;
		Clyde.isEdible = false;
		score+=100;
	}

}

int main()
{
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
				system("cls");
				cout << "CONGRATULATIONS YOU WIN!" << endl;
				Sleep(1000);
			}
			else if(gameOver == true && direction == QUIT){
				exit(0);
			}
			else if (gameOver == true && direction != NEW_GAME){
				system("cls");
				cout << "GAME OVER!" << endl;
				Sleep(1000);
				cout << "YOU SUCK" << endl;
				Sleep(1000);
			}
		}
		cout << endl;
		cout << "Do you want to play another game?" << endl;
		cout << "Press y to play again..." << endl;
		cin >> input;
		if (input == 'y') {
			direction = -1;
			gameOver = false;
			GameBoard[pacman.locationRow][pacman.locationCol] = DOT;
			Setup();
			
		}
		else {
			leavegame = true;
		}

	} while (leavegame == false);

	return 0;
}
