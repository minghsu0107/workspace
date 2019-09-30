//每個數字只有「取」和「不取」兩種情況，分別遞迴下去處理即可
//而 Sum 函數裡有個參數 s 則是記錄到目前為止加起來是多少
//如果已經超過我們設定的總和，則不需要再繼續往下展開。

#include <iostream>  
using namespace std;  
int Num[20], Used[20], n, m;  
int c=0;  
void Sum(int d, int s)  
{  
    int i;  
    if (s==m)  
    {  
        for (i=0; i<d; i++){  
            if (Used[i]) {  
               cout << Num[i] << " ";  
               c++;  
            }  
               
        }  
        cout << endl;  
        return;  
    }  
    if (d==n||s>m) return;  
    Used[d]=1;  
    Sum(d+1, s+Num[d]);  
    Used[d]=0;  
    Sum(d+1, s);  
}  
int main()  
{  
    int i;  
    cin >> n >> m;  
    for (i=0; i<n; i++) cin >> Num[i];  
    Sum(0, 0);  
    if(c==0) cout<<"NO"<<endl;  
    return 0;  
}  