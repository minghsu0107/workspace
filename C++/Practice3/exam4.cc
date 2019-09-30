#include<iostream>
#include<algorithm>
using namespace std;

int Seq[100];
int Math[100];
int Total[100];


bool cmp(int a, int b){
    if(Total[a-1]==Total[b-1]){
         return Math[a-1] > Math[b-1];
      }
    return Total[a-1] > Total[b-1];
}



void exam2(int Seq[],int n){
    sort(Seq,Seq+n,cmp);
    for(int i=0;i<n;i++){
        cout<<Seq[i]<<endl;
    }
}
int main(){
    int n;
    cin>>n;
    int len=0;
    for(int i=0;i<n;i++){
      int seq,math;
      int sum=0;
      cin>>seq;
      Seq[len]=seq;
      for(int j=0;j<5;j++){
        if(j==2){
          cin>>math;
          Math[len]=math;
          sum+=math;
        }
        else{
          int k;
          cin>>k;
          sum+=k;
        }
      }   
      Total[len]=sum;
      len++;
    }
    exam2(Seq,len);
}