#include <iostream>
using namespace std;

int pr(int n){
    int k=1;
    for(int i=1;i<=n;i++){
        k%=100;
        k*=13;
    }
    k=(k-k%10)/10;
    return (k%10);
}

int main(){
    int n;
    cin>>n;
    cout<<pr(n)<<endl;
}