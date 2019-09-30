#include <iostream>
using namespace std;

int evenN(int n){
    while(n%2==0){
        n/=2;
    }
    return n;
}

int main(){
    int n;
    cin>>n;
    cout<<evenN(n)<<endl;
}