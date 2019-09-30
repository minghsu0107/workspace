#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// vector can be used to implement stack
int main(){
    vector<int> vec1;//宣告一個空的, 一個元素都沒有的 vector
    vector<int> vec2(5);//產生一個長度為 5, 每個值為 0 的 vector
    vector<int> vec3(5, 3);//產生一個長度為 5, 每個值為 3 的 vector
    
    vector<int> vec5(vec3);
    // vec5.assign(vec3.begin(), vec3.end());
    // copy(vec3.begin(), vec3.end(), back_inserter(vect5));

    int iarr1[] = {1, 2, 3, 4, 5};
    vector<int> ivector1(iarr1 + 1, iarr1 + 4);//元素的起始位址與最後一個元素的上一個位址
    for(int i = 0; i < ivector1.size(); i++) {
        cout << ivector1[i] << " ";
    }
    cout << endl;
    
    vec3.pop_back();
    int len = vec3.size();
    // 印出 3 3 3 3
    for (int i=0; i<len; i++) {
      cout << vec3[i] << " ";
    }
    cout<<endl;
    for (int x: vec3) {
      cout << x << " ";//迴圈每一次都會從 vec 中選擇一個元素放到 x 變數
                       //當所有 vec 中的元素都被挑選過, 迴圈就會結束
    }
    cout<<endl;
    
    vector<int> vc;
    cout << vc.size() << endl; // 印出 0
    for (int i=0; i<3; i++) {
      vc.push_back(i);
    }
    cout << vc.size() << endl; // 印出 3, 內容: 0, 1, 2
    // begin() 與 end() 為位址
    int iarr2[] = {1, 2, 3};
    vector<int> vec(3);
    copy(iarr2, iarr2 + 3, vec.begin());
    vec.insert(vec.begin()+1, 2, 88);//在第vec.begin()+1個元素後面塞2個88
    cout << vec.size() << endl; // 印出 5, 內容: 1, 88, 88, 2, 3
    vec.insert(vec.end()-1, 2, 99);
    cout << vec.size() << endl; // 印出 7, 內容: 1, 88, 88, 2, 99, 99, 3 
    
    vector<int> vect(iarr1 + 1, iarr1 + 4);;
    vect.erase(vect.begin()+1);
    cout << vect.size() << endl; // 印出 4, 內容: 1, 3, 4, 5
    vect.erase(vect.end()-1);
    cout << vect.size() << endl; // 印出 3, 內容: 1, 3, 4
    
    int iarr[] = {30, 12, 55, 31, 98, 11, 41, 80, 66, 21};
    vector<int> ivector(iarr, iarr + 10);
    
    sort(ivector.begin(), ivector.end());
    
    for(vector<int>::iterator it = ivector.begin();
        it != ivector.end();
        it++) {
    cout << *it << " ";
    }
    cout << endl;

    cout << "輸入搜尋值：";
    int search = 0;
    cin >> search;
 
    vector<int>::iterator it = 
    find(ivector.begin(), ivector.end(), search);
 
    if(it != ivector.end()) {
        cout << "找到搜尋值！" <<*it<<endl;
    }
    else {
        cout << "找不到搜尋值！" << endl;
    }
 
    // 反轉 
    reverse(ivector.begin(), ivector.end());
 
    for(vector<int>::iterator it = ivector.begin();
        it != ivector.end();
        it++) {
 
        cout << *it << " ";
    }
    cout << endl;
}