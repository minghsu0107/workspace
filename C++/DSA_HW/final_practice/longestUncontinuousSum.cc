// every element should be separated
#include <bits/stdc++.h>
#define maxn 1000005
#define INF 1000000005
using namespace std;
int a[maxn], s[maxn], n;

int maxSum() {
    s[0] = a[0];
    s[1] = max(a[0], a[1]);
    for(int i = 2; i < n; i++) {
        s[i] = max(s[i-1], s[i-2] + a[i]);
    }
    int ms= -INF;
    for(int i = 0; i < n; i++) {
        if(s[i] > ms)
            ms = s[i];
    }
    return ms;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    printf("%d\n", maxSum());
    return 0;
}