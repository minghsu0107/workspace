#include <iostream>  
using namespace std;  

// P M 取 N

int Ans[10],Used[11];  
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
        for (int i = 1; i <= M; i++)  
        {   
            if(Used[i]) continue;
            Used[i] = 1;
            Ans[d] = i;  
            Enum(d + 1);  
            Used[i] = 0;
        }  
    }  
}  
  
int main()  
{  
    while (cin >> N >> M)  
    {   
        for(int i = 1; i <= N; i++) Used[i]=0;
        Enum(0);  
    }  
    return 0;  
}  