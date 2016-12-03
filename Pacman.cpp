#include "Pacman.h"
#include "Windows.h"
#include "conio.h"
using namespace std;

bool startOver;
bool gameOver;
bool validInput;
char input;
int direction;

Player pacman;


struct Ghost
{
	int speed, pointValue, locationX, locationY;
	bool isEdible;
	double timeIsEdible;
	Ghost()
	{
		isEdible = false;
		pointValue = 100;
	}
 void	*mover(int endx, int endy){
		int move = solve(locationX, locationY, endx, endy, GameBoard);
		//left
		if(move==0){
			locationX--;
		}
		//up
		else if(move==1){
			locationY--;
		}
		//right
		else if(move==2){
			locationX++;
		}
		//down
		else if(move==3){
			locationY++;
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
	Pinky.locationX = 1;
	Pinky.locationY = 3;
	Inky.locationX = 20;
	Inky.locationY = 1;
	Clyde.locationX = 10;
	Clyde.locationY = 10;
	pacman.locationRow = 16;
	pacman.locationCol = 9;

	GameBoard[Blinky.locationX][Blinky.locationY] = BLINKY;
	GameBoard[Pinky.locationX][Pinky.locationY] = PINKY;
	GameBoard[Inky.locationX][Inky.locationY] = INKY;
	GameBoard[Clyde.locationX][Clyde.locationY] = CLYDE;




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
	cout<<pacman.locationRow<<" "<<pacman.locationCol;
	Blinky.mover(pacman.locationCol, pacman.locationRow);
	Pinky.mover(pacman.locationCol, pacman.locationRow);
	Inky.mover(pacman.locationCol, pacman.locationRow);
	Clyde.mover(pacman.locationCol, pacman.locationRow);
	Sleep(500);

	
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
	system("cls");
			Draw();
			Input();
			Logic();
		}
	} while (startOver == true);

	return 0;
}
