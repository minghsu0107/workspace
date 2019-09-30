#include <stdio.h>
#include <limits.h>
#define MAX 14
int dist[MAX][MAX] = {};
int went[MAX] = {1,0};
int N;
int route = INT_MAX;
void find(int d, int now, int visited){
    if(d >= route) return; //cut（目前累加路徑大於最佳路徑則直接return)
    if(visited == N){      //check if all went
        d += dist[now][0]; // go back to the starting point
        if(d < route)
        route = d;
        return;
    }
    for(int i = 1; i < N; i++){    //recursive permutation
        if(!went[i]){
            went[i] = 1;
            find(d + dist[now][i], i, visited + 1);
            went[i] = 0;
        }
    }
}
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &dist[i][j]);
    find(0, 0, 1); 
    // choose city 0 as the starting(finishing) point
    // so city 0 is already visited => visited start from 1
    printf("%d", route);
    return 0;
}
// 因最短路徑經過每點剛好一次，所以不管選哪個點作為起點最短路徑長度皆相同
// 故只需選定一點當作起點及終點，則只需要O((n-1)!)的時間