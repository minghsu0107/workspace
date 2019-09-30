#include <stdio.h>
#include <ctype.h>
int main(){
	char str[100];
    int table[26]={};
	int i = 0;
	while(scanf("%c",&str[i])!=EOF){
        if(islower(str[i]) || isupper(str[i])){
            int index = tolower(str[i]) - 97;
			table[index]++;
		}
		i++;
	}
	int f = 0;
	for(int i=0;i<26;i++){
		if(f) puts("");
		printf("%d",table[i]);
		f = 1;
	}
	return 0;
}
