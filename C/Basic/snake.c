#include <stdio.h>
int snake(int *ptr, int *row, int *column){
    if(ptr[0]!=0) {
        *row = 0, *column = 0;
        return 0;
    }
    if(ptr[1]!=1) {
        *row = 0, *column = 1;
        return 0;
    }
    int maxrnum = 1, r = 0;
    int maxcnum = 2, c = 1; 
    int dir=1, flag=1;
    for(int i=2;ptr[i];i++){
       if(dir==1){
          if(ptr[i]==ptr[i-1]+1){
              if(flag) maxcnum++;
              else if(c==maxcnum-1){
                  *row = r+1, *column = c;
                  return 0;
              }
              c++;
          }
          else if(ptr[i]==ptr[i-1]+maxcnum){
              if(c!=maxcnum-1){
                  *row = r, *column = c+1;
              }
              maxrnum++;
              r++;
              dir=0;
              flag=0;
          }
          else if(c<maxcnum-1){
              *row = r, *column = c+1;
              return 0;
          }
          else if(c==maxcnum-1){
              *row = r+1, *column = c;
          }
       }else if(dir==0){
          if(ptr[i]==ptr[i-1]-1){
              if(c==0){
                  *row = r+1, *column = c;
                  return 0;
              }
              c--;
          }
          else if(ptr[i]==ptr[i-1]+maxcnum){
              if(c!=0){
                  *row = r, *column = c-1;
                  return 0;
              }
              maxrnum++;
              r++;
              dir=1;
          }
          else if(c>0){
              *row = r, *column = c-1;
              return 0;
          }
          else if(c==0){
              *row = r+1, *column = c;
              return 0;
          }
       }
    }
    *row = maxrnum, *column = maxcnum;
    return 1;
}
int main(void)
{
    int trav[1024] = {0}, row = 0, column = 0, res = 0;
    scanf("%d %d", &trav[0], &trav[1]);
    for(int i = 1; trav[i]; i++)
      scanf("%d", &trav[i + 1]);
    res = snake(trav, &row, &column);
    if(res) printf("%d %d\n", row, column);
    else printf("err %d %d\n", row, column);
    return 0;
}