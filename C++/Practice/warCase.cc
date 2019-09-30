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
    int N;
    int A,B;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>A>>B;
        cout<<"Case "<<(i+1)<<": ";
        war(A,B);
    }
}