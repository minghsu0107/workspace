#include<stdio.h>
 
void bin2ascii(char input_file[32], char output_file[32], char dict[17])
{
    FILE *ifp = fopen(input_file, "rb");
    FILE *ofp = fopen(output_file, "w");
    char c, ibuffer[1024], obuffer[2048];
    const char mask = 15;
 
    int nread;
    while ((nread = fread(ibuffer, sizeof(char), 1024, ifp)) > 0) {
        char *ibuffer_ptr = &(ibuffer[0]);
        char *obuffer_ptr = &(obuffer[0]);
        for (int i = 0; i < nread; i++) {
            c = *(ibuffer_ptr++);
            *(obuffer_ptr++) = dict[((c >> 4) & mask)];
            *(obuffer_ptr++) = dict[(c & mask)];
        }
        fwrite(obuffer, sizeof(char), nread * 2, ofp);
    }
 
    fclose(ifp);
    fclose(ofp);
 
    return;
}
 
void ascii2bin(char input_file[32], char output_file[32], char dict[17])
{
    FILE *ifp = fopen(input_file, "r");
    FILE *ofp = fopen(output_file, "wb");
     char a, b, ibuffer[2048], obuffer[1024], rdict[128];
 
     for (int i = 0; i < 16; i++)
         rdict[dict[i]] = i;
 
    int nread;
    while ((nread = fread(ibuffer, sizeof(char), 1024, ifp)) > 0) {
        char *ibuffer_ptr = &(ibuffer[0]);
        char *obuffer_ptr = &(obuffer[0]);
        nread /= 2;
        for (int i = 0; i < nread; i++) {
            a = rdict[*(ibuffer_ptr++)];
            b = rdict[*(ibuffer_ptr++)];
            *(obuffer_ptr++) = ((a << 4) | b);
        }
        fwrite(obuffer, sizeof(char), nread, ofp);
    }
 
    fclose(ifp);
    fclose(ofp);
 
    return;
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