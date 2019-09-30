#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <string.h>
using namespace std;

int dp[101];

void lis(int arr[],int n) {  
    for (int i = 0; i < n; i++) {  
        dp[i] = 1;  
    }  
    for (int i = 0;i < n; i++) {  
        for (int j = 0; j < i; j++) {  
            if(arr[j] < arr[i]) {  
               dp[i] = max(dp[i], dp[j] + 1);   
            }  
        }  
    }  
    int longest = 0;  
    for(int i = 0; i < n; i++) {  
        longest = max(longest, dp[i]);  
    }  
    cout << longest;  
}  

int main(){
   char a[101];
   char b[101];
   cin >> a >> b;
   int alen = strlen(a);
   int blen = strlen(b);
   map<char, deque<int> > mp;
   for(int i = 0; i < alen; i++) {
      mp[a[i]].push_front(i);
   }
   int l[10000];
   int len = 0;
   for(int i = 0; i < blen; i++) {
       if (!mp[b[i]].empty()){
           for(deque<int>::iterator it = mp[b[i]].begin();
              it != mp[b[i]].end();
              it++) {
              l[len] = *it;
              len++;
           }
       }
   }
   //for(int i=0;i<l.size();i++){
   //    cout<<l[i]<<" ";
   //}
   lis(l,len);
}
/*
假設比較的字串有 A  B 二集合

A = abcbdab

B = bdcaba

 

第一步： 將 A 集合轉成數字集合  (姑且稱為 C)

第二步：求 C 集合的 LIS  ( longest increasing subsequence ) 

 

第一步：將 A 集合轉成數字集合  (姑且稱為 C)

 

方法： 將 A 集合的元素用 B 集合相同元素的位置代替 (大到小）

例如 (假設從 1 開始 => A[1] = a, B[1] = b)

a = {6, 4}    ,    b = {5, 1}    ,    c = {3}    ,    d = {2}

 

C = {6, 4,  5, 1, 3, 5, 1, 2, 6, 4, 5, 1}

 

問題1: 為什麼大到小呢？  

因為如果是小到大，相同字元會被取很多次  (e.g .  b = {1, 5}  , 取 1 5 為 LIS => bb)

 

問題2: 為什麼這樣做會轉變為 LIS 問題呢？

如果我們把相同字元括弧起來，C = { (6, 4),  (5, 1), (3), (5, 1), (2), (6, 4), (5, 1)}

那麼 LCS 要的就是找出最多括弧數，又因為 LIS 為遞增，所以每個括弧至多出現一次
*/