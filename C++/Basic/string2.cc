#include <iostream>
#include <string>
using namespace std;

int main() {
  string a = "stone ";
  string b("is fun");
  cout << a + b << endl;
  cout << b + "\n" << endl;
  
  string s("abc");
  char x = s[0];
  char y = s[1];
  char z = s[2];
  cout<<x<<" "<<y<<" "<<z<<endl;
  
  cout << "\"Hello\""<<endl;  // 印出 "Hello"
  cout << "\'\\Hello\?\'"<<endl;  // 印出 '\Hello?'
  printf("%%\n");
  
  string ar("apple");  
  if (ar.compare("apple") == 0) cout << "is apple" << endl;
  if (ar.compare("banana") < 0) cout << "not banana" << endl;
  
  
  string st("Stone is fun");
  // should print "Stone"
  cout << st.substr(0, 5) << endl;//從字串的第 0 個位置開始取得長度為 5 的子字串
  
  string str("Learn Stone, have fun.");
  int pos = str.find("Stone");
  if (pos != string::npos) {
    cout << pos << endl;
  } 
  else {
    cout << "not found" << endl;
  }
  
    string str1; 
    string str2("caterpillar"); 
    string str3(str2); 
    
    if(str1.empty()) {
        cout << "str1 為空字串" << endl;
    }
    cout << "str1 長度: " << str1.size() << endl;
    cout << "str2 長度: " << str2.size() << endl;
    cout << "str3 長度: " << str3.size() << endl;
    
    if(str3 == str2) {
        cout << "str3 與 str2 內容相同" << endl;
    }
    // assign: 指定字串 
    str1 = str1.assign(str2, 0, 5); 
    cout << "str1: " << str1 << endl; 
    str1 = str1.assign("caterpillar", 5, 6); 
    cout << "str1: " << str1 << endl; 

    str1 = ""; 

    // append: 字串串接 
    str1 = str1.append(str2, 0, 5); 
    str1 = str1.append(str3, 5, 6); 
    cout << "str1: " << str1 << endl; 

    // find: 尋找字串位置 
    cout << "尋找str1中的第一個pill: " << str1.find("pill", 0) << endl; 

    // insert: 插入字串 
    cout << "在str1插入字串***: " 
         << str1.insert(5, "***") << endl; //在第5個後面塞***

    cout << "str1長度: " << str1.length() << endl; 

    for (int i=0;i<str1.length();i++){
      cout<<str1[i]<<" ";
      //cout<<*(str1+i)<<" "; error
    }
    cout<<endl;

}