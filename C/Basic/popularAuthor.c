#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
char au_bk[128][128][64];
int au_bk_num[128]={0};
char bk_sell[128][2][64];
int au_num=0;
int main()
{
        int M;
        char author[64],book[64];
        scanf("%d",&M);
//step1
        for(int i=0;i<M;i++)
        {
                scanf("%s%s",author,book);
                int find=0;
                for(int j=0;j<au_num;j++)
                {
                        if(strcmp(au_bk[j][0],author)==0)
                        {
                                find=1;
                                strcpy(au_bk[j][au_bk_num[j]+1],book);
                                au_bk_num[j]++;
                        }
                }
                if(find==0)
                {
                        strcpy(au_bk[au_num][0],author);
                        strcpy(au_bk[au_num][au_bk_num[au_num]+1],book);
                        au_bk_num[au_num]++;
                        au_num++;
 
                }
        }
//step1 end
        char selling[64];
//step2
        for(int i=0;i<M;i++)
        {
                scanf("%s%s",book,selling);
                strcpy(bk_sell[i][0],book);
                strcpy(bk_sell[i][1],selling);
        }
//step2 end
        int max=INT_MIN;
        char best[64];
//step3
        for(int i=0;i<au_num;i++)
        {
                int selling=0;
                for(int j=1;j<=au_bk_num[i];j++)
                {
                        for(int k=0;k<M;k++) if(strcmp(au_bk[i][j],bk_sell[k][0])==0) {selling+=atoi(bk_sell[k][1]);}
                }
                if(selling>max) {max=selling;strcpy(best,au_bk[i][0]);}
                else if(selling==max&&strcmp(au_bk[i][0],best)<0) {strcpy(best,au_bk[i][0]);}
        }
        printf("%s %d\n",best,max);
//step3 end
        return 0;
}
