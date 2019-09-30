#include <iostream>
using namespace std;

void isprim(int n){
    int j=2;
    while(j*j<=n){
        if(n%j==0){
            cout<<"NO"<<endl;
            break;
        }
        j++;
    }
    if (j*j>n){
        cout<<"YES"<<endl;
    }
}

int main(){
    int n;
    cin>>n;
    isprim(n);
}