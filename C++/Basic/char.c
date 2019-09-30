#include <stdio.h>
#include <string.h>
int main(void) {
    
    char str[20];
    puts("請輸入字串："); 
    fgets(str, sizeof(str), stdin);

    puts("輸入的字串為：");
    puts(str); //輸出字串後，會直接進行換行
    printf("%d",strlen(str));
    
    
    char c;
    printf("請輸入一個字元：");
    c = getchar(); 
    //如果輸入了兩個以上的字元，則 getchar() 會取得第一個字元，
    //並將第二個字元留在緩衝區中，直到再使用 getchar() 或 scanf() 取得輸入。

    putchar(c); //輸出一個字元
    putchar('\n');


    return 0;
}