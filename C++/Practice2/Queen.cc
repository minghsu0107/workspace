#include <iostream>  
using namespace std;  
int Ans[21], Used[21], n, ans;  
int Check(int d, int k)  
{  
    int i;  
    for (i=0; i<d; i++)  
        if (Ans[i]+i==k+d||Ans[i]-i==k-d) return 1;  
    return 0;  
}  
void Queen(int d)  
{  
    int i;  
    if (d==n)  
    {  
        for (i=0; i<n; i++)  
            cout << Ans[i] << " ";  
        cout << endl;  
        ans++;  
        return;  
    }  
    for (i=1; i<=n; i++)  
    {  
        if (Used[i]||Check(d,i)) continue;  // check行跟對角線
        Used[i]=1;  
        Ans[d]=i;  
        Queen(d+1);  
        Used[i]=0;  
    }  
}  
int main()  
{  
    int i;  
    cin >> n;  
    ans=0;  
    for (i=1; i<=n; i++) Used[i]=0;  
    Queen(0);  
    return 0;  
}  