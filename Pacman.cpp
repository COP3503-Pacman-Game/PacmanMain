#include "Pacman.h"
using namespace std;

bool startOver;
bool gameOver;
bool validInput;
char input;
int direction;
Player pacman;

Ghost Blinky;
Ghost Pinky;
Ghost Inky;
Ghost Clyde;

void Setup() {
	system("clear");
	gameOver = false;
	Blinky.locationX = 10;
	Blinky.locationY = 9;
	Pinky.locationX = 9;
	Pinky.locationY = 9;
	Inky.locationX = 10;
	Inky.locationY = 8;
	Clyde.locationX = 10;
	Clyde.locationY = 10;
	pacman.locationRow = 12;
	pacman.locationCol = 9;
}

void Draw() {
	cout << "SCORE: " << pacman.score << endl;
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 19; j++) {
			if (GameBoard[i][j] == WALL) {
				cout << "#";
			}
			else if (GameBoard[i][j] == EMPTY || GameBoard[i][j] == WRAPL || GameBoard[i][j] == WRAPR) {
				cout << " ";
			}
			else if (GameBoard[i][j] == PINKY || GameBoard[i][j] == INKY || GameBoard[i][j] == BLINKY || GameBoard[i][j] == CLYDE) {
				cout << "G";
			}
			else if (GameBoard[i][j] == PACMAN) {
				cout << "X";
			}
		}
		cout << endl;
	}
}

void Input() {
	validInput = false;
	direction = HOLD;

	while (validInput == false) {
		cin >> input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			bool validInput = false;
		}
		else {
			switch (input) {
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
	}
}

void Logic() {
	int tempX = pacman.locationRow;
	int tempY = pacman.locationCol;

	switch (direction) {
	case UP:
		if (movePlayer(pacman, --tempX, tempY) == true) {
			pacman.locationRow--;
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
			Draw();
			Input();
			Logic();
		}
	} while (startOver == true);

	return 0;
}