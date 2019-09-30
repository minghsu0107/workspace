//#include "SpiralSnake.h"
#include <stdio.h>
#include <assert.h>
#define MAXLEN 1000
int A[MAXLEN][MAXLEN];
int dirXY[2][4] = { 0, -1, 0, 1,
                    -1, 0, 1, 0};
 
void SpiralSnake(int N, int *snake, int *result){
    int x, y;
    int dir = 0, flag = 0;
    int stepCount = 1, tmpCC = 1;
    x = y = N/2;
    result[x*N + y] = snake[0];
    for(int i=1; i< N*N; i++){
        x += dirXY[0][dir];
        y += dirXY[1][dir];
        result[x*N + y] = snake[i];
        tmpCC--;
        if(tmpCC == 0){
            dir = (dir + 1) % 4;
            if(flag==0)
                tmpCC = stepCount, flag++;
            else
                tmpCC = ++stepCount, flag = 0;
        }
    }
    return;
}
// 全域static變數代表其在程式執行期間一直存在
// 並表示其可以存取的範圍僅限該原始程式文件
// 亦可 static function() 表同樣意思
static int snake[MAXLEN*MAXLEN];
static int result[MAXLEN*MAXLEN];
// 在函式被宣告的static變數 在下次函式被呼叫時會記住上次離開函式的值
// 它會一直存在記憶體中 即使函式執行完畢仍不會消失
// 由於它仍是被宣告在函式中 所以函式外部仍無法存取
// 通常用作編號(static i=0; i++;)
int main(){
    int N;
    while(scanf("%d", &N)!=EOF){
        for(int i=0; i<N*N; i++)
              assert(scanf("%d", &snake[i])==1);
        SpiralSnake(N, snake, result);
        for(int i=0; i<N*N; i++)
             printf("%d%c", result[i], " \n"[i==N*N-1]);
    }
    return 0;
}