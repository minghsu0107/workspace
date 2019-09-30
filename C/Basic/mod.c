#include <stdio.h>
int main(){
  int len,m;
  scanf("%d",&len);
  int arr[262144]={};
  
  int num[len];
  for(int i=0;i<len;i++){
      scanf("%d",&num[i]);
  }
  
  scanf("%d",&m);
  for(int i=0;i<len;i++){
    arr[num[i]%m]++;
  }
//  for(int i=0;i<len;i++){
//    printf("%d\n",num[i]);
//  }
  for(int i=0;i<m;i++){
    printf("%d\n",arr[i]);
  }
  return 0;
}
