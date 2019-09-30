#include <iostream>
using namespace std;

void tower(int n, int a,int b,int c){
    if(n==1){
       cout<<"Ring "<<n<<" from "<<a<<" to "<<c<<endl; 
    }
    
    else{
       tower(n-1,a,c,b);
       cout<<"Ring "<<n<<" from "<<a<<" to "<<c<<endl;  
       tower(n-1,b,a,c);
    }
}

int main(){
    int n;
    cin>>n;
    tower(n,1,2,3);
}