#include <stdio.h>
int main(int argc, char const *argv[])
{
	FILE *fp1;
	FILE *fp2;
	int sum = 0, another_sum, i;
	char file_name1[32], file_name2[32];
	fp1 = fopen(file_name1, "w");
	for (i = 0; i < 10; i++)
		fprintf(fp1, "%d\n", i); // write integer i into file1
	fclose(fp1);

	fp1 = fopen(file_name1, "r");
	// read an integer from fp1 and input to i until EOF
	while ((fscanf(fp1, "%d", &i)) != EOF)
		sum += i;
	fclose(fp1);

	fp2 = fopen(file_name2, "w");
	fprintf(fp2, "%d\n", sum); // write integer sum into file2
	fclose(fp2);

	fp2 = fopen(file_name2, "r");
	fscanf(fp2, "%d", &another_sum); // read an integer from fp2 and input to another_sum
	fprintf(stdout, "%d", another_sum);
	fclose(fp2);
	return 0;
}
// fprintf returns the number of printed bytes
// fscanf returns the number of input data, if failed then return EOF