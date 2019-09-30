#include <stdio.h>
#include <string.h>
#define MAXLEN 10001
 
int main()
{
    char str[MAXLEN], mark_i[MAXLEN], mark_j[MAXLEN], mark_o[MAXLEN];
    int i, j;
    while ( scanf("%s%d%d", str, &i, &j) != EOF ) {
        int count = 0, k;
        memset(mark_i, '+', sizeof(mark_i));
        memset(mark_j, '+', sizeof(mark_j));
        memset(mark_o, '+', sizeof(mark_o));
        for ( k = 0; str[k] != '\0'; k++) {
            if ( count == i ) { mark_i[k] = str[k]; }
            else if ( count == j ) { mark_j[k] = str[k]; }
            else { mark_o[k] = str[k]; }
            if ( str[k] == 'a' || str[k] == 'e' || str[k] == 'i' || str[k] == 'o' || str[k] == 'u' )
                count++;
        }
        mark_i[k] = mark_j[k] = mark_o[k] = '\0';
        puts(mark_i);
        puts(mark_j);
        puts(mark_o);
    }
    return 0;
}
