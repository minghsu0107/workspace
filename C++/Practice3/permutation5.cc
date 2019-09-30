#include <iostream>
#include <string.h>
using namespace std;  

//重複排列
//當字母重覆出現次數很多次，此時可以使用 128 格的陣列
//每一格分別存入 128 個 ASCII 字元的出現次數，簡化程式碼。

int arr[128];
char Ans[20],s[20];
void Perm(int d,int N)  
{  
    int i;  
    if (d==N)  
    {  
        for (i=0; i<N; i++)  
            printf("%c",Ans[i]);  // 印出一組可能的答案
        cout << endl;  
        return;  
    } 
    for (i=0; i<128; i++)   // 枚舉每一個字母
    {  
        if (arr[i]>0){     // 還有字母剩下來，就要枚舉
          arr[i]--;        // 用掉了一個字母
          Ans[d] = i;      // char 變數可以直接存入 ascii 數值
          Perm(d+1,N);  
          arr[i]++;        // 回收了一個字母
        }
    }  
}  
int main()  
{  
    int i;  
    cin >> s;  
    int len=strlen(s);
    for (i=0; i<len; i++) arr[i]=0;  
    for (i=0; i<len; i++) arr[s[i]]++;
    Perm(0,len);  
}  