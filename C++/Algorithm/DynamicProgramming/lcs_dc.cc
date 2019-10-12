// O(m + n) space, O(mn) time complexity
#include <bits/stdc++.h>
#define MAXN 1000000
using namespace std;
const int INF = 1e9 + 7;
int L[2][MAXN];

string reverse(string str) {
    int len = str.length();
    for (int i = 0; i < len; ++i) {
        str[i] = str[len - i - 1];
    }
    return str;
}

int lcs(int m, int n, string &X, string &Y) {   
    bool bi; 
    for (int i = 0; i <= m; i++) { 
        bi = i & 1; 
        for (int j = 0; j <= n; j++) { 
            if (i == 0 || j == 0) 
                L[bi][j] = 0; 
            else if (X[i-1] == Y[j-1]) 
                L[bi][j] = L[1 - bi][j - 1] + 1; 
            else
                L[bi][j] = max(L[1 - bi][j], L[bi][j - 1]); 
        } 
    } 
    return L[bi][n]; 
}

int lcs_dc(int m, int n, string &X, string &Y, string& res) {
    if (!n || !m) {
        res = "";
        return 0;
    }
    
    if (m == 1) {
        for (int i = 0; i < n; ++i) { 
            if (X[0] == Y[i]) {
                res += X[0];
                break;
            }
        }
        return res.length();
    }
    
    string RX = reverse(X);
    string RY = reverse(Y);

    int mid = m / 2;
    int maxsum = -INF;
    int u = -1;

    for (int i = 0; i <= n; ++i) {
        int L1 = lcs(mid, i, X, Y);
        int L2 = lcs(m - mid, n - i, RX, RY);
        if (maxsum < L1 + L2) {
            maxsum = L1 + L2;
            u = i;
        }
    }

    string c1, c2, XX, YY;
    c1 = c2 = XX = YY = "";

    for (int i = mid; i < m; ++i)
        XX += X[i]; 
    for (int i = u; i < n; ++i)
        YY += Y[i];

    int ans_l = lcs_dc(mid, u, X, Y, c1);
    int ans_r = lcs_dc(m - mid, n - u, XX, YY, c2);
    
    res = c1 + c2;
    return ans_l + ans_r;
}

int main() { 
    string X = "sunday"; 
    string Y = "saturday"; 
    string res;

    int ans = lcs_dc(X.length(), Y.length(), X, Y, res);
    cout << "Length of LCS is " << ans << endl;
    cout << "LCS: " << res << endl;
    return 0; 
} 
/*
time:
    T(m, n) = mn + T(m/2, u) + T(m/2, n - u)
    T(m, n) <= mn + mn/2 + mn/4 + ... = 2mn 
    so T(m, n) = O(mn)
backtracking:
    O(n)
space:
    O(m + n)
*/