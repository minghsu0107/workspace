#include<stdio.h>
#include<string.h>
int main(void){
    int map[26][26] = {0};
    int check[26] ={0};
    int T;
    scanf("%d", &T);
    char a[100];
    while(scanf("%s",a) != EOF) {
        int l = strlen(a);
        for(int i = 0; i < l-1; i++) {
            map[ a[i] - 'a'][ a[i+1] - 'a' ] ++;
        }
    }
    int max = T;
    int x;
    for(int i = 0; i< 26; i++) {
        for(int j  =0; j< 26; j++){
            if( map[i][j] > max){
                x = i;
                max = map[i][j];
            }
        }
    }
    char new_word[26];
    char length = 0;
    while(1){
        if(check[x] == 1) break;
        check[x]++;
        new_word[length++] = x + 'a';
        new_word[length] = '\0';
        max = T;
        int temp = -1;
        for(int i =0; i<26; i++){
            if(check[i] == 0 && map[x][i] > max){
                temp = i;
                max = map[x][i];
            }
        }
        if(temp == -1) break;
        x = temp;
    }
    for(int i = 0; i< 26; i++) {
        for(int j  =0; j< 26; j++){
            printf("%d",map[i][j]);
            if( j != 25) printf(" ");
        }
        printf("\n");
    }
    printf("%s", new_word);
    return 0;
}
