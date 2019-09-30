#include <stdio.h>
#include <stdlib.h>
#define ll long long int
ll n, w[16384];
void seesaw(int ini, int fin,int len){
    if(len < 3) return;
    ll massx = 0, Mass = 0, t;
    for(int i = ini; i <= fin; i++){
        massx += w[i]*(i-ini);
        Mass += w[i];
    }
    if(massx % Mass != 0) return ;
    else  t = (massx / Mass) + ini;
    seesaw(ini, t-1, t-ini);
    printf("%lld\n", t);
    seesaw(t+1, fin, fin-t);
}
int main(){
    scanf("%lld",&n);
    for(int i = 0; i < n; i++)
        scanf("%lld",&w[i]);
    seesaw(0, n-1, n);
}