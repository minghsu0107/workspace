#include <bits/stdc++.h>
using namespace std;
#define MAX 200005
int arr[MAX], isIn[MAX] = {}, n, m, k;
struct Smaller
{
  bool operator() (pair<int,int> a, pair<int,int> b) { 
       return a.first < b.first; 
  }
};
struct Greater
{
  bool operator() (pair<int,int> a, pair<int,int> b) { 
       return a.first > b.first; 
  }
};
inline void write(int x)
{
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
template <typename T>
inline bool ret(T& x) {
    char c = 0; bool flag = false;
    while (c = getchar(), (c < '0' && c != '-') || c > '9') if (c == -1) return false;
    c == '-' ? (flag = true, x = 0) : (x = c - '0');
    while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + c - '0';
    if (flag) x = -x;
    return true;
}
template <typename T, typename ...Args>
inline bool ret(T& x, Args& ...args) { return ret(x) && ret(args...); }
 
int main() {
    ret(n, m, k);
    // max heap
    priority_queue<pair<int,int>, vector<pair<int,int> >, Smaller > p;
    // min heap
    priority_queue<pair<int,int>, vector<pair<int,int> >, Greater > q;
    
    for (int i = 0; i < n; ++i) ret(arr[i]);
    for (int i = 0; i < m; ++i) {
        p.emplace(arr[i], i);
        isIn[i] = 1;
        if (i >= k) {
            q.emplace(p.top());
            isIn[p.top().second] = 2;
            p.pop();
        }
    }
    write(p.top().first), puts("");
    pair<int,int> s;
    for (int i = m; i < n; ++i) {
        // insertion
        p.emplace(arr[i], i);
        isIn[i] = 1;
        do {
            s = p.top();    
            p.pop();
        } while (isIn[s.second] == 0);
        q.emplace(s);
        isIn[s.second] = 2;
        
        // deletion
        if (isIn[i - m] == 1) {    
            isIn[i - m] = 0;    
            do {
                s = q.top();
                q.pop();
            } while (isIn[s.second] == 0);
            p.emplace(s);
            isIn[s.second] = 1;
        }
        isIn[i - m] = 0;
        
        // get kth
        s = p.top();
        while (isIn[s.second] == 0) {
            p.pop();
            s = p.top();
        }
        write(s.first), puts("");
    } 
}