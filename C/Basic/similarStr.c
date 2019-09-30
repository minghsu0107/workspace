#include <stdio.h>
#include <string.h>
int conda(char str1[], char str2[], int alen, int blen){
    if(alen != blen) return 0;
	int flag = 0, swap = 0;
	for(int i = 0;i < alen; i++){
		   if(flag){
			   flag = 0;
			   continue;
		   }
           if(str1[i] == str2[i]) continue;
		   if(!swap && str1[i] == str2[i+1] && str1[i+1] == str2[i]){
			   flag = 1;
			   swap = 1;
			   continue;
		   }
		   return 0;
	}
	return 1;
}
int condb(char str1[], char str2[], int alen, int blen){
	if((alen - blen)!=1) return 0;
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
int main(){
  int n;
  scanf("%d",&n);
  char str1[81];
  char str2[81];
  while(n--){
    scanf("%s%s",str1,str2);
	int alen = strlen(str1);
	int blen = strlen(str2);
	if(alen > blen){
		if(conda(str1,str2,alen,blen) || condb(str1,str2,alen,blen)){
	    	printf("yes\n");
        }
        else printf("no\n");
	}
	else{
		if(conda(str2,str1,blen,alen) || condb(str2,str1,blen,alen)){
	    	printf("yes\n");
        }
        else printf("no\n");
		
	}
  }
  return 0; 
}
