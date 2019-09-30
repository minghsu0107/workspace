#include <stdio.h>
int maze[100][100], n, m, start_r, start_c, end_r, end_c;
int isIn(int r, int c) {
	return (r >= 0 && r < n && c >= 0 && c < m);
}
int dfs(int step, int current_r, int current_c) {
	if (current_r == end_r && current_c == end_c) return 1;
    int dr[4] = {1, 0, -1, 0};
	int dc[4] = {0, 1, 0, -1};
	for (int i = 0; i < 4; i++) {
	    int next_r = current_r + dr[i];
		int next_c = current_c + dc[i];
		if (isIn(next_r, next_c) && maze[next_r][next_c] == 0) {
             maze[next_r][next_c] = step;
			 if (dfs(step + 1, next_r, next_c)) return 1;
			 maze[next_r][next_c] = 0;
		}
	}
	return 0;
}
int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &maze[i][j]);
		}
	}
	scanf("%d%d", &start_r, &start_c);
	scanf("%d%d", &end_r, &end_c);
	maze[start_r][start_c] = 1;
	if (dfs(2,start_r, start_c)) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%2d", maze[i][j]);
			}
			puts("");
		}
	}
	else printf("no solution\n");
	return 0;
}
