#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
  //ctrl-d結束迴圈 
  int val;  // change string to int
  string str("1234567");
  istringstream is(str);//input a string to is 
  is>>val;//read by integer
  cout<<val<<endl;
  is.str("");// clean is
  is.clear();// 可繼續讀取
  
  //讀取多行, 每讀取一行, 將它分解成一個一個單字
  int nlines = 0;
  string line, word;
  while (getline(cin, line)) {
    ++nlines;
    istringstream iss(line); //input a line to iss(a line contains a set of strings)
    while (iss >> word) {    //read by string
      cout << nlines << ": " << word << endl;
    }
  }
  
}