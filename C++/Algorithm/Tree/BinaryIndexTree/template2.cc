//區間修改 單點查詢
#include<bits/stdc++.h>
using namespace std;
int a[500010],b[500010],c[500010],n,m;
int lowbit(int x) {
	return x&-x;
}
void modify(int x,int y) {
	for (int i = x; i <= n; i += lowbit(i))
		c[i] += y;
}
int query(int x) {
	int ans = 0;
	for (int i = x; i > 0;i -= lowbit(i))
		ans += c[i];
	return ans;
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i] - a[i-1]; // 差分數列
	}
	for (int i = 1;i <= n; i++)
		modify(i, b[i]); // maintain 差分數列 with BIT
	for (int i = 1; i <= m; i++) {
		int p; 
		cin >> p;
		if (p == 1) {
			int xx, yy, k;
			cin>> xx >> yy >> k;
			// we only need to modify the boundary of the interval
			modify(xx, k); 
			modify(yy + 1 , -k);
		}
		if (p == 2) {
			int k;
			cin >> k;
			printf("%d\n", query(k));
		}
	}
	return 0;
}
/*
输入格式：

第一行包含两个整数N、M，分别表示该数列数字的个数和操作的总个数。

第二行包含N个用空格分隔的整数，其中第i个数字表示数列第i项的初始值。

接下来M行每行包含2或4个整数，表示一个操作，具体如下：

操作1： 格式：1 x y k 含义：将区间[x,y]内每个数加上k

操作2： 格式：2 x 含义：输出第x个数的值

输出格式：

输出包含若干行整数，即为所有操作2的结果。
*/