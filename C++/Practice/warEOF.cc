#include <iostream>
using namespace std;

void war(int a,int b){
    if (a>b){
        cout<<"A"<<" "<<(a-b)<<endl;
    }
    else if(a<b){
        cout<<"B"<<" "<<(b-a)<<endl;
    }
    else{
        cout<<0<<endl;
    }
    
}
int main(){
    int A,B;
    while(1){
        cin>>A>>B; //先cin
        if ( cin.fail() ) {
            break; //再驗證輸入值 當沒有資料可以輸入的時候結束此程式
        }    
        war(A,B);
    }
}