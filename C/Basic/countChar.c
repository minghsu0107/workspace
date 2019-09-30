#include <stdio.h>
#include <ctype.h>
#include <assert.h>
int main(){
    char str[100];
    int i = 0;
    int num = 0;
    int letter = 0;
    int m = 0;
    int k = 0;
    while(scanf("%c",&str[i])!=EOF){
        if(isalnum(str[i])){
            if(isdigit(str[i])) num++;
            else if(isalpha(str[i])){
                letter++;
                char ch = tolower(str[i]);
                if( ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u') m++;
                else k++;
            }
        }
        i++;
    }
    assert(m+k==letter);
    printf("%d %d %d %d",num,letter,m,k);
    return 0;
}