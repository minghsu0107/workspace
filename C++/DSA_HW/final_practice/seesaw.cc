#include<stdio.h>

int main() {
    long long int n;
    scanf("%lld", &n);
    long long int array[n+1], sum = 0, swap = 0;
    long long int i, temp;
    for(i = 1; i <= n; i++)
    {
        scanf("%lld", &temp);
        array[i] = temp;
        swap += i * temp;
        sum += temp;
    }
    if(swap % sum == 0) return printf("%d %lld\n", 0, swap / sum - 1), 0;
    for(i = 0; i < n/2; i++)
    {
        if(i != 0) swap = swap - i * array[i] + (n+1-i) * array[i] - (n+1-i) * array[n+1-i] + i * array[n+1-i];
        if(swap % sum == 0)
        {
            printf("%lld %lld\n", i, swap / sum - 1);
            break;
        }
    }
    return 0;
}