#include <bits/stdc++.h>
#define MAXN 2005
using namespace std;
typedef long long  ll;
const ll INF = 1e9 + 7;
string s1, s2;
ll dp[MAXN][MAXN];

void print(int len1, int len2){
    cout << "    ";
    for (int j = 0; j < len2; ++j) 
        cout << s2[j] << " ";
    cout << endl;
    for (int i = 0; i <= len1; ++i) {
        if (i) cout << s1[i - 1] << " ";
        else cout << "  ";
        for (int j = 0; j <= len2; ++j)
            cout << dp[i][j] << " ";
        cout << endl;
    }
}

ll solve(int len1, int len2) {
    memset(dp, INF, sizeof(dp));
    
    dp[0][0] = 0;
    for (int i = 0; i < len1; ++i) {
        for (int j = 0; j < len2; ++j) {
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1); // insert 1[i] or delete 2[j]
            dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1); // insert 2[j] or delete 1[i]
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + 1); // replace 1[i] or 2[j]
            if(s1[i] != s2[j])
                dp[i + 1][j + 1] = min(dp[i][j], dp[i + 1][j + 1]);
        }
    }

    ll ans = INF;
    if (len1 <= len2)
        for (int i = 0; i <= len2; ++i) ans = min(ans, dp[len1][i]);
    else
        for (int i = 0; i <= len1; ++i) ans = min(ans, dp[i][len2]);
    //print(len1, len2);
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin >> s1 >> s2;
    printf("%lld\n", solve(s1.length(), s2.length()));
}