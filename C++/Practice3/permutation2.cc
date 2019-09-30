#include <iostream>  
#include <string.h>
using namespace std;  
int Used[20];  // Ans用來存放一組可能的答案
char Ans[20],s[20];
void Perm(int d,int N)  
{  
    int i;  
    if (d==N)  
    {  
        for (i=0; i<N; i++)  
            cout << Ans[i];  // 印出一組可能的答案
        cout << endl;  
        return;  
    }  
    for (i=0; i<N; i++)  
    {  
        if (Used[i]) continue;  
        Used[i]=1;  
        Ans[d]=s[i];  
        Perm(d+1,N);  
        Used[i]=0;  
    }  
}  
int main()  
{  
    int i;  
    cin >> s;  
    int len=strlen(s);
    for (i=0; i<len; i++) Used[i]=0;  
    Perm(0,len);  
}  