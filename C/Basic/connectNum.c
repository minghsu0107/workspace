#include <stdio.h>
int in , max = 0 , last = -1 , len = 0;
int main(){
    while(scanf("%d" , &in)!=EOF){
        int fr , thisback = in % 10 , siz = 0;
        while(in > 0) fr = in % 10 , in /= 10 , siz ++;
        len = (fr == last) ? len + siz : siz;
        last = thisback;
        if(len > max) max = len;
    }
    printf("%d\n", max);
    return 0;
}