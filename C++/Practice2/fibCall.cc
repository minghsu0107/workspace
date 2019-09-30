#include <iostream>
using namespace std;

int call=0;
int count(int n){
    if(n==0){
        return 1;
    }
    else if(n==1){
        return 1;
    }
    else{
       return count(n-1)+count(n-2)+1;
    }
    
}

int fib(int n){
    call++;
    if(n==0){
        return 0;
    }
    else if(n==1){
        return 1;
    }
    else{
       return fib(n-1)+fib(n-2);
    }
}

int main(){
    int n;
    cin>>n;
    cout<<fib(n)<<" "<<count(n);
    cout<<" "<<call;
}