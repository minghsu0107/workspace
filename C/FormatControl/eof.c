#include <stdio.h>
int main(int argc, char const *argv[])
{
	FILE *fp;
	int c, i;
	char file_name[32];
	scanf("%s", file_name);
	fp = fopen(file_name, "w");
	for (int i = 0; i < 3; i++) {
		fputc('1', fp);
	}
	fclose(fp);
	fp = fopen(file_name, "r");
	c = fgetc(fp);
	while (!feof(fp)) {
		putchar(c);
		c = fgetc(fp);
	}
	fclose(fp);
	return 0;
}
/*
FILE *fp;
char string[128];
fgets(string, 128, fp);
while (!feof(fp)) {
	puts(string);
	fgets(string, 128, fp);
}
*/