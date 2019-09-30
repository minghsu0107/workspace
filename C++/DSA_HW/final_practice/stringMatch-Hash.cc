#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define prime_mod 1073676287
#define MAXN 1000010
using namespace std;
typedef long long T;

string s, b;
int cnt0, cnt1, slen, blen;

T h[MAXN];
T h_base[MAXN];

inline void hash_init(int len, T prime=0xdefaced) {
    h_base[0] = 1;
    for(int i = 1;i <= len; ++i){
        h[i] = (h[i-1] * prime + b[i-1]) % prime_mod;
        h_base[i] = (h_base[i-1] * prime) % prime_mod;
    }
}
inline T get_hash(int l, int r) {
    return (h[r+1]-(h[l]*h_base[r-l+1])%prime_mod+prime_mod)%prime_mod;
}

int get_max() {
    for (int i = 1; i < blen; ++i) {
        if (get_hash(i, blen-1) == get_hash(0, blen-1-i))
            return blen - i;
    }
    return 0;
}

int main() {
    IOS
    cin >> s >> b;

    
    slen = s.size();
    blen = b.size();
    hash_init(blen);

    for (int i = 0; i < slen; i++) {
        if (s[i] == '0')
            cnt0++;
        else
            cnt1++;
    }

    int l = get_max();
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