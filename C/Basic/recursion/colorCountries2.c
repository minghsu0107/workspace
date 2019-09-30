#include <stdio.h>
int adjacent[20][20] = {{}}, countries_color[20] = {};
int flag = 0;
void color(int n, int c, int index) {
    if (!flag && index == n) {
        for (int i = 0; i < n; i++) {
		   printf("%d\n", countries_color[i]);
		}
        flag = 1;
        return;
    }
    for (int i = 1; i <= c && !flag; i++) {
        countries_color[index] = i;
        for (int j = 0; j < n && !flag; j++) {
            if (j == index) continue;
            if (adjacent[index][j] && countries_color[index] == countries_color[j] 
                && countries_color[index] != 0) {
                countries_color[index] = 0;
                break;
            }
        }
        if (countries_color[index] != 0 && !flag) color(n, c, index+1);
    }
    countries_color[index] = 0;
}
void color2(int n, int c, int index) {
    for (int i = 0; i < n && !flag; i++) {
        if (i == index - 1) continue;
        if (adjacent[index - 1][i] && countries_color[index - 1] == countries_color[i] 
            && countries_color[index - 1] != 0) {
            return;   
        }
    }
    if (!flag && index == n) {
        for (int i = 0; i < n; i++) {
           printf("%d\n", countries_color[i]);
        }
        flag = 1;
        return;
    }
    for (int i = 1; i <= c && !flag; i++) {
        countries_color[index] = i;
        color2(n, c, index+1);
    }
    countries_color[index] = 0;
}
int main(int argc, char const *argv[])
{   
	int n, c, p;
	scanf("%d%d%d", &n, &c, &p);
	for (int i = 0; i < p; i++) {
	    int a, b;
        scanf("%d%d", &a, &b);
        adjacent[a][b] = 1;
        adjacent[b][a] = 1;
	}
	color2(n, c ,0);
    if(!flag) printf("no solution.\n");
	return 0;
}
