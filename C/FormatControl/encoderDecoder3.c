#include <stdio.h>
 
void bin2ascii(char input_file[32], char output_file[32], char dict[17]) {
    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "wt");
    unsigned char byte;
    while ( fread(&byte, 1, 1, fin) ) {
        fputc(dict[ (byte & 0xF0) >> 4 ], fout); // 0x: 十六進位; F0: 1111-0000
        fputc(dict[ byte & 0x0F ], fout); // 0x: 十六進位; 0F: 0000-1111
    }
    fclose(fin);
    fclose(fout);
}
void ascii2bin(char input_file[32], char output_file[32], char dict[17]) {
    FILE *fin = fopen(input_file, "r");
    FILE *fout = fopen(output_file, "wb");
    unsigned char table[128];
    for ( int i = 0; i < 16; i++)
        table[dict[i]] = i;
    char c[2];
    unsigned char write = 0;
    while ( fread(c, sizeof(char), 2, fin) ) {
        write += (unsigned char)table[c[0]];
        write <<= 4;
        write += (unsigned char)table[c[1]];
        fwrite(&write, sizeof(char), 1, fout);
        write = 0;
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