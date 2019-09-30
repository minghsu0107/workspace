#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
char alpha1[10], alpha2[10], ans[10], map[26], test1[10], test2[10], test3[10];
int len1, len2, len3;
int check() {
    int a1 = atoi(test1), a2 = atoi(test2), a3 = atoi(test3);
    return ((a1 * a2) == a3);
}
int digit(int d, int len) {
    if (d < len1) {
	   if (isdigit(alpha1[d])) return 1;
	}
	else if (d >= len1 && d - len1 < len2) {
	   if (isdigit(alpha2[d - len1])) return 1;
	}
	else if (d >= len1 + len2 && d < len) {
	   if (isdigit(ans[d - len1 - len2])) return 1;
	}
	return 0;
}
int enumerate (int d, int len) {
	if (d == len) {
		return check();
	}
	int k = digit(d, len);
	if (k) {
		return enumerate(d + 1, len);
	}
	for (int i = 0; i <= 9 && !k; i++) {
		if (d < len1) {
           if (map[alpha1[d] - 'A'] != -1) {
    	      test1[d] = map[alpha1[d] - 'A'] + '0';
    	      return enumerate(d + 1, len);
    	   }
    	   else {
    	   	  test1[d] = i + '0';
	       	  map[alpha1[d] - 'A'] = i;
	       	  if (enumerate(d + 1, len)) return 1;
	       	  map[alpha1[d] - 'A'] = -1;
    	   }
		} else if (d - len1 < len2) {
			if (map[alpha2[d - len1] - 'A'] != -1) {
    	       test2[d - len1] = map[alpha2[d - len1] - 'A'] + '0';
    	       return enumerate(d + 1, len);
    	    }
    	    else {
               test2[d - len1] = i + '0';
	       	   map[alpha2[d - len1] - 'A'] = i;
	       	   if (enumerate(d + 1, len)) return 1;
	       	   map[alpha2[d - len1] - 'A'] = -1;
    	    }

		} else if (d < len) {
            if (map[ans[d - len1 - len2] - 'A'] != -1) {
    	       test3[d - len1 - len2] = map[ans[d - len1 - len2] - 'A'] + '0';
               return enumerate(d + 1, len);
    	    }
    	    else {
    	       test3[d - len1 - len2] = i + '0';
	       	   map[ans[d - len1 - len2] - 'A'] = i;
	       	   if (enumerate(d + 1, len)) return 1;
	       	   map[ans[d - len1 - len2] - 'A'] = -1;
    	    }
		}
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	scanf("%s%s%s", alpha1, alpha2, ans);
	memset(map, -1, sizeof(map));
	strcpy(test1, alpha1);
	strcpy(test2, alpha2);
	strcpy(test3, ans);
	len1 = strlen(alpha1), len2 = strlen(alpha2), len3 = strlen(ans);
    int len = len1 + len2 + len3;
    if(enumerate(0, len)) printf("%s x %s = %s\n", test1, test2, test3);
	return 0;
}