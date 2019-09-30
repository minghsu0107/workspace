#include <iostream>
using namespace std;

void isIn(int arr[],int len){
    for(int i=1;i<=len;i++){
        if (arr[i]==0){
            cout<<i<<" ";
        }
    }
}

int main(){
    int N,M;
    cin>>N>>M;
    int arr[25]={};
    for(int i=0;i<M;i++){
        int num;
        cin>>num;
        arr[num]=num;
    }
    isIn(arr,N);
}