#include <iostream>
#include <string>
#include <vector>
using namespace std;

void pt(string s){
    vector<int> vec;
    for(int i=0;i<s.length();i++){
        switch(s[i]){
        case 'I':
          vec.push_back(1);
          break;
        case 'V':
          vec.push_back(5);
          break;
        case 'X':
          vec.push_back(10);
          break;
        case 'L':
          vec.push_back(50);
          break;
        case 'C':
          vec.push_back(100);
          break;
        case 'D':
          vec.push_back(500);
          break;
        case 'M':
          vec.push_back(1000);
          break;
        default:
          cout<<"ERROR"<<endl;
        }
    }
    int sum=0;
    int len=vec.size();
    int k=0;
    for(int i=0;i<len-1;i+=k){
        if(vec[i]<vec[i+1]){
            sum+=vec[i+1]-vec[i];
            k=2;
        }
        else{
            sum+=vec[i];
            k=1;
        }
    }
    if(!(vec[len-2]<vec[len-1])) sum+=vec[len-1];
    cout<<sum<<endl;
}

int main(){
   string s;
   cin>>s;
   pt(s);
}