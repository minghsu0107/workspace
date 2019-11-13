#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long  ll;
const ll INF = 1e9 + 7;
int n, m;
string s1, s2;
ll dp[2000][2000];

int solve(int i, int j) {
    if (i == n || j == m) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (s1[i] != s2[j]) return dp[i][j] = solve(i+1, j+1);
    else return dp[i][j] = min({solve(i+1, j) + 1, solve(i, j+1) + 1, solve(i+1, j+1) + 1});
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> s1 >> s2;
    n = (int)s1.size(); m = (int)s2.size();
    memset(dp, -1, sizeof dp);
    cout << solve(0, 0) << endl;
}

/*
Once we align the head of two strings, we can handle the case
that it is only required to solve the prefix of s1 and s2 (if len(s2) <= len(s1))
Therefore, we solve recursively from the head but not tail

solve(i, j) means the answer of (prefix of s1 starts from 0, prefix of s2 starts from 0)
ie. starts comparing from s1[0] and s2[0]

since null string is different from any string,
solve(n, j) = solve(i, m) = 0
*/