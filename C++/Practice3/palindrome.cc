#include <iostream>
#include <string>
using namespace std;

void judge(string s){
    int len=s.length();
    bool det=true;
    for (int i=0;i<len/2;i++){
        if (s[i]!=s[len-1-i]){
            cout<<"NO";
            det=false;
            break;
        }
    }
    if(det==true) cout<<"YES";
}

int main(){
    string s;
    cin>>s;
    judge(s);
}