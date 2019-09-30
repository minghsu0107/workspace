#include <stdio.h>
#include <string.h>
typedef struct {
  int id;
  char first_name[32];
  char last_name[32];
  int boss_id;
} employee;
int n;
employee info[32];
int searchIdByName(char f[], char l[]) {
    for (int i = 0; i < n; i++) {
        if (!strcmp(f, info[i].first_name) && !strcmp(l, info[i].last_name))
           return info[i].id;
    }
    return -1;
}
int searchBossByName(char f[], char l[]) {
    for (int i = 0; i < n; i++) {
        if (!strcmp(f, info[i].first_name) && !strcmp(l, info[i].last_name))
           return info[i].boss_id;
    }
    return -1;
}
int searchBossById(int idx) {
    for (int i = 0; i < n; i++) {
    	if (info[i].id == idx) return info[i].boss_id;
    }
    return -1;
}
void query(char f1[], char l1[], char f2[], char l2[]) {
	int i1 = searchIdByName(f1, l1), b1 = searchBossByName(f1, l1);
	int i2 = searchIdByName(f2, l2), b2 = searchBossByName(f2, l2);
	//printf("%d %d %d %d\n", i1, b1, i2 ,b2);
	while (1) {
        if (b1 == i2) {
           printf("subordinate\n");
           return;
        }
        else if (i1 == b2) {
           printf("supervisor\n");
           return;
        }
        else if (b1 == b2 && b1 != i2 && b2 != i1) {
           printf("colleague\n");
           return;
        }
        int x = searchBossById(b1), y = searchBossById(b2);
        if ((x == b1) && (y == b2)) break;
        b1 = x, b2 = y;
	}
    printf("unrelated\n");
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &info[i].id);
        scanf("%s%s", info[i].first_name, info[i].last_name);
        scanf("%d", &info[i].boss_id);
	}
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		char f1[32], l1[32], f2[32], l2[32];
		scanf("%s%s%s%s", f1, l1, f2, l2);
		query(f1, l1, f2, l2);
	}
	return 0;
}