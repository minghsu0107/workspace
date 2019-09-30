#include <stdio.h>
#include <stdlib.h>
#define MAXM 65536
#define MAXN 2147483647
typedef struct {
    int x, y;
} Attraction;
int min(int a,int b){
    if(a < b) return a;
    return b;
}
int N, M;
int check(int a1,int a2,int a3,int a4){
    if(a1 <= a2 && a1 <= a3 && a1 <= a4) return 1;
    if(a2 <= a1 && a2 <= a3 && a2 <= a4) return 2;
    if(a3 <= a1 && a3 <= a2 && a3 <= a4) return 3;
    if(a4 <= a1 && a4 <= a2 && a4 <= a3) return 4;
    return 0;
}
int cmp(const void *a,const void *b){
    Attraction *c = (Attraction *)a;
    Attraction *d = (Attraction *)b;
    int circle1 = min(min(c->y, N-1-c->x), min(N-1-c->y, c->x));
    int circle2 = min(min(d->y, N-1-d->x), min(N-1-d->y, d->x));
    if(circle1 > circle2) return 1;
    if(circle1 == circle2){
        int edge1 = check(c->y, N-1-c->x, N-1-c->y, c->x);
        int edge2 = check(d->y, N-1-d->x, N-1-d->y, d->x);
        if(edge1 > edge2) return 1;
        if(edge1 == edge2 && edge1 == 1 && c->x > d->x) return 1;
        if(edge1 == edge2 && edge1 == 2 && c->y > d->y) return 1;
        if(edge1 == edge2 && edge1 == 3 && c->x < d->x) return 1;
        if(edge1 == edge2 && edge1 == 4 && c->y < d->y) return 1;
    }
    return -1;
}
int main(int argc,char *argv[])
{
    FILE *fin = fopen(argv[1], "rb");
    scanf("%d %d", &N, &M);
    Attraction attr[M];
    for(int i=0;i<M;i++){
        fread(&attr[i], sizeof(Attraction), 1, fin);
    }
    fclose(fin);
    qsort(attr, M, sizeof(Attraction), cmp);
    for(int i=0;i<M;i++)
        printf("%d %d\n", attr[i].x, attr[i].y);
    return 0;
}