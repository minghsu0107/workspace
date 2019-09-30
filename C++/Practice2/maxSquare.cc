#include <iostream>
using namespace std;

int map[100][100];
int arr[100][100];

int min(int a,int b,int c){
    int min=(a<b)? a:b;
    min=(c<min)? c:min;
    return min;
}


int maxSide(int x,int y){
   int p=0;
   if(x==0 || y==0){
     return map[x][y]==0? 1:0;
   }
   if(arr[x][y]==-1){
       int a=maxSide(x-1,y);
       int b=maxSide(x,y-1);
       int c=maxSide(x-1,y-1);
       if(map[x][y]==0){
          arr[x][y]=min(a,b,c)+1;
       }
       else{
          arr[x][y]=0;
       }
   }
   return arr[x][y];
}


int main(){
    int H,W;
    cin>>H>>W;
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            int k;
            cin>>k;
            map[i][j]=k;
            arr[i][j]=-1;
        }
    }
    int p=0;
    maxSide(H-1,W-1);
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
           p=arr[i][j]>p? arr[i][j]:p;
        }
    }
    cout<<p*p<<endl;
}