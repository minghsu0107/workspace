#include<cstdio>
using namespace std;

void find_lcs_len(char a[], char b[], int len_a, int len_b) {
	
	int l[len_a+1][len_b+1];
	
	for (int i = 0; i <=len_a; i++) {
		l[i][0] = 0;
	}
	for (int i = 0; i<=len_b; i++) {
		l[0][i] = 0;
	}

	for (int i = 1; i <= len_a; i++) {
		for (int j = 1; j <= len_b; j++) {
			if (a[i-1] == b[j-1]){
				l[i][j] = l[i-1][j-1]+1;
				
			}
			else {
				if (l[i-1][j] < l[i][j-1]) {
					l[i][j] = l[i][j-1];
					
				}
				else {
					l[i][j] = l[i-1][j];
					
				}
			}
		}
	}

	if(l[len_a][len_b] == 0){
		printf("*\n");
		return;
	}
	int index = l[len_a][len_b];
	char lcs[10005];
	int ia = len_a, jb = len_b; 
    while (ia > 0 && jb > 0) { 
    	// If current character in X[] and Y are same, then 
     	// current character is part of LCS 
	    if (a[ia-1] == b[jb-1]) { 
	    	lcs[index-1] = a[ia-1]; // Put current character in result 
	    	ia--; jb--; index--;     // reduce values of i, j and index 
	    }
	    // If not same, then find the larger of two and 
	    // go into the direction of larger value 
	  	else if (l[ia-1][jb] > l[ia][jb-1]) 
	     	ia--; 
	  	else
	     	jb--; 
    } 
	for (int i = 0; i < l[len_a][len_b]; i++) {
		printf("%c", lcs[i]);
	}
	printf("\n");
}
int main() {
	int T;
	scanf("%d",&T);
	for(int i = 0; i < T; i++) {
		int n, m;
		scanf("%d%d", &n, &m);
		char str1[10005];
		char str2[10005];
		scanf("%s%s",str1, str2);
		find_lcs_len(str1, str2, n, m);

	}
	return 0;
}