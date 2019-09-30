#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct person {
    unsigned int id;
    char name[32];
} person;
typedef struct friend {
    unsigned int id1;
    unsigned int id2;
} friend;
unsigned int getId(char str[], person *pbuf, int p) {
    for (int i = 0; i < p; i++) {
    	if (!strcmp(str, pbuf[i].name)) return pbuf[i].id;
    }
    return -1;
}
bool is_Friend(unsigned int idx1, unsigned int idx2, friend *fbuf, int f) {
    for (int i = 0; i < f; i++) {
    	if (fbuf[i].id1 == idx1 && fbuf[i].id2 == idx2) return true;
    	if (fbuf[i].id1 == idx2 && fbuf[i].id2 == idx1) return true;
    }
    return false;
}
void query(person *pbuf, friend *fbuf, int p, int f) {
	char name1[32], name2[32];
	while (scanf("%s%s", name1, name2) == 2) {
          unsigned int idx1 = getId(name1, pbuf, p), idx2 = getId(name2, pbuf, p);
		  if (idx1 == -1 || idx2 == -1) return;
		  if (is_Friend(idx1, idx2, fbuf, f)) printf("yes\n");
		  else printf("no\n");
    }
}
int main(int argc, char const *argv[])
{
	FILE *fp1 = fopen("friends", "rb");
    int p, f;
    fread(&p, sizeof(int), 1, fp1);
    person *pbuf = (person*)malloc(sizeof(person) * p);
    fread(pbuf, sizeof(person), p, fp1);

    fread(&f, sizeof(int), 1, fp1);
    friend *fbuf = (friend*)malloc(sizeof(friend) * f);
    fread(fbuf, sizeof(friend), f, fp1);

    query(pbuf, fbuf, p, f);
    fclose(fp1);
    free(pbuf);
    free(fbuf);
	return 0;
}