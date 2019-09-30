#include <iostream>  
#include <string.h>
using namespace std;  
char Ans[20],s[20];  //Ans用來存放一組可能的答案
int m, n;  // C m 取 n
void com(int d, int len)
{  
    if (len == n)  
    {  
        for (int i=0; i<n; i++)  
            cout << Ans[i];  // 印出一組可能的答案
        cout << endl;  
        return;  
    }
    if (d == m) return;
    Ans[len]=s[d];
    com(d+1,len+1);
    com(d+1,len);
}
// backtracking
void com2(int d, int len)
{  
    if (len == n)  
    {  
        for (int i=0; i<n; i++)  
            cout << Ans[i];  // 印出一組可能的答案
        cout << endl;  
        return;  
    }
    for (int i = d; i < m; i++) {
        Ans[len] = s[i];
        com2(i+1, len+1);
    }
}  
int main()  
{  
    cin >> m >> n >> s;  
    int m = strlen(s);
    com(0, 0);
}  