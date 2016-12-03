#include <iostream>
#include <math.h>
#include <vector>
#include <stdbool.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <queue>
#include <windows.h>
#include <cmath>
#include <ctime>

using namespace std;
int score;
//bool gameOver;

//Gamestates
const int RIGHT = 1;
const int LEFT = 3;
const int UP = 0;
const int DOWN = 2;
const int NEW_GAME = 204;
const int QUIT = 205;
const int PAUSE = 206;
const int RESUME = 207;
const int HOLD = 208;
const int WIN_GAME = 209;

//Variables on the board
const int WALL = 0;
const int EMPTY = 1;
const int DOT = 2;
const int SPECIAL_DOT = 3;
const int FRUIT = 6;
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
	{ WALL  ,SPECIAL_DOT,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,SPECIAL_DOT ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY },
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY/*PINKY*/ ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY/*INKY*/  ,EMPTY/*BLINKY*/,EMPTY/*CLYDE*/ ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY },
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY, EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY },
	{ WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,WALL  ,EMPTY ,WALL },
	{ WALL  ,SPECIAL_DOT,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,SPECIAL_DOT,WALL },
	{ WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL  ,EMPTY ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,EMPTY ,WALL },
	{ WALL  ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,EMPTY ,WALL },
	{ WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL , WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL  ,WALL }
	};



struct Player
{
	int locationRow, locationCol, lives;
	double movementTimer;
	Player()
	{
		locationRow = 16;
		locationCol = 9;
		//lives = 3;
	}
};


void generateFruit(){
	bool validLoc= false;
	while(validLoc == false){
		int locFruitRow = rand() % 22;
		int locFruitCol = rand() % 19;
		int element = GameBoard[locFruitRow][locFruitCol];
		if (element==WALL || element==PACMAN || element==INKY || element==PINKY || element==CLYDE  || element==BLINKY || element == SPECIAL_DOT){
			validLoc = false;
		}
		else if((locFruitRow == 8 || locFruitRow == 12) && ((locFruitCol >= 0 && locFruitCol <= 2) || (locFruitCol <= 18 && locFruitCol >= 16))){
			validLoc = false;
		}
		else if (locFruitCol >= 5 && locFruitCol <= 13 && locFruitRow >= 7 && locFruitRow <= 13) {
			validLoc = false;
		}
		else{
			GameBoard[locFruitRow][locFruitCol] = FRUIT;
			validLoc = true;
		}
	}
}


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
		//GameBoard[10][18] = WRAPR;
		//GameBoard[10][19] = WRAPL;
	//}

	int element = GameBoard[x][y];

	if (element == WALL) {
		return false;
	}
	else if ((element == BLINKY) || (element == PINKY) || (element == INKY) || (element == CLYDE)) {
		//gameOver = true;
		return false;
	}
	else if (element == DOT) {
		score++;
	}
	else if (element == SPECIAL_DOT) {
		score+=10;
		//!!!Need somehow to set ghosts to edible!!!
	}
	else if (element == FRUIT) { //fixed fruit
		score += 10;

	}

	GameBoard[player.locationRow][player.locationCol] = EMPTY; //current position becomes empty
	player.locationRow = x; player.locationCol = y;
	GameBoard[player.locationRow][player.locationCol] = PACMAN; //desired position becomes player
	return true;

	}


		int solve(int starty, int startx, int endx, int endy, int boardold[22][19]) {
		int board[22][19];


//1,1 3,1 1,20
		int temp=starty;
		starty=18-startx;
		startx=temp;

//9,16 16,9
		temp=endy;
		endy=18-endx;
		endx=temp;

		
/*
		int board [19][22];

for(int i=0; i<19; i++) {
    for(int j=0; j<22; j++) {
        board[i][j] = boardold[22-1-j][i];
    }
}
*/



	    for (int i=0;i<22;i++)
	       for (int j=0; j<19;j++)
	           if (boardold[i][j] > 0 )
	               board[i][j] =1;
	           else
	           		board[i][j]=0;






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

void clearScreen() //Fixed the flicker, god bless Bao
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}