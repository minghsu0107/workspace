#include <stdio.h>

static char table[128];
void _init_table(char dict[17]) {
	for (int i = 0; dict[i]; i++) {
		table[dict[i]] = i;
	}
}
void bin2ascii(char input_file[32], char output_file[32], char dict[17]) {
    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "w");
    unsigned char buf;
    while (fread(&buf, 1, 1, fin)) {
    	  unsigned char c1 = 0, c2 = 0;
          c1 |= (buf >> 4);
          c2 |= buf & 15;
          fputc(dict[c1], fout);
          fputc(dict[c2], fout); // fprintf(fout, "%hhu", dict[c2]);
    }
    fclose(fin);
    fclose(fout);
}
void ascii2bin(char input_file[32], char output_file[32], char dict[17]) {
    FILE *fin = fopen(input_file, "r");
    FILE *fout = fopen(output_file, "wb");
    char c1, c2;
    _init_table(dict);
    while (fscanf(fin, "%c%c", &c1, &c2) != EOF) { // (c1 = fgetc(fin)) != EOF
          char buf = 0;
          buf |= table[c1];
          buf <<= 4;
          buf |= table[c2];
          fwrite(&buf, sizeof(char), 1, fout); 
    }
    fclose(fin);
    fclose(fout);
}
int main(){
    int T;
    char input_file[32];
    char output_file[32];
    char dict[17];
    scanf("%d%s%s%s", &T, input_file, output_file, dict);
    if (T) ascii2bin(input_file, output_file, dict);
    else  bin2ascii(input_file, output_file, dict);
    return 0;
}