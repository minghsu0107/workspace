#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    cin>>s;
    int len=s.length();
    char str[len+1];
    for (int i=0;i<len;i++){
        int a=s[i]-2-'A'; //以整數表示字元內容(利用字元相加減)
        int b=0;
        if (a<0){
            b=a+26;
        }
        else{
            b=a;
        }
        str[i]=static_cast<char>('A'+b);
    }
    str[len]='\0';
    cout<<str;
}