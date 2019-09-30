#include <iostream>
using namespace std;

int main() { 
    int N;
    cin>>N;
    for (int i = 1, j = 1; 
         j <= N; 
         (i==N)?(i=(++j/j)):(i++)) { 
 
        int tmp = i * j; 
        cout << i << "x" << j; 
        cout << ((tmp>=10)? "=": "= ") ; //or cout<<i<<"x"<<j<<"="<<setw(2)<<tmp;
        if(i == N) 
            cout << i*j << endl; 
        else 
            cout << i*j << "  "; 
    } 
}