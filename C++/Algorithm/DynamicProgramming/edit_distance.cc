// A Dynamic Programming based C++ program to find minimum 
// number operations to convert str1 to str2 
#include <bits/stdc++.h> 
#define MAXN 1000000
using namespace std; 

int dp[MAXN][MAXN]; 
// Utility function to find the minimum of three numbers 
int min(int x, int y, int z) { 
	return min(min(x, y), z); 
} 

int editDistDP(string str1, string str2, int m, int n) { 
	// Create a table to store results of subproblems 

	// Fill d[][] in bottom up manner 
	for (int i = 0; i <= m; ++i) { 
		for (int j = 0; j <= n; ++j) { 
			// If first string is empty, only option is to 
			// insert all characters of second string 
			if (i == 0) dp[i][j] = j; // Min. operations = j 

			// If second string is empty, only option is to 
			// remove all characters of second string 
			else if (j == 0) dp[i][j] = i; // Min. operations = i 

			// If last characters are same, ignore last char 
			// and recur for remaining string 
			else if (str1[i-1] == str2[j-1]) dp[i][j] = dp[i-1][j-1]; 

			// If the last character is different, consider all 
			// possibilities and find the minimum 
			else
				dp[i][j] = 1 + min(dp[i][j-1], // Insert 
						           dp[i-1][j], // Remove 
								   dp[i-1][j-1]); // Replace 
		} 
	} 
	return dp[m][n]; 
} 

int editDistDP2(string str1, string str2, int m, int n) {
	int dp[2][MAXN]; 
	bool bi; 
	for (int i = 0; i <= m; ++i) { 
		bi = i & 1;
		for (int j = 0; j <= n; ++j) { 
			if (i == 0) dp[bi][j] = j;
			else if (j == 0) dp[bi][j] = i; 
			else if (str1[i-1] == str2[j-1]) dp[bi][j] = dp[1-bi][j-1]; 
			else
				dp[bi][j] = 1 + min(dp[bi][j-1], dp[1-bi][j], dp[1-bi][j-1]);
		} 
	} 
	return dp[bi][n]; 
}

// Driver program 
int main() { 
	// your code goes here 
	string str1 = "sunday"; 
	string str2 = "saturday"; 

	cout << editDistDP(str1, str2, str1.length(), str2.length()) << endl; 
	cout << editDistDP2(str1, str2, str1.length(), str2.length()) << endl;
	return 0; 
} 