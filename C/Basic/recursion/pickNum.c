#include <stdio.h>
int k, n, m;
int num[21];
int cnt = 0, sum = 0, ki = 0;
// traceback
void pick0(int d){
    if (sum <= m && ki >= k) cnt++;
    for (int i = d; i < n; i++) {
        if (sum + num[i] <= m && ki <= n) {
            sum += num[i];  // 每步能選就選 選了才算是否為解 沒選就不會算到 所以不會重複計算
            ki ++;
            pick0(i+1);
            sum -= num[i];
            ki --;
        } 
    }
}
int cnt2 = 0;
void pick1(int d, int sum, int ki) {
    if (sum > m || ki > n) return;
    if (sum <= m && ki >= k) cnt2++;
    for (int i = d; i < n; i++) {
        pick1(i+1, sum + num[i], ki + 1);
    }
}
// wrong solution
int count = 0;
void pick(int d, int sum, int ki){
    if (sum > m || ki > n) return;
    if (sum <= m && ki >= k) count++; // this method may count the solution repeatedly
    if (d==n) return;
    pick(d+1, sum, ki);
    pick(d+1, sum + num[d], ki+1);
}
int dfs(int d, int sum, int ki){
    int ans = 0;
    if (sum > m || ki > n) return 0;
    if (d == n) return ki >= k && sum <= m;
    ans += dfs(d+1, sum, ki);
    ans += dfs(d+1, sum+num[d], ki+1);
    return ans;
}
int dfs2(int n, int m, int k){
    if (m < 0 || k > n) return 0;
    if (n == 0) return k <= 0 && m >= 0;
    return dfs2(n-1, m, k) + dfs2(n-1, m-num[n-1], k-1);
}
int main(){
    scanf("%d%d%d",&k, &n, &m);
    for(int i = 0; i < n; i++){
        scanf("%d", &num[i]);
    }
    pick0(0);
    pick1(0,0,0);
    pick(0,0,0);
    printf("%d\n",cnt);
    printf("%d\n",cnt2);
    printf("%d\n",count);
    printf("%d\n",dfs(0,0,0));
    printf("%d\n",dfs2(n, m, k));
    return 0;
}
