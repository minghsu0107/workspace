#include <stdio.h>
int place_number(int n, int sudoku[9][9]) {
	if (n == 81) {
        for (int i = 0; i < 9; i++) {
		    for (int j = 0; j < 9; j++)
			    printf("%d ", sudoku[i][j]);
			puts("");
	    }
		return 1;
	}
	int row = n/9, col = n%9, block_row = row/3, block_col = col/3;
	if (sudoku[row][col] != 0) return place_number(n+1, sudoku);
	for (int t = 1; t <= 9; t++) {
		int conflict = 0;
		for (int i = 0; i < 9 && !conflict; i++) {
			if ((sudoku[row][i] == t) || (sudoku[i][col] == t))
				conflict = 1;
		}
		if (!conflict) {
			for (int x = 0; x < 3 && !conflict; x++) {
				for(int y = 0; y < 3 && !conflict; y++) {
                    if (sudoku[3*block_row + x][3*block_col + y] == t) 
                    	conflict = 1;
				}
			}
		    if (!conflict) {
		    	sudoku[row][col] = t;
		    	if (place_number(n+1, sudoku)) return 1;
		    }
		}
	}
	sudoku[row][col] = 0;
	return 0;
}
int main() {
	int sudoku[9][9];
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			scanf("%d", &sudoku[i][j]);
    place_number(0, sudoku);
}