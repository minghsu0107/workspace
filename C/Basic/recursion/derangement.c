#include <stdio.h> 
#include <string.h> 
int Used[16], rule[16][16], l[16];
char Ans[16];
void perm(int d,int N) { 
 
    if (d==N) { 
        Ans[d] = '\0';  
        puts(Ans);
        return;  
    }  
    for (int i = 0; i < N; i++) {   
        if (Used[i]) continue;
        int invalid = 0;
        for (int j = 0; j < l[i]; j++) {
            if(d == rule[i][j]) {
                invalid = 1;
                break;
            } 
        }
        if (invalid) continue;
        Used[i] = 1;  
        Ans[d] = i + 'A';
        perm(d+1, N); 
        Used[i] = 0;  
    }  
} 
int main() {   
    int n, m;  
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(l, 0, sizeof(l));
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d",&a, &b); 
            rule[a-1][l[a-1]++] = b-1;
        }
        perm(0,n);  
    }
    return 0;
}