#include<cstdio> 
#include<iostream> 
#include<algorithm> 
#include<cstring> 
using namespace std; 
#define maxn 2222 
char c[maxn],s[maxn]; 
int ans[maxn][2],res; 
int main() { 
	while (~scanf("%s%s",c,s)) {
		int len1 = strlen(c), len2 = strlen(s);
		int cnt = 0, flag, l, r, len; 
		res = 0; 
		for (int i = 0; i < len2; i++) { 
			flag = 0, len = 0; 
			for (int j = 0; j < len1; j++) 
				if (c[j] == s[i]) { 
					flag = 1; 
					l = r = j; 
					for (int k = 1; j + k < len1 && i + k < len2; k++) {
						if (c[j+k] == s[i+k]) r++; 
						else break;
					} 
					if (len < r - l + 1) {
						len = r - l;
						ans[res][0] = l, ans[res][1] = r; 
					}
					l = r = j; 
					for (int k = -1; j + k >= 0 && i - k < len2; k--) {
						if (c[j+k] == s[i-k]) l--; 
						else break; 
					}
					if(len < r - l + 1) {
						len = r - l;
						ans[res][0] = r, ans[res][1] = l; 
					}
				} 
			if (!flag) break; 
			res++, i += len; 
		} 
		if (!flag) printf("-1\n"); 
		else { 
			printf("%d\n",res); 
			for (int i = 0; i < res; i++)
				printf("%d %d\n",ans[i][0] + 1, ans[i][1] + 1); 
		} 
	} 
	return 0; 
}
