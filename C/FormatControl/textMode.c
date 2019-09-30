#include <stdio.h>
#include <assert.h>

// "r": read from the start of file
// "r+": read and write from the start of file

// "w": write from the start of file (orginal one eliminated)
// "w+": read and write from the start of file (orginal one eliminated) 

// "a": write from the end of file
// "a+": read from the start of file; write from the end of file

// for "r" and "r+": file must exist
// for other two: if file does not exist, make file
int main(int argc, char const *argv[])
{
	FILE *fp1;
	FILE *fp2;
	int c, i;
	char file_name1[32], file_name2[32];
	scanf("%s%s", file_name1, file_name2);

	fp1 = fopen(file_name1, "w");
	assert(fp1 != NULL);
	for (int i = 0; i < 10; i++) {
		fputc('1', fp1);
	}
	fclose(fp1);

	fp2 = fopen(file_name2, "w");
	assert(fp2 != NULL);
	for (int i = 0; i < 20; i++) {
		fputc('2', fp2);
	}
	fclose(fp2);

    fp1 = fopen(file_name1, "r"); // "r" == "rt"
    assert(fp1 != NULL);
    fp2 = fopen(file_name2, "w"); // "w" == "wt"
    // fp2 = fopen(file_name2, "a"); // "a": data in fp1 is concatenated to end of file2
    assert(fp2 != NULL);

    while((c = fgetc(fp1)) != EOF) {
    	fputc(c, fp2);
    }
    fclose(fp1);
    fclose(fp2);

    fp2 = fopen(file_name2, "r");
    assert(fp2 != NULL);

    while ((c = fgetc(fp2)) != EOF) {
    	fputc(c, stdout);
    }
    fclose(fp2);
	return 0;
}
// fgetc(stdin) == getchar()
// fputc(c, stdout) == putchar(c)
// puts(string) == fputs(string, stdout) with '\n'
/*
char string[128];
while(fgets(string, 128, stdin) != NULL) {
	process string;
}
while(fgets(string, 128, fp) != NULL) {
	process string;
}
*/

