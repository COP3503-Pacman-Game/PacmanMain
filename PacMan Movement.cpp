#include <iostream>
#include <Windows.h>
#include <math.h>
using namespace std;

struct Player 
{
	int locationX, locationY, score, lives;
	Player()
	{
		locationX = -1;
		locationY = -1;
		score = 0;
		lives = 3;
	}
};


/*These are arbitrary values, BUT if we keep all
values greater than 0 wrap-around is much easier 
to implement.
*/
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

//Do we have access to GameBoard from this function?
const int LevelX = GameBoard.size;
const int LevelY = GameBoard[0].size;

bool movePlayer(Player &player, int x, int y)
{
	int element = GameBoard[x][y];
	
	if(element == WALL){
		return false;
	}
	else if((element == BLINKY) OR (element == PINKY) OR (element == INKY) OR (element == CLYDE)){
		player.lives--;
		return false;
	}
	else if(element == DOT){
		player.score++;
	}
	else if(element == SPECIAL_DOT){
		player.score++;
		//!!!Need somehow to set ghosts to edible!!!
	}
	else if((element == CHERRY) OR (element == BANANA) OR (element == STRAWBERRY)){
		player.score += 10;
	}
	//Wrap-around
	else if(x < 0){	//left to right
		x = LevelX - 1;
	}
	else if(x == LevelX){ //right to left
		x = 0;
	}
	else if(y < 0){ //top to bottom
		y = LevelY - 1;
	}
	else if(y == LevelY){ //bottom to top
		y = 0;
	}
	
	GameBoard[player.x][player.y] = EMPTY; //current position becomes empty
	
	player.x = x; player.y = y;
	GameBoard[player.x][player.y] = PACMAN; //desired position becomes player
	return true;
}



