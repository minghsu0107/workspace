// save strlen of every string in array slen to save time
// use combination instead of permutation to save time (因為解為對稱的)
#include <stdio.h>
#include <string.h>
#include <limits.h>
char str[105][15];
int slen[105];
int result[3], test[2], used[105] = {};
int n = 0, minDistance = INT_MAX;
int edit(int idx1, int idx2, int head1, int head2, int len1, int len2) {
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;
    if (str[idx1][head1] == str[idx2][head2]) {
        return edit(idx1, idx2, head1+1, head2+1, len1 - 1, len2 - 1);
    } else {
        int a = edit(idx1, idx2, head1, head2+1, len1, len2 - 1);
        int b = edit(idx1, idx2, head1+1, head2, len1 - 1, len2);
        return 1 + (a < b? a : b);
    }
}
int compare(int result[], int idx1, int idx2) {
	return 1000 * (idx1 + 1) + (idx2 + 1) < 1000 * (result[1] + 1) + (result[2] + 1);
}
void com (int d, int len) {
	if (len == 2) {
		int tmp = edit(test[0], test[1], 0, 0, slen[test[0]], slen[test[1]]);
		if (tmp < minDistance || (tmp == minDistance && compare(result, test[0], test[1]))) {
			minDistance = tmp;
			result[0] = minDistance;
		    result[1] = test[0];
		    result[2] = test[1];
		}
		return;
	}
	if (d == n) return;
	test[len] = d;
	com(d+1, len+1);
	com(d+1, len);
}
// backtracking
void com2 (int d, int len) {
		if (len == 2) {
		int tmp = edit(test[0], test[1], 0, 0, slen[test[0]], slen[test[1]]);
		if (tmp < minDistance || (tmp == minDistance && compare(result, test[0], test[1]))) {
			minDistance = tmp;
			result[0] = minDistance;
		    result[1] = test[0];
		    result[2] = test[1];
		}
		return;
	}
    for (int i = d; i < n; i++) {
    	test[len] = i;
    	com2(i+1, len+1);
    }
}
int main() {    
	while (scanf("%s", str[n]) != EOF) {
	    slen[n] = strlen(str[n]);
	    n++;
	}
    com2(0, 0);
    printf("%d %d %d", result[0], result[1]+1, result[2]+1);
	return 0;
}