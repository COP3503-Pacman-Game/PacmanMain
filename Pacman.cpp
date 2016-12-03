#include "Pacman.h"
#include "Windows.h"
#include "conio.h"
using namespace std;

bool startOver;
bool gameOver;
bool validInput;
char input;
int direction=-1;

Player pacman;


struct Ghost
{
	int speed, pointValue, locationX, locationY, style, dir;
	bool isEdible;
	double timeIsEdible;
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
if (dir!=RIGHT && locationY-1>=0 && GameBoard[locationX][locationY-1]!=WALL){
	ways.push_back(LEFT);
}
if (dir!=LEFT && locationY+1<19 && GameBoard[locationX][locationY+1]!=WALL){
	ways.push_back(RIGHT);
}
if (dir!=DOWN && locationX-1>=0 && GameBoard[locationX-1][locationY]!=WALL){
	ways.push_back(UP);
}
if (dir!=UP && locationX+1<22 && GameBoard[locationX+1][locationY]!=WALL){
	ways.push_back(DOWN);
}
int move;
srand(time(NULL));
	if (ways.empty()){
		move=(dir+2)%4;
	}else
		move = ways.at(rand()%ways.size());
 			if (style  == 0){
 				if (sqrt(pow(pacman.locationRow - locationX,2) + pow(pacman.locationCol - locationY,2) ) <10)
 					move = solve(locationX, locationY, endx, endy, board);
 				else if (inColRow())
 					move = solve(locationX, locationY, endx, endy, board);
 			}else if (style == 1){
 				if (inColRow() )
 					move = solve(locationX, locationY, endx, endy, board);
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
	}

};

Ghost Blinky;
Ghost Pinky;
Ghost Inky;
Ghost Clyde;

void Setup() {
	gameOver = false;
	Blinky.locationX = 1;
	Blinky.locationY = 1;
	Blinky.style = 0;
	Blinky.dir=0;
	Pinky.locationX = 1;
	Pinky.locationY = 3;
	Pinky.style = 1;
	Pinky.dir=0;
	Inky.locationX = 20;
	Inky.locationY = 1;
	Inky.style = 1;
	Inky.dir=0;
	Clyde.locationX = 10;
	Clyde.locationY = 10;
	Clyde.style = 2;
	Clyde.dir=0;
	pacman.locationRow = 16;
	pacman.locationCol = 9;
/*
	GameBoard[Blinky.locationX][Blinky.locationY] = BLINKY;
	GameBoard[Pinky.locationX][Pinky.locationY] = PINKY;
	GameBoard[Inky.locationX][Inky.locationY] = INKY;
	GameBoard[Clyde.locationX][Clyde.locationY] = CLYDE;

*/
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
		}
	}
}

void Draw() {

	cout << "SCORE: " << pacman.score << endl;
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 19; j++) {
		if((Blinky.locationX == i && Blinky.locationY == j)
			||(Pinky.locationX == i && Pinky.locationY == j)
			||(Inky.locationX == i && Inky.locationY == j)
			||(Clyde.locationX == i && Clyde.locationY == j))	{
			cout << "GG";
			}
		else{
			if (GameBoard[i][j] == WALL) {
				cout << "##";
			}
			else if (GameBoard[i][j] == DOT) {
				cout << (char)46 <<(char)46;
			}
			else if (GameBoard[i][j] == EMPTY || GameBoard[i][j] == WRAPL || GameBoard[i][j] == WRAPR) {
				cout << "  ";
			}
			/*else if (GameBoard[i][j] == PINKY || GameBoard[i][j] == INKY || GameBoard[i][j] == BLINKY || GameBoard[i][j] == CLYDE) {
				cout << "GG";
			}*/
			else if (GameBoard[i][j] == PACMAN) {
				cout << "XX";
			}
		}
	}


		cout << endl;
		for (int j = 0; j < 19; j++) {
			if((Blinky.locationX == i && Blinky.locationY == j)
				||(Pinky.locationX == i && Pinky.locationY == j)
				||(Inky.locationX == i && Inky.locationY == j)
				||(Clyde.locationX == i && Clyde.locationY == j))	{
				cout << "GG";
				}
			else{
			if (GameBoard[i][j] == WALL) {
				cout << "##";
			}
			else if (GameBoard[i][j] == DOT) {
				cout << (char)46 <<(char)46;
			}
			else if (GameBoard[i][j] == EMPTY || GameBoard[i][j] == WRAPL || GameBoard[i][j] == WRAPR) {
				cout << "  ";
			}
			/*else if (GameBoard[i][j] == PINKY || GameBoard[i][j] == INKY || GameBoard[i][j] == BLINKY || GameBoard[i][j] == CLYDE) {
				cout << "GG";
			}*/
			else if (GameBoard[i][j] == PACMAN) {
				cout << "XX";
			}
		}
	}
		cout<<endl;
	}
	cout<<Pinky.locationX-30<<" "<<Pinky.locationY<<" "<<GameBoard[Pinky.locationX-30][Pinky.locationY]<<endl;
}


void Input() {


	if(_kbhit()){
		switch(_getch()){
			case 'n':
				validInput = true;
				direction = NEW_GAME;
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
	//cout<<pacman.locationRow<<" "<<pacman.locationCol;
	if(direction != -1){
	Blinky.mover(pacman.locationCol, pacman.locationRow);
	Pinky.mover(pacman.locationCol, pacman.locationRow);
	Inky.mover(pacman.locationCol, pacman.locationRow);
	Clyde.mover(pacman.locationCol, pacman.locationRow);
}
	Sleep(400);

	
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
			cout << "Need a way to continue in same direction" << endl;
		}
		break;
	case LEFT:
		if (movePlayer(pacman, tempX, --tempY) == true) {
			pacman.locationCol--;
		}
		else {
			cout << "Need a way to continue in same direction" << endl;
		}
		break;
	case DOWN:
		if (movePlayer(pacman, ++tempX, tempY) == true) {
			pacman.locationRow++;
		}
		else {
			cout << "Need a way to continue in same direction" << endl;
		}
		break;
	case RIGHT:
		if (movePlayer(pacman, tempX, ++tempY) == true) {
			pacman.locationCol++;
		}
		else {
			cout << "Need a way to continue in same direction" << endl;
		}
		break;
	case NEW_GAME:
		gameOver = true;
		startOver = true;
		break;
	case QUIT:
		gameOver = true;
		break;
	case PAUSE:
		validInput = false;
		cout << direction << endl;
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
					validInput = true;
					cout << "RESUME" << endl;
					break;
				default:
					validInput = false;
					break;
				}
			}
		}
		break;
	case HOLD:
		cout << "Something went wrong" << endl;
		break;
	}
}

int main()
{
	do {
		Setup();
		while (gameOver == false)
		{
			
			Input();
			Logic();
			system("cls");
			Draw();
		}
	} while (startOver == true);

	return 0;
}
