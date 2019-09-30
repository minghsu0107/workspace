#include <stdio.h>
int gcd(int a,int num){ return ((num==0)? a:gcd(num,a%num));}
int value(int type, int width, int height, int length){
   if(width<=0 || height<=0 || length<=0) return -2;
   int typ[]={79,47,29,82,26,22};
   int val[]={30,10,4,5,3,9};
   int index=-1;
   for(int i=0;i<6;i++){
      if(type==typ[i]){
         index=i;
         break;
      }
      else if(i==5) return -1;
   }
   int side=gcd(width,height);
   side=gcd(side,length);
   int vol=side*side*side;
   int p=vol*vol*val[index];
   return p*(width/side)*(height/side)*(length/side);
}
int main(){
    int type, width, height, length;
    scanf("%d%d%d%d",&type,&width,&height,&length);
    int k = value(type,width,height,length);
    printf("%d\n",k);
}