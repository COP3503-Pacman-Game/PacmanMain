#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> solve(int startx, int starty, int endx, int endy, int board[22][19]) {
    
    
    
    
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
    Xloc.emplace(startx);
    Yloc.emplace(starty);
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
                Xloc.emplace(X-1);
                Yloc.emplace(Y);
            }
            nott = false;
        }
        //up
        if (Y-1>=0 && board[X][Y-1]==1){
            //cout<<"got up ";
            board [X][Y-1] =board[X][Y]+1;
            if (!(X==endx && Y-1==endy)){
                Xloc.emplace(X);
                Yloc.emplace(Y-1);
            }
            nott = false;
        }
        //right
        if (X+1<sizex && board[X+1][Y]==1){
            //cout<<"got right ";
            board [X+1][Y] =board[X][Y]+1;
            if (!(X+1==endx && Y==endy)){
                Xloc.emplace(X+1);
                Yloc.emplace(Y);
            }
            nott = false;
        }
        //down
        if (Y+1<sizey && board[X][Y+1]==1){
            board [X][Y+1] =board[X][Y]+1;
            //cout<<"got down ";
            if (!(X==endx && Y+1==endy)){
                //cout<<Y+1<<endl;
                Xloc.emplace(X);
                Yloc.emplace(Y+1);
                
            }
            nott = false;
        }
        //cout<<endl;
        if (nott){
            Xdes.emplace(X);
            Ydes.emplace(Y);
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
                Xdes.emplace(XD-1);
                Ydes.emplace(YD);
            }
            if (YD-1>=0 && board[XD][YD-1]!=0){
                Xdes.emplace(XD);
                Ydes.emplace(YD-1);
            }
            if (XD+1<sizex && board[XD+1][YD]!=0){
                Xdes.emplace(XD+1);
                Ydes.emplace(YD);
            }
            if (YD+1<sizey && board[XD][YD+1]!=0){
                Xdes.emplace(XD);
                Ydes.emplace(YD+1);
            }
        }
    }
    vector <int>moves ;
    int curx=startx;
    int cury=starty;
    //left=0
    if (curx-1>=0 && board[curx-1][cury]>board[curx][cury] ){
        curx-=1;
        cout<<"left"<<endl;
        moves.push_back(0);
    }
    //up=1
    else if (cury-1>=0 && board[curx][cury-1]>board[curx][cury] ){
        cury-=1;
        cout<<"up"<<endl;
        moves.push_back(1);
    }
    //right=2
    else if (curx+1<sizex && board[curx+1][cury]>board[curx][cury] ){
        curx+=1;
        cout<<"right"<<endl;
        moves.push_back(2);
    }
    //down=3
    else if (cury+1<sizey && board[curx][cury+1]>board[curx][cury] ){
        cury+=1;
        cout<<"down"<<endl;
        moves.push_back(3);
    }
    
    while(curx!=endx || cury!=endy){
        //left=0
        if (curx-1>=0 && board[curx-1][cury]>board[curx][cury] ){
            board[curx][cury]=-1;
            curx-=1;
            cout<<"left"<<endl;
            moves.push_back(0);
        }
        //up=1
        else if (cury-1>=0 && board[curx][cury-1]>board[curx][cury] ){
            board[curx][cury]=-1;
            cury-=1;
            cout<<"up"<<endl;
            moves.push_back(1);
        }
        //right=2
        else if (curx+1<sizex && board[curx+1][cury]>board[curx][cury] ){
            board[curx][cury]=-1;
            curx+=1;
            cout<<"right"<<endl;
            moves.push_back(2);
        }
        //down=3
        else if (cury+1<sizey && board[curx][cury+1]>board[curx][cury] ){
            board[curx][cury]=-1;
            cury+=1;
            cout<<"down"<<endl;
            moves.push_back(3);
        }else{
            cout<<"error in path"<<endl;
            break;
            
        }
        
        
    }
    cout<<"Finished solve";
    /*
     while(true){
     repaint();
     try{
     t1.sleep(50);
     }
     catch(InterruptedException e){}
     }
     */
    
    return moves;
}
