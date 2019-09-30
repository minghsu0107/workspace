#include <stdio.h>
#include <string.h>
char tmp[100000];
int len = 0;
void merge(char result[], char str[]) {
	len = 0;
	int alen = strlen(result), blen = strlen(str);
	int i = 0, j = 0;
	while (i < alen && j < blen) {
		if (strncmp(&result[i], &str[j], 3) <= 0) {
			strncpy(tmp + len, &result[i], 3);
			len += 3;
			i += 3;
		}
		else {
			strncpy(tmp + len, &str[j], 3);
			len += 3;
			j += 3;
		}
	}
    if (i == alen) strcpy(tmp + len, &str[j]);
    else if (j == blen) strcpy(tmp + len, & result[i]);
    strcpy(result, tmp);
}
int main(int argc, char const *argv[])
{
	char str[100000], result[100000];
	scanf("%s", result);
	while (~scanf("%s", str)) {
		merge(result, str);
		printf("%s\n", result);
	}
	return 0;
}