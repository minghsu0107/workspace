#include <stdio.h>
int adjacent[400][2], countries_color[20] = {};
int color(int p, int n, int c, int index) {
    for (int i = 0; i < p; i++) {
    	int country1 = adjacent[i][0], country2 = adjacent[i][1];
    	if (countries_color[country1] == countries_color[country2] 
    		&& countries_color[country1] != 0) 
    		return 0;
    }
    if (index == n) return 1;
    for (int i = 1; i <= c; i++) {
        countries_color[index] = i;
        if (color(p, n, c, index+1)) return 1;
    }
    countries_color[index] = 0;
    return 0;
}
int main(int argc, char const *argv[])
{   
	int n, c, p;
	scanf("%d%d%d", &n, &c, &p);
	for (int i = 0; i < p; i++) {
        scanf("%d%d", &adjacent[i][0], &adjacent[i][1]);
	}
	if (color(p, n, c, 0)) {
		for (int i = 0; i < n; i++) {
		   printf("%d\n", countries_color[i]);
		}
    }
    else printf("no solution.\n");
	return 0;
}