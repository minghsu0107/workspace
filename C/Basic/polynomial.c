#include <stdio.h>
int main(void){
  int alen,blen;
  int a[105],b[105];
  scanf("%d",&alen);
  for(int i=0;i<alen;i++){
    scanf("%d",&a[i]);
  }
  scanf("%d",&blen);
  for(int i=0;i<blen;i++){
    scanf("%d",&b[i]);
  }
  int c[210]={};
  for(int i=0;i<alen;i++){
    for(int j=0;j<blen;j++){
       c[i+j]+=a[i]*b[j];
    }
  }
  int clen=alen+blen-1;
  for(int i=0;i<clen;i++){
    if(i!=0) printf(" %d",c[i]);
    else printf("%d",c[i]);
  }
  return 0;
}