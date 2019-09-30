#include <iostream>
using namespace std;

int gtime(int n,int m){
    int time=0;
    while(n<m){
        n*=3;
        time+=1;
    }
    return time;
}

int main(){
    int N;
    int M;
    cin>>N>>M;
    cout<<gtime(N,M)<<endl;
}