#include <iostream>  
#include <string.h>
using namespace std;  
char Ans[20],s[20];  //Ans用來存放一組可能的答案
bool solution[20];
void com(int d, int N)  
{  
    int i;  
    if (d==N)  
    {  
        for (i=0; i<N; i++)  
            if(solution[i]) cout << Ans[i];  // 印出一組可能的答案
        cout << endl;  
        return;  
    }  
    solution[d]=true;
    Ans[d]=s[d];
    com(d+1,N);
    
    solution[d]=false;
    com(d+1,N);
}  
int main()  
{  
    int i;  
    cin >> s;  
    int len = strlen(s);
    for (i=0; i< len; i++) solution[i] = false;  
    com(0, len);  
}  