#include <stdio.h>
#include <stdlib.h>
typedef struct RoomStatus {
    int capacity;
    struct Reservation *reservation;
} RoomStatus;
typedef struct Reservation {
    int nP;
    int StartTime;
    int EndTime;
    struct Reservation *next;
} Reservation;
int isValid(RoomStatus *room, int nP, int sT, int eT){
    Reservation *pre = NULL, *cur = room->reservation;
    for(; cur!=NULL; pre=cur, cur=cur->next){
        if(eT <= cur->StartTime) break;
        if(sT < cur->EndTime) return 0;
    }
    Reservation *tmp = (Reservation *)malloc(sizeof(Reservation));
    tmp->nP = nP, tmp->StartTime = sT, tmp->EndTime = eT;
    if(pre == NULL)
        room->reservation = tmp;
    else
        pre->next = tmp;
    tmp->next = cur;
    return 1;
}
 
int ReserveRoom(RoomStatus list[], int n, int nP, int StartTime, int EndTime){
    for(int i=0; i<n; i++){
        if(list[i].capacity >= nP){
            if(isValid(&list[i], nP, StartTime, EndTime))
                return 1;
        }
    }
    return 0;
}
int main(){
    int n = 3;
    RoomStatus list[n];
    for(int i=0; i < n; i++){
        list[i].capacity = i+2;
        list[i].reservation = NULL;
    }
    int nP, sTime, eTime;
    while(scanf("%d %d %d", &nP, &sTime, &eTime)!=EOF)
        printf("%d", ReserveRoom(list, n, nP, sTime, eTime));
    puts("");
    printf("---Room Status List---\n");
    for(int i=0; i<n; i++){
        printf("%d ---", list[i].capacity);
        for(Reservation *tmp = list[i].reservation; tmp!=NULL; tmp=tmp->next)
            printf("->(%d:%d, %d)", tmp->nP, tmp->StartTime, tmp->EndTime);
        puts("");
    }
    printf("---      End       ---\n");
    return 0;
}