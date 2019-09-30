#include <stdio.h>
#include <stdbool.h>
int map[9][9], result[9][9];
bool isIn (int r, int c) {
	return (r >= 0 && r < 9 && c >= 0 && c < 9);
}
bool check(int r, int c) {
	if (r == -1 || c == -1) return true;
	int cnt = 0;
	for (int i = r - 1; i <= r + 1; i++) {
		for (int j = c - 1; j <= c + 1; j++) {
			if (!isIn(i, j)) continue;
			cnt += result[i][j];               
		}
	}
	if (map[r][c] == cnt) return true;
	return false;
}
bool dfs(int r, int c) {
	if(r > 1 && c == 0) {
		if (!check(r - 2, 8)) return false;
	}
	if (r == 9) return check(8, 8);
	result[r][c] = 0;
	int nc = (c + 1) % 9, nr = (c == 8) ? r + 1 : r;
	if(check(r - 1, c - 1) && dfs(nr, nc)) return true;
	result[r][c] = 1;
	if(check(r - 1, c - 1) && dfs(nr, nc)) return true;
	result[r][c] = 0;
	return false;
}
bool dfs2(int r, int c) {
	if (r > 1 && c == 0) {
		if (!check(r - 2, 8)) return false;
	}
	if (r == 9) return check(8, 8);
	for (int i = 0; i < 2; i++) {
		result[r][c] = i;
		if (check(r-1, c-1)) {
			int nc = (c + 1) % 9, nr = (c == 8) ? r + 1 : r;
			if (dfs2(nr, nc)) return true;
		}
	}
	return false;
}
int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	if (dfs2(0, 0)) {
		for (int i = 0; i < 9; i++) {
		    for (int j = 0; j < 9; j++) {
			    printf("%d%c", result[i][j], " \n"[j == 9 - 1]);
		    }
	    }
	}
    else printf("no solution\n");	
	return 0;
}