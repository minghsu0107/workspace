#include <iostream>
#include <string.h>
#include <string>
using namespace std;

int main(){
  char s[] = "ahello";
  cout<<s<<endl;
  cout<<s+1<<endl;
  cout<<"&s:"<<&s<<endl;
  cout<<"&*s:"<<&*s<<endl;
  cout<<"*(s+1):"<<*(s+1)<<endl;
  cout<<"*s+1: "<<*s+1<<endl;
  cout<<"&s[0]:"<<&s[0]<<endl;
  
  string a("hello");
  cout<<a<<endl;
  const char *st = a.c_str();// 將string 初始成char squence
  for(const char* q=st;q!=st+strlen(st);q++){
    cout<<*q;
  }
  cout<<endl;
  for(int i=0;i<strlen(st);i++){
    cout<<st[i];
  }
  cout<<endl;
  for (int i=0; s[i]!='\0'; i++) {
    cout << (int)s[i] << ":" << s[i]<<" ";
    cout<<*(s+i)<<endl;
  }
  
  for (int i=0; i<strlen(s); i++) {
    int code = s[i] - 'a';  //以整數表示字元內容(利用字元相加減)
    cout << code << ":" << s[i] << "," << endl;
  }
  
  char *p=s;
  cout<<"&p: "<<&p<<endl<<"p+1: "<<p+1<<endl;//&p代表p指標的位址
  int leng = strlen(s);
  cout<<s+leng-1<<endl;
  for (char *q=s; q != s + leng; q++) {
    cout << q << ": " << *q << endl;
  }
  for (int i=0; i<leng; i++) {
    cout << i << ": " << *(p++) << endl;//*(p+i)也可以 但不改變p內容
  }
  cout<<*p<<endl;//p指到最後一位 即'\0'

  char num[] = "1234";
  int d = 0;
  for (int i=0; i<4; i++) {
    d = d * 10 + (num[i] -'0');//以整數表示字元內容(利用字元相加減)
  }
  cout << "d: " << d << endl;
}