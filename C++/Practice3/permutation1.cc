#include <iostream>  
using namespace std;  
int Ans[20], Used[21], n;  //Ans用來存放一組可能的答案
void Perm(int d)  
{  
    int i;  
    if (d==n)  
    {  
        for (i=0; i<n; i++)  
            cout << Ans[i];  // 印出一組可能的答案
        cout << endl;  
        return;  
    }  
    for (i=1; i<=n; i++)  
    {  
        if (Used[i]) continue;  
        Used[i]=1;  
        Ans[d]=i;  
        Perm(d+1);  
        Used[i]=0;  
    }  
}  
int main()  
{  
    int i;  
    cin >> n;  
    for (i=1; i<=n; i++) Used[i]=0;  
    Perm(0);  
}  