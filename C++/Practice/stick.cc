#include <iostream>
using namespace std;

int stick(int n){    //買了n支冰
    int maxEat=n;    //先吃掉n支冰
    int remainStick=n;  //吃了n支後剩餘n支棍
    while(remainStick>=5){//剩餘棍至少有5支才可換冰
        remainStick-=5;
        maxEat+=1; //每五支棍可多吃一支冰
        remainStick++; //吃完一支冰剩餘棍多一支
    }
    return maxEat; //回傳最多能吃的總數
}
int stick2(const int n,int remain){
    int max=n;
    if(n<5) return max;
    else if(remain<5) return max;
    else{
    max=1+stick2(n,remain-4);
    }
    return max;
}
int stick3(int n){
    int max=n;
    for (int rm=n;rm>=5;rm-=4){
        max++;
    }
    return max;
}
int main(){
    int N;
    cin>>N;
    cout<<stick3(N)<<endl;
    //int R=N;
    //cout<<stick2(N,R)<<endl;
}