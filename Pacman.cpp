#include "Pacman.h"
using namespace std;

bool gameOver;
bool validInput;
char input;
string direction;
Player pacman;



void Setup() {
	gameOver = false;
}

void Draw() {
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
	direction = " ";

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
				direction = "NEW GAME";
				break;
			case 'p':
				direction = "PAUSE";
				validInput = true;
				break;
			case 'q':
				direction = "QUIT";
				validInput = true;
				break;
			case 'w':
				direction = "UP";
				validInput = true;
				break;
			case 'a':
				direction = "LEFT";
				validInput = true;
				break;
			case 's':
				direction = "DOWN";
				validInput = true;
				break;
			case 'd':
				direction = "RIGHT";
				validInput = true;
				break;
			default:
				validInput = false;
				break;
			}
		}
	}
}

void Logic() {

	if (direction.compare("UP") == 0) {
		cout << direction << endl;
		if (movePlayer(pacman, pacman.locationX--, pacman.locationY) == false) {
			cout << "Need a way to continue in same direction" << endl;
		}
	}
	else if (direction.compare("LEFT") == 0) {
		cout << direction << endl;
		if (movePlayer(pacman, pacman.locationX, pacman.locationY++) == false) {
			cout << "Need a way to continue in same direction" << endl;
		}
	}
	else if (direction.compare("DOWN") == 0) {
		cout << direction << endl;
		if (movePlayer(pacman, pacman.locationX++, pacman.locationY) == false) {
			cout << "Need a way to continue in same direction" << endl;
		}
	}
	else if (direction.compare("RIGHT") == 0) {
		cout << direction << endl;
		if (movePlayer(pacman, pacman.locationX, pacman.locationY--) == false) {
			cout << "Need a way to continue in same direction" << endl;
		}
	}
	else if (direction.compare("NEW GAME") == 0) {
		cout << direction << endl;
		gameOver = true;
	}
	else if (direction.compare("QUIT") == 0) {
		cout << direction << endl;
		gameOver = true;
	}
	else if (direction.compare("PAUSE") == 0) {
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
	}
	else if (direction.compare(" ") == 0) {
		cout << direction << endl;
		cout << "Something went wrong" << endl;
	}
}

int main()
{
	Setup();
	while (gameOver == false)
	{
		Draw();
		Input();
		Logic();
	}
	return 0;
}