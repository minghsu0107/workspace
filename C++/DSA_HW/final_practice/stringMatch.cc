#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
string s, b;
int cnt0, cnt1, nxt[1000010];
void getNext(string p) {
    int i = 1, j = 0;
    nxt[0] = -1;
    while(i < p.size()) {
        if(j == -1 || p[i] == p[j]) {
            nxt[++i] = ++j;
        } else
            j = nxt[j];
    }
}
int KmpSearch(char* s, char* p) {
    int i = 0, j = 0;
    getNext(p);

    int sLen = strlen(s);
    int pLen = strlen(p);

    while (i < sLen && j < pLen) {
        if (j == -1 || s[i] == p[j])
            i++, j++;
        else
            j = nxt[j];
    }
    return j == pLen ? i - pLen : -1;
}
int main() {
    IOS
    cin >> s >> b;
    getNext(b);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0')
            cnt0++;
        else
            cnt1++;
    }

    int l = nxt[b.size()];
    int flag = 0;

    for (int i = 0; i < l; i++) {
        if (b[i] == '0' && cnt0 > 0) {
            cout << 0;
            cnt0--;
        } else if (b[i] == '1' && cnt1 > 0) {
            cout << 1;
            cnt1--;
        } else {
            flag = 1;
            break;
        }
    }

    if (!flag) {
        while (cnt0 > 0 || cnt1 > 0) {
            flag = 0;
            for (int i = l; i < b.size(); i++) {
                if (b[i] == '0' && cnt0 > 0) {
                    cout << 0;
                    cnt0--;
                } else if (b[i] == '1' && cnt1 > 0) {
                    cout << 1;
                    cnt1--;
                } else {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }
    }
    
    for (int i = 0; i < cnt0; i++)
        cout << 0;
    for (int i = 0; i < cnt1; i++)
        cout << 1;
    return 0;
}
/*
按最长前缀后缀一样的长度来输出，最后再补上剩下的
*/