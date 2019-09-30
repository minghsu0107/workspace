#include <iostream>  
using namespace std;  
  
int Ans[10];  //製作一個陣列，用來存放一組可能的情形。陣列中不同的格子，就是不同的維度。
int N, M;  
void Enum(int d)  
{  
    if (d == N)  
    {  
        for (int i = 0; i < N; i++)  
        {  
            cout << Ans[i];  
        }  
        cout << endl;  
        return;  
    }  
    else  
    {  
        for (int i = 0; i <= M; i++)  
        {  
            Ans[d] = i;  
            Enum(d + 1);  
        }  
    }  
}  
  
int main()  
{  
    while (cin >> N >> M)  
    {  
        Enum(0);  
    }  
    return 0;  
}  