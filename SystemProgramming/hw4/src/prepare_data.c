#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TESTSIZE 10000

unsigned char buf[TESTSIZE];

int main() {
	FILE *fp1 = fopen("data/y_test", "rb");
	
	FILE *fp2 = fopen("test_label.csv", "w");
	
	fprintf(fp2, "id,label\n");

	fread(buf, sizeof(unsigned char), TESTSIZE, fp1);
	for (int i = 0; i < TESTSIZE; ++i) {
		fprintf(fp2, "%d,%d\n", i, (int)buf[i]);
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}