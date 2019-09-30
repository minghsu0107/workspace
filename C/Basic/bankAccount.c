#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int balance[32], n;
char user[32][32];
void give(char *u1, char *ins, char *u2, char *d) {
	int t1 = -1, t2 = -1;
	for (int i = 0; i < n; i++) {
	  if (strcmp(user[i], u1) == 0) {
	  	 t1 = i;
	  	 break;
	  }
	}
	if (t1 == -1) return;
	for (int i = 0; i < n; i++) {
      if (strcmp(user[i], u2) == 0) {
	     t2 = i;
	     break;
	  }
	}
    if (t2 == -1) return;
    char str[] = "gives";
	char* ptr = strstr(ins, str);
	if (ptr != NULL) {
		int money = atoi(d);
		if (balance[t1] - money >= 0) {
			balance[t1] -= money, balance[t2] += money;
		}
	}
}
void instruction (char* u, char *ins, char *d) {
	int t = -1;
	for (int i = 0; i < n; i++) {
	  if (strcmp(user[i], u) == 0) {
	  	 t = i;
	  	 break;
	  }
	}
	if (t == -1) return;
    char table[3][10] = {"earns", "spends", "becomes"};
    char *ptr1 = strstr(ins, table[0]);
    char *ptr2 = strstr(ins, table[1]);
    char *ptr3 = strstr(ins, table[2]);
    int money = atoi(d);
    if (ptr1 != NULL) {
	    balance[t] += money;
    	return;
    }
    if (ptr2 != NULL) {
        if (balance[t] - money >= 0) {
            balance[t] -= money;
        }
        return;
    }
    if (ptr3 != NULL) {
        balance[t] = money;
    	return;
    }
}
int main(){
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
    	scanf("%s%d", user[i], &balance[i]);
    }
    char line[128], *s[4];
    while (fgets(line, 128, stdin) != NULL) {
        s[0] = strtok(line," ");
        s[1] = strtok(NULL, " ");
        s[2] = strtok(NULL, " ");
        s[3] = strtok(NULL, "\n");
        if (s[3] != NULL) {
        	give(s[0], s[1], s[2], s[3]);
        } else {
            instruction(s[0], s[1], s[2]);
        }
    }
    for (int i = 0; i < n; i++) {
		printf("%s %d\n", user[i], balance[i]);
	}
	return 0;
}
