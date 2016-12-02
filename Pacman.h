#include <iostream>
#include <math.h>
#include <vector>
#include <stdbool.h>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

//Gamestates
const int RIGHT = 200;
const int LEFT = 201;
const int UP = 202;
const int DOWN = 203;
const int NEW_GAME = 204;
const int QUIT = 205;
const int PAUSE = 206;
const int RESUME = 207;
const int HOLD = 208;

//Variables on the board
const int EMPTY = 0;
const int WALL = 1;
const int DOT = 2;
const int SPECIAL_DOT = 3;
const int CHERRY = 4;
const int BANANA = 5;
const int STRAWBERRY = 6;
const int BLINKY = 7;
const int PINKY = 8;
const int INKY = 9;
const int CLYDE = 10;
const int PACMAN = 11;
const int WRAPL = 12;
const int WRAPR = 13;


int GameBoard[22][19] = {
	{ WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY },
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,PINKY ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ WRAPL ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,INKY  ,BLINKY,CLYDE ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WRAPR },
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY, PACMAN,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY },
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL , WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL }
	};



struct Player
{
	int locationRow, locationCol, score, lives;
	Player()
	{
		locationRow = 12;
		locationCol = 9;
		score = 0;
		lives = 3;
	}
};

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

};

/*These are arbitrary values, BUT if we keep all
values greater than 0 wrap-around is much easier
to implement.
*/


//Do we have access to GameBoard from this function?

bool movePlayer(Player player, int x, int y)
{
	//Reset WRAPR and WRAPL
	//TEMPORARY- MAKE SURE TO CHANGE
	GameBoard[10][18] = WRAPR;
	GameBoard[10][19] = WRAPL;

	int element = GameBoard[x][y];

	if (element == WALL) {
		return false;
	}
	else if ((element == BLINKY) || (element == PINKY) || (element == INKY) || (element == CLYDE)) {
		player.lives--;
		if (player.lives == 0) {
			//gameOver = true;
		}
		//reset level
		return false;
	}
	else if (element == DOT) {
		player.score++;
	}
	else if (element == SPECIAL_DOT) {
		player.score++;
		//!!!Need somehow to set ghosts to edible!!!
	}
	else if ((element == CHERRY) || (element == BANANA) || (element == STRAWBERRY)) {
		player.score += 10;
	}

	else if (element == WRAPL) {
		GameBoard[player.locationRow][player.locationCol] = EMPTY; //current position becomes empty
		player.locationRow = 10;
		player.locationCol = 18;
		GameBoard[player.locationRow][player.locationCol] = PACMAN; //desired position becomes player
		return true;
	}

	else if (element == WRAPR) {
		GameBoard[player.locationRow][player.locationCol] = EMPTY; //current position becomes empty
		player.locationRow = 10;
		player.locationCol = 0;
		GameBoard[player.locationRow][player.locationCol] = PACMAN; //desired position becomes player
		return true;
	}
	
	GameBoard[player.locationRow][player.locationCol] = EMPTY; //current position becomes empty
	player.locationRow = x; player.locationCol = y;
	GameBoard[player.locationRow][player.locationCol] = PACMAN; //desired position becomes player
	return true;
	}
	/*
	//Wrap-around
	else if (x < 0) {	//left to right
		x = LevelX - 1;
	}
	else if (x == LevelX) { //right to left
		x = 0;
	}
	else if (y < 0) { //top to bottom
		y = LevelY - 1;
	}
	else if (y == LevelY) { //bottom to top
		y = 0;
	}
	
	
	*/




