#include <stdio.h>
#include <assert.h>
//#include "length.h"
void init(int length[3]);
void add(int length[3], int i);
void sum(int lengtha[3], int lengthb[3], int lengthc[3]);
void diff(int lengtha[3], int lengthb[3], int lengthc[3]);
//main.c
int main() {
    int a[3] = {-1, -1, -1}, b[3] = {-1, -1, -1};
    int c[3] = {-1, -1, -1}, d[3] = {-1, -1, -1};
    int e[3] = {-1, -1, -1}, f[3] = {-1, -1, -1};
    int cmd, x, y, z;
    scanf("%d", &cmd);
    if (cmd == 1) {
        init(a);
        printf("%d %d %d\n", a[0], a[1], a[2]);
    } else if (cmd == 2) {
        init(a);
        scanf("%d", &x);
        add(a, x);
        printf("%d %d %d\n", a[0], a[1], a[2]);
    } else if (cmd == 3) {
        init(a), init(b);
        scanf("%d %d", &x, &y);
        add(a, x), add(b, y);
        sum(a, b, c);
        printf("%d %d %d\n", c[0], c[1], c[2]);
    } else if (cmd == 4) {
        init(a), init(b), init(c), init(d);
        scanf("%d %d %d", &x, &y, &z);
        assert(x+y >= z);
        add(a, x), add(b, y);
        sum(a, b, c);
        add(d, z);
        diff(c, d, e);
        printf("%d %d %d\n", e[0], e[1], e[2]);
    }
    return 0;
}
//length.c
void init(int len[3]) {
    len[0] = len[1] = len[2] = 0;
}
void add(int len[3], int i) {
    len[2] += i;
    len[1] += len[2]/12, len[2] %= 12;
    len[0] += len[1]/3, len[1] %= 3;
}
void sum(int lena[3], int lenb[3], int lenc[3]) {
    lenc[2] = lena[2] + lenb[2];
    lenc[1] = lena[1] + lenb[1] + lenc[2]/12, lenc[2] %= 12;
    lenc[0] = lena[0] + lenb[0] + lenc[1]/3, lenc[1] %= 3;
}
void diff(int lena[3], int lenb[3], int lenc[3]) {
    lenc[2] = lena[2] - lenb[2];
    lenc[1] = lena[1] - lenb[1] - (lenc[2] < 0);
    if (lenc[2] < 0) lenc[2] += 12;
    lenc[0] = lena[0] - lenb[0] - (lenc[1] < 0);
    if (lenc[1] < 0) lenc[1] += 3;
}