#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXS 1<<20
char S[MAXS];
int empty = 1;
int main() {
    int n = 0;
    char cmd[16], s1[8], s2[8];
    n = strlen(S);
    while (scanf("%s", cmd) == 1) {
        if (!strcmp(cmd, "insert")) {
            scanf("%s%s", s1, s2);
			if (empty) {
				S[0] = s2[0];
				S[1] = '\0';
				n++;
				empty = 0;
				continue;
			}
			if (!strcmp(s1, "left")) {
				S[n+1] = '\0';
				for (int i = n-1; i >= 0; i--)
					S[i+1] = S[i];
				S[0] = s2[0];
				n++;

			}
			else if (!strcmp(s1, "right")) {
				S[n+1] = '\0', S[n] = s2[0];
				n++;
			}
			else {
				int frlen = atoi(s1) - 1;
				char temp[MAXS];
				strncpy(temp, S, frlen);
				strcpy(temp + frlen, s2);
				strcat(temp, S + frlen);
				strcpy(S,temp);
                n++;
			}
        } else if (!strcmp(cmd, "delete")) {
            scanf("%s", s1);
			if (!strcmp(s1, "left")) {
                for (int i = 0; i < n; i++)
					S[i] = S[i+1];
				n--;

			}
			else if (!strcmp(s1, "right")) {
                S[n-1] = '\0';
				n--;
			}
			else {
				int frlen = atoi(s1) - 1;
				char temp[MAXS];
				strncpy(temp, S, frlen);
				strcpy(temp + frlen, S+frlen+1);
				strcpy(S,temp);
				n--;
			}
        }
        //printf("S = %s\n", S);
    }
	int max = 0, count = 0, len = 0;
	char target[2], result[MAXS];
	char* ptr;
    for(int i = 0; i < n;){
		ptr = &S[i];
		target[0] = S[i];
		target[1] = '\0';
		count = strspn(ptr, target);
		if (count > max) {
			max = count;
			len = 0;
            result[len++] = target[0];
		}
		else if (count == max) {
            result[len++] = target[0];
		}
		i += count;
	}
	for (int i = 0; i < len; i++){
		printf("%c ",result[i]);
	}
	printf("%d",max);
    return 0;
}
