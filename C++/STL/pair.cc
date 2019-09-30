#include <iostream>
#include <utility>
using namespace std;
int main() {
	
	pair<char, int> p, p1('a', 100), p2('a', 200);
    p = p1;
    cout << p.first << " " << p.second << endl;
    cout << (p2 > p1) << endl;

    // 非成員函式 make_pair 函式會回傳一個pair<A, B>
    // 不用特別指明第一項和第二項的型別，編譯器會自行幫你解析
    p = make_pair('a', 300);
    cout << p.first << " " << p.second << endl;
	return 0;
}