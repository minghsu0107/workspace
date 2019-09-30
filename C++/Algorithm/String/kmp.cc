#include <iostream>
#include <cstring>
using namespace std;
 
const int N = 1000002;
// nxt[i] saves the longest length that prefix == suffix 
// (excluding the entire string itself)
// in substring[1, i] (index starts from 1)
int nxt[N]; // Next数组是从1开始的
char S[N], T[N];
int slen, tlen;
 
void getNext() {
    int j, k;
    j = 0; k = -1; nxt[0] = -1;
    while(j < tlen)
        if(k == -1 || T[j] == T[k])
            nxt[++j] = ++k;
        else
            k = nxt[k];
}
/*
返回模式串T在主串S中首次出现的位置
返回的位置是从0开始的。
*/
int KMP_Index() {
    int i = 0, j = 0;
    getNext();
 
    while(i < slen && j < tlen) {
        if(j == -1 || S[i] == T[j]) {
            i++; j++;
        }
        else
            j = nxt[j];
    }
    if(j == tlen)
        return i - tlen;
    else
        return -1;
}
/*
返回模式串在主串S中出现的次数
*/
int KMP_Count() {
    int ans = 0;
    int i, j = 0;
 
    if(slen == 1 && tlen == 1) {
        if(S[0] == T[0])
            return 1;
        else
            return 0;
    }
    getNext();
    for(i = 0; i < slen; i++) {
        while(j > 0 && S[i] != T[j])
            j = nxt[j];
        if(S[i] == T[j])
            j++;
        if(j == tlen) {
            ans++;
            j = nxt[j];
        }
    }
    return ans;
}
int main() {
    cin >> S >> T;
    slen = strlen(S);
    tlen = strlen(T);
    cout << KMP_Index() << endl;
    cout << KMP_Count() << endl;
    for (int i = 1; i <= tlen; ++i)
        cout << nxt[i] << " ";
    cout << endl;
    return 0;
}