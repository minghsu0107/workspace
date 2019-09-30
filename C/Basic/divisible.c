#include <stdio.h>
void print(int *res, int flag){
	int f = 0;
	if(flag) puts("");
	for(int i = 0; i < 4; i++){
		if(f) printf(" ");
		if(res[i] == 1) printf("yes");
		else if(res[i] == -1) printf("no");
		f = 1;
	}
	return;
}
void judge2(char *num, int len, int *res){
    if((num[len-1]-'0')%2 == 0) res[0] = 1;
	else res[0] = -1;
}
void judge3(char *num, int len, int *res){
	int sum = 0;
	for(int i = 0; i < len; i++){
		sum += (num[i]-'0');
	}
	if(sum%3 == 0) res[1] = 1;
    else res[1] = -1;
}
void judge5(char *num, int len, int *res){
    if((num[len-1]-'0')%5 == 0) res[2] = 1;
	else res[2] = -1;
}
void judge11(char *num, int len, int *res){
	int asum = 0, bsum = 0;
	for(int i = 0; i < len; i++){
		if(i%2) asum += (num[i] - '0');
		else bsum += (num[i] - '0');
	}
	if((asum - bsum)%11 == 0) res[3] = 1;
	else res[3] = -1;
}

int main(){
	char ch, number[1005];
	int result[4], i = 0, flag = 0;
    while(1){
        scanf("%c",&ch);
        if(ch == '\n'){
           	judge2(number,i,result);
    		judge3(number,i,result);
    		judge5(number,i,result);
    		judge11(number,i,result);
    		print(result,flag);
    		i = 0, flag = 1;
		}
        else if(ch != '-'){
            number[i] = ch;
            i++;
        }
        else break;
	}
	return 0;
}
