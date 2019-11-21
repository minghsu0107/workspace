#include<bits/stdc++.h>
#define IOS {ios::sync_with_stdio(false);cin.tie(nullptr);}
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#define ll long long
#pragma GCC optimize("Ofast", "no-stack-protector", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native")
using namespace std;

inline void rit(int &n) {
	bool neg = 0;
	char c;
	while(!isdigit(c=getchar()) && c != '-');
	if(c == '-') {
		neg = 1;
		c = getchar();
	}
	n = c - '0';
	while(isdigit(c=getchar()))
		n = n * 10 + c -'0';
	if(neg) n= -n;
}

inline void wit(ll n) {
	if(!n) {
		putchar('0');
		return;
	}
	char buf[16];
	int t = 0;
	while(n) {
		buf[t++] = n % 10 + '0';
		n /= 10;
	}
	while(t--)
		putchar(buf[t]);
}

int main(){
	IOS;
	int n;
	rit(n);
	wit(n); putchar('\n');
	return 0;
}