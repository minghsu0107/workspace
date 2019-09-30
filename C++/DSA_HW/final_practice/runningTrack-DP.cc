#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MAXN = 2222;
string s1, s2;
/*
dp1[i][j]: lcp of s2[i, m-1] and s1[j, n-1]
dp2[i][j]: lcp of s2[i, m-1] and s1[j, 0] (reverse)
*/
int dp1[MAXN][MAXN], dp2[MAXN][MAXN], cnt;
std::vector<pair<int, int> > ans;
int main(int argc, char const *argv[]) {
    cin >> s1 >> s2;
    int len1 = s1.size(), len2 = s2.size();
    for(int i = len2 - 1; i >= 0; --i) 
        for(int j = len1 - 1; j >= 0; --j)
            if(s1[j] == s2[i]) dp1[i][j] = max(dp1[i][j], dp1[i + 1][j + 1] + 1);
    for(int i = len2 - 1; i >= 0; --i)
        for(int j = 0; j < len1; ++j)
            if(s1[j] == s2[i]) dp2[i][j] = max(dp2[i][j], (j ? dp2[i + 1][j - 1] : 0) + 1);
    while (cnt < len2) {
        int x = 0, l = 0, r = 0;
        for(int i = 0; i < len1; ++i)
            if(x < dp1[cnt][i]) {
                x = dp1[cnt][i];
                l = i + 1;
                r = i + x;
            }
        for(int i = 0; i < len1; ++i)
            if(x < dp2[cnt][i]) {
                x = dp2[cnt][i];
                l = i + 1;
                r = i + 2 - x;
            }
        if(!x) {
            cout << -1 << endl;
            return 0;
        }
        ans.push_back(make_pair(l, r));
        cnt += x;
    }
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); ++i)
        cout << ans[i].first << ' ' << ans[i].second << endl;
    return 0;
}