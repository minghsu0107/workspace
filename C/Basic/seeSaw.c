#include <stdio.h>
int n, w[2050];
int check(int w[],int n){
   for(int i=1;i<n-1;i++){
       int sumleft = 0;
       for(int j=i;j>0;j--){
           sumleft+=w[i-j]*j;
       }
       int sumright = 0;
       for(int k=1;k<=n-i-1;k++){
           sumright+=w[i+k]*k;
       }
       if(sumleft==sumright) return i;
   } 
   return -1;
}
int main(){
   scanf("%d",&n);
   for(int i=0;i<n;i++){
       scanf("%d",&w[i]);
   }
   int k = check(w,n);
   int count=0;
   while(k<0){
       count++;
       int tmp = w[count-1];
       w[count-1] = w[n-count];
       w[n-count] = tmp;
       k = check(w,n);
   }
   for (int i=0; i<n; i++){
        if (i!= k)
            printf("%d%c", w[i], i!=n-1? ' ': '\n');
        else
            printf("v ");
    }
   return 0; 
}