//每組輸入有兩行，第一行有兩個正數數 N、M，
//接下來有 N 行，每行有兩個正整數 Ai、Bi，代表 Ai 有Bi個。請你印出總合為 M 的所有組合。

#include <iostream>
using namespace std;
int Num[20], Times[20], Used[20], n, m;
void Sum(int d, int s)
{
    int i, j;
    if (s==m)
    {
        for (i=0; i<d; i++)
            for (j=0; j<Used[i]; j++)
                cout << Num[i] << " ";
        cout << endl;
        return;
    }
    if (d==n||s>m) return;
    for (i=Times[d]; i>=0; i--)
    {
        Used[d]=i;
        Sum(d+1, s+Num[d]*i);
    }
}

//多用一個 Times[ ] 陣列來記錄每個數字的個數
//而 Used[ ] 陣列也從原本的記錄有沒有使用改成使用了幾個。

int main()
{
    int i;
    cin >> n >> m;
    for (i=0; i<n; i++) cin >> Num[i] >> Times[i];
    Sum(0, 0);
    return 0;
}