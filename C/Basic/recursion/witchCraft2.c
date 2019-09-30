#include <stdio.h>
int D, a, b, c, A, B, C, done;
void judge(int mp, int stg){
    if (mp < 0) return;
    if (done) return;
    switch (stg){
        case 2:
            if (!c || !C) return;
            if (!done && mp % C == 0 && mp / C <= c){
                done = 1; 
                return;
            }
            break;
        case 1:
            for (int i = 0; i <= b && mp >= 0 && !done; i++){
                if (!mp){
                    done = 1; 
                    return;
                }
                judge(mp, stg+1);
                mp -= B;
            }
            break;
        case 0:
            for (int i = 0; i <= a && mp >= 0 && !done; i++){
                if (!mp) {
                    done = 1; 
                    return;
                }
                judge(mp, stg+1);
                mp -= A;
            }
            break;
    }
}
int main(){
    int n;
    scanf("%d", &n);
    while (n--){
        scanf("%d%d%d%d%d%d%d", &D, &a, &b, &c, &A, &B, &C);
        done = 0;
        judge(D, 0);
        if (done) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}
