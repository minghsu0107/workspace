#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#define MAXN 30
#define L 7

// 車牌都是七個字元，但是每個字串後面都會有 '\0' 字元代表結尾，所以陣列大小至少要是 7+1=8
char license[MAXN][L+5];
 
int getHyphen(char *str){ // get the position of the hyphen (2 or 3, else return -1)
    if (str[2] == '-') return 2;
    return str[3] == '-' ? 3 : -1;
}
 
int multipleSameChar(char *str){ // check if an alpha or digit appears more than twice
    for(int i = 0; i < L; i++){
        int cnt = 1;
        for(int j = i + 1; j < L; j++)
            if (str[i] == str[j]) cnt++;
        if (cnt >= 3) return 1;
    }
    return 0;
}
 
int validSum(char *str){ // check if the sum of all digits cannot be divided by 7
    int sum = 0;
    for(int i = 0; i < L; i++)
        if (isdigit(str[i])) sum += str[i] - '0';
    return sum % 7 != 0; // no need to check if has at least one digit, since if there are no digits, sum remains 0 and it is invalid
}
 
int isValid(char *str){ // check if the string satisties all four constraints
    int sum = 0, haveNum = 0;
    int hyphen = getHyphen(str);
 
    if (hyphen == -1) return 0; // invalid (neither first nor second kind)
    if (!validSum(str)) return 0; // invalid (constraint 2.)
    if (multipleSameChar(str)) return 0; // invalid(constraint 3.)
 
    for(int i = 0; i < L; i++){
        char ch = str[i];
        if (i != hyphen && !isalnum(ch)) return 0; // invalid (constraint 1.)
        if (ch == '4' && str[i+1] == '4') return 0; // invalid (constraint 4.)
    }
 
    return 1;
}
 
 
int isSmaller(char *str1, char * str2){ // compare two strings
    int h1 = getHyphen(str1), h2 = getHyphen(str2);
    return h1 != h2 ? h1 < h2 : strcmp(str1, str2) < 0; // first check the type, if same type, check ASCII code using strcmp()
}
 
int sort(int *idx, int cnt){ // sort the index (selection sort)
    int tmp;
    for(int i = 0; i < cnt; i++){
        for(int j = i + 1; j < cnt; j++){
            if (isSmaller(license[idx[j]], license[idx[i]]))
                tmp = idx[i], idx[i] = idx[j], idx[j] = tmp;
        }
    }
}
 
int main(){
    int N, idx[MAXN], vcnt = 0;
 
    assert(scanf("%d", &N) == 1);
    for(int i = 0; i < N; i++){
        assert(scanf("%s", license[i]) == 1);
        if (isValid(license[i])) idx[vcnt++] = i; // safe the indices of all valid strings
    }
 
    sort(idx, vcnt);
 
    for(int i = 0; i < vcnt; i++)
        printf("%s\n", license[idx[i]]);
 
    return 0;
}

//每個條件判斷盡量寫成 function ，增加程式的易讀性。

//如果有需要用到字母的 ASCII 值，可以用單引號。例如 'A' <= ch ， 而不是 65 <= ch。程式碼比較乾淨也不容易出錯。

//善用 ctype.h 裡的 function。例如判斷 ch 是不是數字，可以用 isdigit(ch) ，不用自己寫成 '0' <= ch && ch <= '9'。

//比較字串大小時 (根據 ASCII 碼的值)，可以用 string.h 裡的 strcmp(const char*, const char*) 幫助判斷。

//關於isdigit(ch)： 若 ch 是不是數字，會回傳 0；否則會回傳 非零的值(只保證不是零，不一定是 1)
//其他類似的 function 包括 isalnum(ch), isalpha(ch) 等等也一樣。 