#include <iostream>  
using namespace std;  
int Ans[20], n;  //Ans用來存放一組可能的答案
bool solution[20];
void com(int d)  
{  
    int i;  
    if (d==n)  
    {  
        for (i=0; i<n; i++)  
            if(solution[i]) cout << Ans[i];  // 印出一組可能的答案
        cout << endl;  
        return;  
    }  
    solution[d]=true;
    Ans[d]=d+1;
    com(d+1);
    
    solution[d]=false;
    com(d+1);
}  
int main()  
{  
    int i;  
    cin >> n;  
    for (i=0; i<n; i++) solution[i] = false;  
    com(0);  
}  