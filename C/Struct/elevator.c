#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXF 1000
#define MAXL 1500
typedef struct Elevator{
    int position;
    int visited[MAXF + 1];
    int u, d, F;
    int dinvalid, uinvalid;
} Elevator;
 
Elevator* newElevator(int u, int d, int F){
    Elevator* elevator = (Elevator*) malloc(sizeof(Elevator));
    elevator->position = 1;
    elevator->u = u;
    elevator->d = d;
    elevator->F = F;
    elevator->visited[1] = 1;
    for(int i = 2; i <= F; i++)
        elevator->visited[i] = 0;
    elevator->dinvalid = 0;
    elevator->uinvalid = 0;
    return elevator;
}
 
int up(Elevator* elevator){
    int p = elevator->position + elevator->u;
    elevator->dinvalid = 0;
    if (p > elevator->F){
        if (++elevator->uinvalid > 3) return -1;
        else return 0;
    }
    elevator->position = p;
    elevator->uinvalid = 0;
    return elevator->visited[p] = 1;
}
 
int down(Elevator* elevator){
    int p = elevator->position - elevator->d;
    elevator->uinvalid = 0;
    if (p <= 0){
        if (++elevator->dinvalid > 3) return -1;
        else return 0;
    }
    elevator->position = p;
    elevator->dinvalid = 0;
    return elevator->visited[p] = 1;
}
int visited(struct Elevator* elevator, int floor){
    return elevator->visited[floor];
}
 
int getPosition(struct Elevator* elevator){
    return elevator->position;
}
int main(){
    int u, d, F, N;
    char mv[MAXL];
    struct Elevator *elevator;
 
    assert(scanf("%d", &N) == 1);
    for(int n = 1; n <=N; n++){
        assert(scanf("%d %d %d", &u, &d, &F) == 3);
        assert(scanf("%s", mv) == 1);
 
        elevator = newElevator(u, d, F);
 
        int L = strlen(mv);
        for(int l = 0; l < L; l++){
            int x;
            if (mv[l] == 'U') x = up(elevator);
            if (mv[l] == 'D') x = down(elevator);
 
            if (x == 0) printf("Invalid\n");
            else if (x == 1) printf("Valid %d\n", getPosition(elevator));
            else{
                printf("Broken\n");
                break;
            }
 
        }
 
        for(int i = 1; i <= F; i++)
            if (visited(elevator, i)) printf("%d\n", i);
 
        free(elevator);
    }
    return 0;
}
