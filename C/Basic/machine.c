#include <stdio.h>
int main(void){
    int arrival,ta,tb;
    int completion=0;
    int ra=0;
    int rb=0;
    while(scanf("%d%d%d",&arrival,&ta,&tb)!=EOF){
        int tmp;
        tmp=arrival>=ra? arrival:ra;
        ra=tmp+ta;
        tmp=ra>=rb? ra:rb;
        rb=tmp+tb;
        completion=rb;
        printf("%d\n",completion);
    }
    return 0;
}