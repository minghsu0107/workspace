#include <iostream>
using namespace std;

int numSet(int n){
    int count=1;
    while(n!=1){
      n=(n%2==0)? n/2 : 3*n+1;
      count+=1;
    }
    return count;
}
int main(){
    int N;
    cin>>N;
    cout<<numSet(N)<<endl;
}