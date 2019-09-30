#include <iostream>
#include <functional>
#include <random>
using namespace std;
int main(){
    std::random_device rd; // 種子產生器
    std::mt19937 gen = std::mt19937(rd()); //使用mt19937引擎
    std::uniform_real_distribution<> dis(-1, 1); //使用平均分佈 

    auto randfun = std::bind(dis, gen); //將引擎和分佈綁在一起變成新函數 randfun

    cout<<randfun()<<' '<<randfun()<<' '<<randfun()<<endl; //可以直接重複呼叫
}