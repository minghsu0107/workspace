#include <stdio.h>
#include <limits.h>
int w[205], l[205], sol[205], n;
int maxnum = INT_MIN, maxsum = INT_MIN;
void stack(int d, int slen, int s) {
    if (slen + n - d < maxnum) return;
    if (slen > maxnum) {
       maxnum = slen, maxsum = s;
    }
    if (slen == maxnum && s > maxsum) maxsum = s;
    for (int i = d; i < n; i++) {
        int valid = 0;
        if ((w[i] <= w[sol[slen - 1]] && l[i] <= l[sol[slen - 1]]) ||
            (l[i] <= w[sol[slen - 1]] && w[i] <= l[sol[slen - 1]]) ||
            slen == 0)
           valid = 1;
        if (valid) {
            sol[slen] = i;
            stack(i + 1, slen + 1, s + i);
        }
    }
}
int main(int argc, char const *argv[])
{
    int arr[205];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &w[i], &l[i]);
        arr[i] = i;
    }
    stack(0, 0, 0);
    printf("%d %d", maxnum, maxsum);
    return 0;
}