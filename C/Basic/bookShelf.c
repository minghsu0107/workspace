#include <stdio.h>
int hasEOF = 0;
unsigned long long bookshelf = 0;
int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) {
            hasEOF = 1;
            return EOF;    
        }
        p = buf;
    }
    return *p++;
}
int ReadInt(int *x) {
    char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
 
int inTheShelf( int x)
{
    long long cpy = bookshelf; 
    short mod;
    short count = 0;
    while(cpy != 0) {
        mod = cpy % 256;
        cpy /= 256;
        count++;
        if(count == 1 && mod == x) return 1;
        if(mod == x){
            // take out the book and add it to right
            // clean out spaces for cpy and x
            bookshelf <<= 8 * (9 - count); // discard everything on the left of the taken book and the book itself
            bookshelf >>= 8 * (8 - count); // clean out a space for cpy
            cpy <<= 8 * (count);
            bookshelf += cpy; // cpy saves the part on the left of the taken book
            bookshelf += x; // add right
            return 1;
        }
    }            
    return 0;
}
int main() {
    int x;
    while (ReadInt(&x)) {
         if(!inTheShelf(x)) {
            bookshelf <<= 8; // pop left
            bookshelf |= x;  // add right (we can also use +=)
        }
    }   
    for(int i = 7 ; i >= 0 ;i--) {
        printf("%lld ", bookshelf >> 8*7);
        bookshelf <<= 8;
    }
    return 0;
}
