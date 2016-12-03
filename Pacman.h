#include <iostream>
#include <math.h>
#include <vector>
#include <stdbool.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <queue>

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
const int WALL = 0;
const int EMPTY = 1;
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
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY/*PINKY*/ ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ WRAPL ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY/*INKY*/  ,EMPTY/*BLINKY*/,EMPTY/*CLYDE*/ ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WRAPR },
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY, EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY },
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,PACMAN ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL , WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL }
	};



struct Player
{
	int locationRow, locationCol, score, lives;
	double movementTimer;
	Player()
	{
		locationRow = 16;
		locationCol = 9;
		score = 0;
		lives = 3;
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
	//if (pacman.locationRow != 10 && (pacman.locationCol != 18 && pacman.locationCol != 19)) {
		GameBoard[10][18] = WRAPR;
		GameBoard[10][19] = WRAPL;
	//}

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


	int solve(int startx, int starty, int endx, int endy, int board[22][19]) {


	    for (int i=0;i<19;i++)
	       for (int j=0; j<22;j++)
	           if (board[j][i] > 0 )
	               board[j][i] =1;


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
	    for (i=0;i<sizex;i++)
	        for (j=0;j<sizey;j++)
	            board[i][j]=1;
	    Xloc.push(startx);
	    Yloc.push(starty);
	    board[startx][starty]=2;


	    while(!Xloc.empty()){
	        bool nott = true;

	        X = Xloc.front();
	        Xloc.pop();
	        Y = Yloc.front();
	        Yloc.pop();
	        //left
	        // cout<<X<<" "<<Y<<" ";
	        if (X-1>=0 && board[X-1][Y]==1 ){
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
	    for (i=0;i<sizex;i++){
	        for (j=0;j<sizey;j++)
	            cout<<board[j][i]<<" ";
	        cout<<endl;
	    }
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
	        if (kill){
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
	    vector <int>moves ;
	    int curx=startx;
	    int cury=starty;
	    //left=0
	    if (curx-1>=0 && board[curx-1][cury]>board[curx][cury] ){
	        curx-=1;
	        //cout<<"left"<<endl;
	        moves.push_back(0);
	    }
	    //up=1
	    else if (cury-1>=0 && board[curx][cury-1]>board[curx][cury] ){
	        cury-=1;
	        //cout<<"up"<<endl;
	        moves.push_back(1);
	    }
	    //right=2
	    else if (curx+1<sizex && board[curx+1][cury]>board[curx][cury] ){
	        curx+=1;
	        //cout<<"right"<<endl;
	        moves.push_back(2);
	    }
	    //down=3
	    else if (cury+1<sizey && board[curx][cury+1]>board[curx][cury] ){
	        cury+=1;
	        //cout<<"down"<<endl;
	        moves.push_back(3);
	    }

	    while(curx!=endx || cury!=endy){
	        //left=0
	        if (curx-1>=0 && board[curx-1][cury]>board[curx][cury] ){
	            board[curx][cury]=-1;
	            curx-=1;
	            //cout<<"left"<<endl;
	            moves.push_back(0);
	        }
	        //up=1
	        else if (cury-1>=0 && board[curx][cury-1]>board[curx][cury] ){
	            board[curx][cury]=-1;
	            cury-=1;
	            //cout<<"up"<<endl;
	            moves.push_back(1);
	        }
	        //right=2
	        else if (curx+1<sizex && board[curx+1][cury]>board[curx][cury] ){
	            board[curx][cury]=-1;
	            curx+=1;
	            //cout<<"right"<<endl;
	            moves.push_back(2);
	        }
	        //down=3
	        else if (cury+1<sizey && board[curx][cury+1]>board[curx][cury] ){
	            board[curx][cury]=-1;
	            cury+=1;
	            //cout<<"down"<<endl;
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
