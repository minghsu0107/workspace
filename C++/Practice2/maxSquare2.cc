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
   int max=0;
   for(int i=0;i<=x;i++){
       arr[i][0]=map[i][0]=0? 1:0;
       max=arr[i][0]>max? arr[i][0]:max;
   }
   for(int i=0;i<=y;i++){
       arr[0][i]=map[0][i]=0? 1:0;
       max=arr[0][i]>max? arr[i][0]:max;
   }
   for(int i=1;i<=x;i++){
       for(int j=1;j<=y;j++){
           arr[i][j]=map[i][j]==0? min(arr[i-1][j],arr[i][j-1],arr[i-1][j-1])+1:0;
           max=arr[i][j]>max? arr[i][j]:max;
       }
   }
   return max*max;
}


int main(){
    int H,W;
    cin>>H>>W;
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            int k;
            cin>>k;
            map[i][j]=k;
        }
    }
    int p=maxSide(H-1,W-1);
    cout<<p<<endl;
}