#include <iostream>
#include <math.h>
using namespace std;

int pnum(int n,int m){
    int sum=1;
    for (int i=0;i<m;i++){
        sum*=n--;
    }
    return sum;
}

int main(){
    int N;
    int M;
    cin>>N>>M;
    cout<<pnum(N,M)<<endl;
}