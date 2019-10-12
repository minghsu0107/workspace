// replace, insert, or delete
#include <bits/stdc++.h>
#define MAXN 1000000
using namespace std;
const int INF = 1e9 + 7;
int dp[2][MAXN]; 

string reverse(string str) {
    int len = str.length();
    for (int i = 0; i < len; ++i) {
        str[i] = str[len - i - 1];
    }
    return str;
}

int edit(int m, int n, string &str1, string &str2) {  
    bool bi; 
	for (int i = 0; i <= m; ++i) { 
		bi = i & 1;
		for (int j = 0; j <= n; ++j) { 
			if (i == 0) dp[bi][j] = j;
			else if (j == 0) dp[bi][j] = i; 
			else if (str1[i - 1] == str2[j - 1]) dp[bi][j] = dp[1 - bi][j - 1]; 
			else
				dp[bi][j] = 1 + min(dp[bi][j - 1], min(dp[1 - bi][j], dp[1 - bi][j - 1]));
		} 
	} 
	return dp[bi][n];
}

void print_sol(int m, int n, string &X, string &Y) {
	if (!m || !n) {
		cout << "   " << endl;
		return;
	}
	if (dp[m][n] == dp[m - 1][n] + 1)
		print_sol(m - 1, n, X, Y);
	else if (dp[m][n] == dp[m][n - 1] + 1)
		print_sol(m, n - 1, X, Y);
	else
		print_sol(m - 1, n - 1, X, Y);
	cout << X[m - 1] << " " << Y[n - 1] << endl;
}

int edit_dc(int m, int n, string &X, string &Y) {
	/*
	if (!n) return m;
	if (!m) return n;
	if (m == 1) {
		for (int i = 0; i < n; ++i) {
			if (X[0] == Y[i])
				return n - 1;
		}
		return n;
	}
	*/
    if (n <= 2 || m <= 2) {
    	//return edit(m, n, X, Y); 
    	int dp[m + 1][n + 1];
		for (int i = 0; i <= m; ++i) { 
			for (int j = 0; j <= n; ++j) { 
				if (i == 0) dp[i][j] = j;
				else if (j == 0) dp[i][j] = i; 
				else if (X[i - 1] == Y[j - 1]) dp[i][j] = dp[i - 1][j - 1]; 
				else
					dp[i][j] = 1 + min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));
			} 
		}
		print_sol(m, n, X, Y); 
		return dp[m][n];
    }
    
    string RX = reverse(X);
    string RY = reverse(Y);

    int mid = m / 2;
    int maxsum = INF;
    int u = -1;

    for (int i = 0; i <= n; ++i) {
        int tmp = edit(mid, i, X, Y) + edit(m - mid, n - i, RX, RY);
        if (maxsum > tmp) {
            maxsum = tmp;
            u = i;
        }
    }

    string XX, YY;
    XX = YY = "";
    for (int i = mid; i < m; ++i)
        XX += X[i]; 
    for (int i = u; i < n; ++i)
        YY += Y[i];
    
    int ans_l = edit_dc(mid, u, X, Y);
    int ans_r = edit_dc(m - mid, n - u, XX, YY);
    return ans_l + ans_r;
}

int main() { 
    string X = "sunday"; 
    string Y = "zxsaturday"; 

    cout << edit_dc(X.length(), Y.length(), X, Y) << endl;
    return 0; 
} 