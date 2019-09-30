#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//ptr[i] 等價於 *(ptr+i)
//ptr[i][j] 等價於 *(*(ptr+i) + j)
//ptr[i][j][k] 等價於 *(*(*(ptr+i) + j) + k)
void processSetMatrix(int ***ptr) {
    int f = 0;
    for (int i = 0; ptr[i]; i++) {
        for (int j = 0; ptr[i][j]; j++) {
            for (int k = 0; ptr[i][j][k]; k++) {
                int v = ptr[i][j][k];
                if (f)    putchar(' ');
                printf("%d", v);
                f = 1;
            }
        }
    }
    puts("");
} 
int main() {
    int n;
    scanf("%d", &n);
    {
        int ***setmtx = (int ***) malloc(sizeof(int**) * (n + 1));
        int setarr_sz, set_sz;
        setmtx[n] = NULL;
        for (int i = 0; i < n; i++) {
            scanf("%d", &setarr_sz);
            setmtx[i] = (int **) malloc(sizeof(int *) * (setarr_sz + 1));
            setmtx[i][setarr_sz] = NULL;
            for (int j = 0; j < setarr_sz; j++) {
                scanf("%d", &set_sz);
                setmtx[i][j] = (int *) malloc(sizeof(int) * (set_sz + 1));
                setmtx[i][j][set_sz] = 0;
                for (int k = 0; k < set_sz; k++) {
                    scanf("%d", &setmtx[i][j][k]);
                    assert(setmtx[i][j][k] != 0);
                }
            }
        }
        processSetMatrix(setmtx); // 不能直接傳一個多維陣列 只能傳指標對應指標 
                                  // 但 int* ptr 可以指向一個整數一維陣列
  
    }
    return 0;
}
