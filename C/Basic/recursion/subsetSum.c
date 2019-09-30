#include <stdio.h>   
int Num[20], Used[20], n, m; 
int count = 0, s = 0;
void Sum0(int d){
    if (s == m) count++;
    for (int i = d; i < n; i++){
        if (s+Num[i] <= m) {
            s += Num[i];
            Sum0(i+1);
            s-=Num[i];
        }
    }
}
int Sum(int d, int s) 
{   
    if (s>m) return 0;
    if (s==m) 
    { 
       return 1;  // be aware that we can return here because it's impossible for s to become larger here
    } 
    if (d==n) return 0; 
    return (Sum(d+1, s+Num[d]) + Sum(d+1, s)); // if we just want to know if there is a solution
	                                           // then we return Sum(d+1, s+Num[d]) || Sum(d+1, s)
} 
int Sum2(int d, int s) // may TLE
{   
    int ans = 0;
    if (s > m) return 0;
    if (d == n) 
    {  
       return (s == m);
    } 
    ans += Sum2(d+1, s+Num[d]); 
    ans += Sum2(d+1, s);
    return ans;
} 
int ct = 0;
void Sum3(int d, int s)
{
    if (s > m) return;
    if (s == m) {
        ct++;
        return;
    }
    if (d == n) return;
    Sum3(d+1, s+Num[d]);
    Sum3(d+1, s);
}
int main() 
{ 
    int i; 
    scanf("%d",&n); 
    for (i=0; i<n; i++) scanf("%d",&Num[i]); 
    while(scanf("%d",&m)!=EOF){
       //Sum0(0);
       //printf("%d\n",count);
       //count = 0;
       //printf("%d\n",Sum(0,0));
       //printf("%d\n",Sum2(0,0));
       Sum3(0,0);
       printf("%d\n",ct);
       ct = 0;
    }
    return 0; 
}
