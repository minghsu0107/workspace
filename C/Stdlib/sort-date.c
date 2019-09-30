#include <stdio.h>
#include <stdlib.h>
#define MAXN 1000001
 
int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf)
            return EOF;  
        p = buf;
    }
    return *p++;
}
int ReadInt(unsigned *x) {
    char c;
    while((c = readchar()) < '0')    {if(c == EOF) return 0;}
    *x = c - '0';
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    return 1;
}
 
int cmp(const void *a, const void *b) {
    return (*(unsigned*)a > *(unsigned*)b) - (*(unsigned*)a < *(unsigned*)b);
}
 
unsigned date[1000000];
 
int main(void)
{
    int n;
    scanf("%d", &n);
    unsigned x;
    for ( int i = 0; i < n; i++) {
        ReadInt(&date[i]); // year
        date[i] <<= 4;
        ReadInt(&x); // month
        date[i] += x;
        date[i] <<= 5;
        ReadInt(&x); // day
        date[i] += x;
    }
    qsort(date, n, sizeof(unsigned), cmp);
    for ( int i = 0; i < n; i++)
        printf("%u %u %u\n", date[i] >> 9, (date[i] >> 5) & 0x0000000F, date[i] & 0x0000001F );
    return 0;
}
/*
0x0000000F: 00000000-00000000-00000000-00001111
0x0000001F: 00000000-00000000-00000000-00011111
*/