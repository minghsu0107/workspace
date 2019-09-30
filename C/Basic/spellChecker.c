#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char dic[100005][105];
char word[105];
int candicate[100005];
int n,q, count = 0;
int isIn(char word[]){
	for(int i = 0; i < n; i++){
		if(strcmp(dic[i], word) == 0){
			return 1;
		}
	}
	return 0;
}
int check1(char* str1, char* str2, int alen){
	int count = 0;
    for(int i = 0;i < alen; i++){
        if(str1[i] != str2[i]) count++;
        if(count > 1) return 0;
    }
    return 1;
}
int check2(char* str1, char* str2, int alen, int blen){
    int flag = 1;
	for (int i = 0; i < blen; i++){
		if(flag){
			if(str2[i] == str1[i]) continue;
			if(str2[i] == str1[i+1]) {
				flag = 0;
                continue;
			}
			return 0;
		}else{
            if(str2[i]==str1[i+1]) continue;
			return 0;
		}

	}
	return 1;	
}
int isCandicate(char word[], int wlen){
    for(int i = 0;i < n; i++){
    	int dlen = strlen(dic[i]);
    	if(abs(dlen - wlen) == 1 || dlen == wlen){
    	    if(dlen > wlen){
    	    	if(check2(dic[i], word, dlen, wlen)) {
    	    	   candicate[count++] = i;
    	        }
    	    }
    	    else if(dlen < wlen){
    	    	if(check2(word, dic[i], wlen, dlen)) {
    	    	   candicate[count++] = i;
    	        }
    	    }
    	    else{
                if(check1(dic[i], word, dlen)){
                   candicate[count++] = i;
                }
    	    }
    	}
    }
    if(count > 0) return 1; 
    return 0;
}
void judge(char word[], int wlen){
	if(isIn(word)){
		printf(">%s\n",word);
	}
    else if(isCandicate(word, wlen)){
    	int f = 0;
        for(int i = 0;i < count; i++){
        	if(f) printf(" ");
        	if(!f) printf("?");
        	printf("%s", dic[candicate[i]]);
        	f = 1;
        }
        puts("");
        count = 0;
    }else{
        printf("!%s\n",word);
    }
    return;
}
int main(){
    scanf("%d",&n);
    for(int i = 0; i < n;i++){
    	scanf("%s", dic[i]);
    }
    scanf("%d",&q);
    while(q--){
    	scanf("%s", word);
    	int wlen = strlen(word);
    	judge(word, wlen);
    }
	return 0;
}
