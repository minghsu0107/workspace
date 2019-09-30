#include<bits/stdc++.h> 
#define int long long 
using namespace std;
int t;
vector<int> s;
int cnt[1000009];
class discretization{
    private:
        vector<int> lisan,status;
    public:
        inline vector<int> com(vector<int> a)
        {
            status.resize(a.size());
            lisan = a;
            sort(lisan.begin(),lisan.end());
            lisan.resize(unique(lisan.begin(),lisan.end())-lisan.begin());
            int len = a.size();
            for(int i = 0; i < len; i++) 
                status[i] = lower_bound(lisan.begin(),lisan.end(),a[i])-lisan.begin();
            return status;
        }
}li;

class BIT{
    private:
        vector<int> BITT;
        int dis;
    public:
        inline void init(int n) {
            BITT.clear();
            BITT.resize(n+1,0);
            dis = n;
        }
        inline void update(int i,int x)
        {
            while(i <= dis) {
                BITT[i] += x;
                i += i&-i;
            }
        }
        inline int sum(int i) {
            int res = 0;
            while(i > 0) {
                res += BITT[i];
                i -= i&-i;
            }
            return res;
        }
}bit;
main() {
    int aa = 0;
    ios_base::sync_with_stdio(0); cin.tie(0);
    while(cin >> t && t) {
        s.clear(); memset(cnt,0,sizeof(cnt));bit.init(t);
        for(int i = 0; i < t; i++) {
            int a; cin >> a;
            s.push_back(a);
        }
        s = li.com(s);

        for(auto x:s) cnt[x]++;
        for(int i = 1; i < t; i++) cnt[i] += cnt[i-1];
        int ans = 0;
        // bit.sum(x) = sum of number of elements that < x in current cond.
        for(auto i:s) {
            if(i != 0) ans += cnt[i-1]-bit.sum(i);
            bit.update(i+1, 1); // for x > i, sum[x] += 1
        }

        cout << "Case #" << ++aa << ": " << ans << '\n';
    }
    return 0;
}
/*
每讀入一個數字，就看看若排序完的話，在它前面應該要有幾個數，
再看看實際上有多少數在它前面(看個數前綴和)，相減後就代表有多少個比它小但在它後面，
為了看有幾個數要用BIT，要先將資料離散化。
*/
