#include <stdio.h>
#include <ctype.h>
void prASCII16(){
    char c;
    int i, j;
    printf("   0123456789abcdef\n");
    for(i = 2; i <= 7; i++){
        for(j = 0; j <= 15; j++){
            c= i * 16 + j;
            if(c % 16 ==0) printf("%2d ",c / 16);
            if(isprint(c)) printf("%c", c);
            else printf(" ");
        }
        printf("\n");
    }
    return;
}
void printASCII10(){
    int c;
    printf("   0123456789\n");
    for(c = 30; c <= 127; c++){
        if(c%10 == 0)
           printf("%2d ", c / 10);
        if(isprint(c))  // 可顯示字元(包含空白) v.s. isgraph 可顯示字元(不含空白)
           printf("%c", c);
        else
           printf(" ");
        if(c % 10 == 9)
           printf("\n");
    }
    return;
}
int main(){
    prASCII16();
    printf("\n");
    printASCII10();
    return 0;
}