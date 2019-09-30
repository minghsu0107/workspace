#include <stdio.h>
 
int main(){
    char in[17],out[17];
    int n;
    scanf("%s %s %d", in, out, &n);
    FILE *fin = fopen(in, "rb");
    FILE *fout = fopen(out, "wb");
    fseek(fin, 0, SEEK_END);
    int cnt = ftell(fin);
    for (int i = 0; i < cnt; i++){
        fseek(fin, -(((n+i)%cnt)+1), SEEK_END);
        unsigned char tmp, ret=0;   
        fread(&tmp, 1, 1, fin);
        for (int j = 0; j < 8; j++)
            if ((tmp & (1 << j)))
                ret |= 1 << (7 - j);
        fwrite(&ret, 1, 1, fout);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}