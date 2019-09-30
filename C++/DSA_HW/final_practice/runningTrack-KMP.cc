#include <stdio.h> 
#include <iostream> 
#include <algorithm> 
#include <string.h> 
#define maxs 2100 
#define MME(i,j) memset(i,j,sizeof(i)) 
using namespace std; 
char s[maxs], p[maxs]; 
char revers_s[maxs]; 
int nexts[maxs], ansnum; 
int leftt[maxs], rightt[maxs]; 
char sub_p[maxs]; 
void get_nexts(char *s) { 
	int len = strlen(s); 
	int i = 0, k = -1; 
	nexts[0] = -1; 
	while(i < len) { 
		if( k == -1 || s[i] == s[k]) nexts[++i] = ++k; 
		else k = nexts[k]; 
	} 
} 
int kmp(char *s,char *p, bool flag) { 
	get_nexts(p); 
	int lens = strlen(s), lenp = strlen(p); 
	int i, j; 
	i = j = 0; 
	while (i < lens) { 
		if (j == -1 || s[i] == p[j]) 
			i++, j++; 
		else j = nexts[j]; 
		if (j == lenp) { 
			//flag 为 1时 表示反串
			if(!flag) { 
				leftt[ansnum] = (i - lenp) + 1; 
				rightt[ansnum] = i; 
			} 
			else { 
				leftt[ansnum] = (lens - (i - lenp + 1)) + 1; 
				rightt[ansnum] = (lens - i) + 1; 
			} 
			return 1; 
		} 
	} 
	return 0; 
} 
int main() { 
	while (~scanf("%s%s", s, p)) { 
		ansnum = 0; 
		int lens = strlen(s), lenp = strlen(p); 
		strcpy(revers_s, s); 
		reverse(revers_s, revers_s + lens); 
		int ll = 0, rr = 0, templenp = 0; 
		while(ll < lenp) { 
			bool flag = 0; 
			while (rr < lenp) { 

				int cnt = 0; 
				for (int j = ll; j <= rr; j++) 
					sub_p[cnt++]=p[j]; 
				sub_p[cnt]='\0'; 

				if (kmp(s, sub_p, 0)) { 
					flag = 1; 
					rr++; 
					continue; 
				} 
				else { 
					if (kmp(revers_s, sub_p, 1)) { 
						flag = 1; 
						rr++; 
						continue; 
					} 
					else break; 
				} 
			} 
			if(!flag) break; 
			ansnum++; 
			ll = rr; 
		} 
		if(ll == lenp) { 
			printf("%d\n",ansnum); 
			for (int i = 0; i < ansnum; i++) { 
				printf("%d %d\n",leftt[i], rightt[i]); 
			} 
		} 
		else puts("-1"); 
	} 
	return 0; 
}
