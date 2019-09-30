#include <stdio.h>
int n,m;
int arr[100][100];
void move(int i,int j,int flag){
   int way=0;
   switch(flag){
     case 1:
       while(i!=-1 && j!=m){
         if(!way){
           if(arr[i][j]){
             j++;
             way=1;
           }else{
             i--;
           }
         }else{
           if(arr[i][j]){
             i--;
             way=0;
           }else{
             j++;
           }
         }
       }
       break;
     case 2:
       while(i!=n && j!=-1){
         if(!way){
           if(arr[i][j]){
              i++;
              way=1;
           }else{
              j--;
           }
         }else{
           if(arr[i][j]){
              j--;
              way=0;
           }else{
              i++;
           }
         }
       }
       break;
     case 3:
       while(i!=n && j!=-1){
         if(!way){
           if(arr[i][j]){
             j--;
             way=1;
           }else{
             i++;
           }
         }else{
           if(arr[i][j]){
             i++;
             way=0;
           }else{
             j--;
           }
         }
       }
       break;
     case 4:
       while(i!=-1 && j!=m){
         if(!way){
           if(arr[i][j]){
             i--;
             way=1;
           }else{
             j++;
           }
         }else{
           if(arr[i][j]){
             j++;
             way=0;
           }else{
             i--;
           }
         }
       }
       break;
     default:
       break;
   }
   if(i==n) printf("%d\n",j);
   if(j==m) printf("%d\n",m+n-1-i);
   if(i==-1) printf("%d\n",2*m+n-1-j);
   if(j==-1) printf("%d\n",i+2*m+n);
}
int main(){
  scanf("%d%d",&m,&n);
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
       scanf("%d",&arr[i][j]);
    }
  }
  for(int j=0;j<m;j++){
    move(n-1,j,1);
  }
  for(int i=n-1;i>=0;i--){
    move(i,m-1,2);
  }
  for(int j=m-1;j>=0;j--){
    move(0,j,3);
  }
  for(int i=0;i<n;i++){
    move(i,0,4);
  }
  return 0;
}