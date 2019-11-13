#include <bits/stdc++.h>
#define MAXN 2005
using namespace std;
typedef long long  ll;
const ll INF = 1e9 + 7;
string s1, s2;
ll dp[MAXN][MAXN];

void print(int len1, int len2) {
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
    
    // dp[i][j] == # of least operations
    // making s1[0 to i-1] and s2[0 to j-1] be s1' and s2'
    // where len(s1') == len(s2') and s1 != s2 at every element
    dp[0][0] = 0;
    for (int i = 0; i < len1; ++i) {
        for (int j = 0; j < len2; ++j) {
            // example: AX vs. B
            // if dp[A][B] is solved, then dp[AX][B]
            // can be updated by dp[A][B] + 1
            // 1. insert B: convert into AX vs. B[0:len-1]+B[len-1]+Y
            // 2. delete A: convert into A[0:len-1]X VS. B
            // can be written as below
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
            dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);

            // example AX vs. BY
            // dp[AX][BY] can be updated by dp[A][B]+1
            // or if X != Y, then dp[AX][BY] can be updated by dp[A][B]
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + 1); // replace 1[i] or 2[j]
            if(s1[i] != s2[j])  // if s1[i] and s2[j] are different, no need operation 
                dp[i + 1][j + 1] = min(dp[i][j], dp[i + 1][j + 1]);
        }
    }

    // for example, if len1 <= len2, the answer may not be dp[len1][len2] 
    // if a prefix of s2 that satisfies the condition,
    // we do not need to care about the rest of s2
    // we choose the smallest answer among all prefix of s2
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