#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char journalName[64];
    int numCitedPaper;
    int citedPaperIndex[1024];
} paper;
typedef struct {
    char *journalName;
    int citationCount;
    int publishCount;
} Pack;
int numJournal = 0;
char *journalList[1024] = {};
int citationCount[1024] = {};
int publishCount[1024] = {};
int journalFind(char *name) {
    for (int i = 0; i < numJournal; i++)
        if(strcmp(name, journalList[i])==0)
            return i;
    return -1;
}
int cmp(const void *a, const void *b) {
    Pack *aa = (Pack *)a;
    Pack *bb = (Pack *)b;
    return strcmp(aa->journalName, bb->journalName);
}
void compute(paper P[], int N) {
    for (int i = 0; i < N; i++) {
        if (journalFind(P[i].journalName)==-1) {
            journalList[numJournal] = P[i].journalName;
            publishCount[numJournal] = 1;
            numJournal++;
        }
        else
            publishCount[journalFind(P[i].journalName)]++;
    }
    for (int i = 0; i < N; i++) {
        int numCite = P[i].numCitedPaper;
        for (int j = 0; j < numCite; j++) {
            int citeId = P[i].citedPaperIndex[j];
            citationCount[journalFind(P[citeId].journalName)]++;
        }
    }
    //Pack is used to sorting.
    Pack pack[1024] = {};
    for (int i = 0; i < numJournal; i++) {
        pack[i].journalName = journalList[i];
        pack[i].citationCount = citationCount[i];
        pack[i].publishCount = publishCount[i];
    }
    qsort(pack, numJournal, sizeof(Pack), cmp);
    for (int i = 0; i < numJournal; i++)
        printf("%s %d/%d\n", pack[i].journalName, pack[i].citationCount, pack[i].publishCount);
    return;
}
int main() {
    int N;
    paper P[1024] = {};
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s%d", P[i].journalName, &P[i].numCitedPaper);
        for (int j = 0; j < P[i].numCitedPaper; j++)
            scanf("%d", &P[i].citedPaperIndex[j]);
    }
    compute(P, N);
    return 0;
}