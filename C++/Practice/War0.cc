#include <iostream>
using namespace std;

void war(int a,int b){
    if (a>b){
        cout<<"A"<<" "<<(a-b)<<endl;
    }
    else if(a<b){
        cout<<"B"<<" "<<(b-a)<<endl;
    }
    else{
        cout<<0<<endl;
    }
    
}

int main(){
    int A,B;
    while(cin>>A>>B){
        if(A==0&&B==0) break;
        war(A,B);
    }
}