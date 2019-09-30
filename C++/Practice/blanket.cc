#include <iostream>
using namespace std;

void pr(int n){
    for (int i=0;i<n;i++){
        int rm=i%3;
        for(int j=0;j<n;j++){
            if (j%3==rm){
                cout<<"@";
            }
            else{
               cout<<"-"; 
            }
        }
        cout<<endl;
    }
}


int main(){
    int n;
    cin>>n;
    pr(n);
}