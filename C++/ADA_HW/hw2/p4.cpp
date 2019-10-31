#include <bits/stdc++.h>
#define MAXN 200010
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0) 
char _;
using namespace std;

int n, s1, s2, s3, tmp;
int ans = 0;
int a[MAXN], g[7], cnt[7];

bool init() {
	if (s1 > s3) swap(s1, s3);
	if (s1 > s2) swap(s1, s2);
	if (s2 > s3) swap(s2, s3);
	g[0] = s1, g[1] = s2, g[2] = min(s1 + s2, s3), g[3] = max(s1 + s2, s3), 
	g[4] = s1 + s3, g[5] = s2 + s3, g[6] = s1 + s2 + s3;
	for (int i = 0; i < n; ++i) {
		bool flag = false;
		for (int j = 0; j < 7; ++j) {
			if (a[i] <= g[j]) {
				++cnt[j];
				flag = true;
				break;
			}
		}
		if (!flag) return false;
	}
	return true;
}

int solve() {
	if (s1 + s2 >= s3) {
		while (cnt[3]) {
			--cnt[3], ++ans;
			if (cnt[2] || cnt[1] || cnt[0]) {
				if (cnt[2]) --cnt[2];
				else if (cnt[1]) --cnt[1];
				else if (cnt[0]) --cnt[0];
			}
		}
		while (cnt[4]) {
			--cnt[4], ++ans;
			if (cnt[1] || cnt[0]) {
				if (cnt[1]) --cnt[1];
				else if (cnt[0]) --cnt[0];
			}
		}
		while (cnt[5]) {
			--cnt[5], ++ans;
			if (cnt[0]) {
				--cnt[0];
			}
		}
		ans += cnt[6];
		cnt[6] = 0;
		while (cnt[2]) {
			--cnt[2], ++ans;
			if (cnt[0] && cnt[1]) {
				--cnt[0], --cnt[1];
			}
			else {
				if (cnt[0] && !cnt[1]) {
					if (cnt[0] >= 2){
						cnt[0] -= 2;
					}
					else if (cnt[0]) {
						--cnt[0];
					}
				}
				else if (!cnt[0] && cnt[1]) {
					--cnt[1];
				}
				else
					if (cnt[2]) --cnt[2];
			}
		}
		while (cnt[1]) {
			--cnt[1], ++ans;
			if (cnt[0] && cnt[1]) {
				--cnt[0], --cnt[1];
			}
			else {
				if (cnt[0] && !cnt[1]) {
					if (cnt[0] >= 2){
						cnt[0] -= 2;
					}
					else if (cnt[0]) {
						--cnt[0];
					}
				}
				else if (!cnt[0] && cnt[1]) {
					--cnt[1];
				}
			}
		}
		while (cnt[0]) {
			--cnt[0], ++ans;
			if (cnt[0] >= 2) {
				cnt[0] -= 2;
			}
			else if (cnt[0]) {
				--cnt[0];
			}
		}
	}
	else {
		while (cnt[4]) {
			--cnt[4], ++ans;
			if (cnt[1] || cnt[0]) {
				if (cnt[1]) --cnt[1];
				else if (cnt[0]) --cnt[0];
			}
		}
		while (cnt[5]) {
			--cnt[5], ++ans;
			if (cnt[0]) {
				--cnt[0];
			}
		}
		ans += cnt[6];
		cnt[6] = 0;
		
		while (cnt[3] > 0) {
			--cnt[3], ++ans;
			if (cnt[0] && cnt[1]) {
				--cnt[0], --cnt[1];
			}
			else if (cnt[0] >= 2 && !cnt[1]) {
				cnt[0] -= 2;
			}
			else if (!cnt[0] && cnt[1]) {
				--cnt[1];
			}
			else if (cnt[0] == 1 && !cnt[1]) {
				--cnt[0];
			}
			else if (cnt[2]) {
				--cnt[2];
			}
		}
				
		tmp = 0;
        while(cnt[1] > 0) {
            if (cnt[1] == 1) {
                ++ans;
                --cnt[1];
                --cnt[0];
                ++tmp;
            }
            else {
                cnt[1] -= 2;
                cnt[0] -= 1;
                ++ans;
            }
        }
        cnt[2] -= tmp;
        
		while (cnt[0] > 0) {
			if (cnt[2] > 0) {
				cnt[0] -= 2, --cnt[2];
			}
			else {
				cnt[0] -= 3;
			}
			++ans;
		}
		while (cnt[2] > 0) {
			cnt[2] -= 2, ++ans;
		}
	}
	return ans;
}

int main() {
	scan(n);
	scan(s1);
	scan(s2);
	scan(s3);
	for (int i = 0; i < n; ++i) {
		scan(a[i]);
	}
	if (init()) printf("%d\n", solve());
	else puts("-1");
}