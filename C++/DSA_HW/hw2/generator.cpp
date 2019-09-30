#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	FILE *fp = fopen("hw2.1.txt", "w");
	fprintf(fp, "%d\n", 200);
	for (int i = 0; i < 200;++i) {
		fprintf(fp, "%d %c\n", i, 'a');
	}
	fprintf(fp, "%d\n", 10);
	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%d %d\n", i, 10 - i);
	} 
	fclose(fp);
}