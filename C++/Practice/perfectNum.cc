#include <iostream>
using namespace std;

void pf(int n){
    int sum=1;
    for (int i=2;i*i<=n;i++){
        if(n%i==0){
            sum+=i+(n/i);
        }
    }
    if (sum>n){
        cout<<"Abundant"<<endl;
    }
    else if(sum<n){
        cout<<"Deficient"<<endl;
    }
    else{
        cout<<"Perfect"<<endl;
    }
}

int main(){
    int n;
    cin>>n;
    pf(n);
}
