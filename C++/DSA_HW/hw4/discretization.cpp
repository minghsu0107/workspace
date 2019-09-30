// elements may repeat
#include <bits/stdc++.h> 
using namespace std; 
bool cmp(int a,int b) { return a<b; } 
int a[100], t[100];
int main() { 
	int n; 
	scanf("%d", &n);  
	for (int i = 0; i < n; i++) { 
		scanf("%d",&a[i]); 
		t[i] = a[i]; 
	} 
	sort(t, t + n, cmp); 
	int m = unique(t, t + n) - t;
	//unique(t,t+n)是去重后数组的末地址，t是初始地址。 
	for (int i = 0; i < n; i++) { 
		a[i] = lower_bound(t, t + m, a[i]) - t;
		//lower_bound（）函数寻找下标最小的位置 
	} 
	for (int i = 0; i < n; i++) { 
		printf("%d ",a[i]); 
	} 
	return 0; 
} 
