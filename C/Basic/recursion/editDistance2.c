// 剪枝(if l > minDistance => this solution has no use) + 用雙重迴圈取代combination recursion
#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MIN(x, y) ((x) < (y) ? (x) : (y))
char str[105][15];
int slen[105], result[3];
int n = 0, minDistance = INT_MAX;
int edit(int idx1, int idx2, int head1, int head2, int len1, int len2, int l) {
    if (l > minDistance) return -1;
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;
    if (str[idx1][head1] == str[idx2][head2]) {
        return edit(idx1, idx2, head1+1, head2+1, len1 - 1, len2 - 1, l);
    }
    int a = edit(idx1, idx2, head1, head2+1, len1, len2 - 1, l + 1);
    int b = edit(idx1, idx2, head1+1, head2, len1 - 1, len2, l + 1);
    return 1 + MIN(a, b);
}
int compare(int result[], int idx1, int idx2) {
	return 1000 * (idx1 + 1) + (idx2 + 1) < 1000 * (result[1] + 1) + (result[2] + 1);
}
int main() {    
	while (scanf("%s", str[n]) != EOF) {
	    slen[n] = strlen(str[n]);
	    n++;
	}
	for (int i = 0; i < n; i++) {
	    for (int j = i + 1; j < n; j ++) {
	       int tmp = edit(i, j, 0, 0, slen[i], slen[j], 0);
		   if (tmp != -1 && tmp < minDistance || (tmp == minDistance && compare(result, i, j))) {
		      minDistance = tmp;
		      result[0] = minDistance;
		      result[1] = i;
		      result[2] = j; 
		   }
	    }
	}
    printf("%d %d %d", result[0], result[1]+1, result[2]+1);
	return 0;
}
