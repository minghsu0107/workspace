#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0) 
char _;
char **F[1024]; //  representing the first table, stores the address of the begining of each line
char *S[16384]; //  representing the second table, stores the address of all words.
char W[10000000];  // stores all the words.
int nF[1024];  // stores the number of words in each line.
 // Since global array would be initialized to be 0 at the begining,
 // the code below doesn't need to put a \0, and just add 1 more space after stroing a string.
int main(){
    int N;
    scan(N);
    int nW = 0, pos = 0;
    for (int i=0; i<N; i++){
        char _t;
        F[i] = &S[nW];
        while (scanf("%s%c", &W[pos], &_t)==2){
            S[nW] = &W[pos];
            nW++;
            nF[i]++;
            pos += strlen(&W[pos]) + 1;
            if (_t == '\n')
                break;
        }
    }
 
    int M;
    scan(M);
    for (int i=0; i<M; i++){
        int l1, w1, l2, w2;
        scanf("%d %d %d %d", &l1, &w1, &l2, &w2);
        char *tmp = F[l1][w1];
        F[l1][w1] = F[l2][w2];
        F[l2][w2] = tmp;
    }
 
    for (int i=0; i<N; i++, puts("")){
        for (int j=0; j<nF[i]; j++){
            if (j==0)
                printf("%s", F[i][j]);
            else
                printf(" %s", F[i][j]);
        }
    }
    return 0;
}