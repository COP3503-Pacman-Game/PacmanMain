#include <iostream>
#include <fstream>

#include <vector>
using namespace std;
int main(int argc, char const *argv[]) {
  string line;
  int score;
  vector<string> nameVect;
  vector<int> scoreVect;
  ifstream myFile("scoreBoard.txt");
      if (!myFile) {
          cerr << "Input file can not be opened" << endl;
          exit(0);
      }
      string nextLine;
      int i = 0;
      while (getline(myFile, line, '\n')) {
          //cout << "*" << line << "*" <<endl;
          nameVect.push_back(line);
          getline(myFile, line, '\n');
          scoreVect.push_back(stoi(line));


i++;


  }
  for (int i=0; i<7;++i){
    cout<< nameVect.at(i)<<" "<<scoreVect.at(i)<<endl;
  }
string newname;
cin >> newname;
//here we did have cin for score

//cin>> score;



for (int j=0; j<scoreVect.size();++j){
  cout<<"getting here"<<endl;
  if (score>scoreVect.at(j)){
    nameVect.insert(nameVect.begin()+j, newname);
    scoreVect.insert(scoreVect.begin()+j, score);
    break;
  }
}
  for (int n=0; n<7;++n){
    cout<< nameVect.at(n)<<" "<<scoreVect.at(n)<<endl;
  }


  myFile.close();
  ofstream myOutFile("scoreBoard.txt");
    if (!myOutFile) {
      cerr << "Output file can not be opened" << endl;
      exit(0);
    }
    for (int i=0; i<7; i++) {
    myOutFile << nameVect.at(i)<< endl;
    myOutFile << scoreVect.at(i)<<endl;
  }
    myOutFile.close();

}
