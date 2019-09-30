#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 50
#define MAXL 20
#define K 3 // number of groups
 
int N, L, R;
char strs[MAXN][MAXL+5];
 
int dist(char *str1, char *str2){ // Manhattan distance of two strings
    int s = 0;
    for(int i = 0; i < L; i++)
        s += abs(str1[i] - str2[i]);
    return s;
}
 
int isSmaller(char *str1, char *str2){ // check if str1 is lexigraphically smaller than str2
    return strcmp(str1, str2) < 0;
}
 
int isCloser(char *curStr, char *oriStr, char *newStr, int oriDist){ // check if newStr is closer to curStr (compare with dist(curStr, oriStr))
    int newDist = dist(curStr, newStr);
    return newDist != oriDist ? newDist < oriDist : isSmaller(newStr, oriStr); // if the distance is the same, check the lexigraphic order
}
 
int pickClosest(char *str, int *candidateIds, int numCandidate){ // pick the closest candidate from candidateIds[] which has the minimal distance to str
    int minDist = dist(str, strs[candidateIds[0]]), minId = 0;
    for(int i = 1; i < numCandidate; i++){ // for each candidate
        char *candidateStr = strs[candidateIds[i]];
        if (isCloser(str, strs[candidateIds[minId]], candidateStr, minDist)) // check if it is better than the currenct min
            minDist = dist(str, candidateStr), minId = i;
    }
    return minId;
}
 
int assignNewLeader(int *memberIds, int memberCnt){ // given the members, find the new leader
    int sum[MAXL+5] = {0};
    char meanStr[MAXL+5] = {0};
    for(int i = 0; i < L; i++){ // calculate the mean of the group (step 2.)
        for(int j = 0; j < memberCnt; j++)
            sum[i] += strs[memberIds[j]][i];
        meanStr[i] = sum[i] / memberCnt;
    }
    return memberIds[pickClosest(meanStr, memberIds, memberCnt)]; // pick the one with minimal distance to the mean (step 3.)
}
 
int sort(int *idx, int cnt){ // sort the index (selection sort)
    int tmp;
    for(int i = 0; i < cnt; i++){
        for(int j = i + 1; j < cnt; j++){
            if (isSmaller(strs[idx[j]], strs[idx[i]]))
                tmp = idx[i], idx[i] = idx[j], idx[j] = tmp;
        }
    }
}
 
void kmeans(int *leaderIds, int (*memberIds)[MAXN], int *memberCnt){
    for(int i = 0; i < K; i++) leaderIds[i] = i;
 
    for(int r = 0; r < R; r++){
        for(int i = 0; i < K; i++) memberCnt[i] = 0; // clean up and start again in every iteration
        for(int i = 0; i < N; i++){
            int gid = pickClosest(strs[i], leaderIds, K); // pick leader (step 1.)
            memberIds[gid][memberCnt[gid]++] = i; // increase group member count
        }
        for(int i = 0; i < K; i++)
            leaderIds[i] = assignNewLeader(memberIds[i], memberCnt[i]); // find new leader (step 2. 3.)
    }
}
 
 
int main(){
    scanf("%d %d %d", &N, &L, &R);
 
    for(int i = 0; i < N; i++)
        scanf("%s", strs[i]) == 1;
 
    int leaderIds[K], memberIds[K][MAXN], memberCnt[K];
    kmeans(leaderIds, memberIds, memberCnt); // iterate k-means for R rounds
    sort(leaderIds, K); // sort the leaders
 
    for(int i = 0; i < K; i++)
        printf("%s\n", strs[leaderIds[i]]);
 
    return 0;
}
