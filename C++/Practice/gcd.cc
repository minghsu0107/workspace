#include<iostream>
using namespace std;

int gcd1(int m,int n){
    if (m%n==0) return n;
    return gcd1(n,m%n);
}
int gcd2(int m,int n){
    while(n!=0){
        int tmp=m;
        m=n;
        n=tmp%n;
    }
    return m;
}
int gcd3(int m,int n){
    if (n==0) return m;
    return gcd3(n,m%n);
}
int main(){
    int m,n;
    cin>>m>>n;
    cout<<gcd1(m,n)<<endl;
    cout<<gcd2(m,n)<<endl;
    cout<<gcd3(m,n)<<endl;
}