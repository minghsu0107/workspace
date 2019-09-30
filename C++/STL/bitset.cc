#include <bitset>
#include <string>
#include <iostream>
using namespace std;
int main() {
	// 建立10bits 之 bitset
	bitset<10> a, b;
	// 建立10bits 之 bitset，並以無號數(長)整數初始化 bitset
	bitset<10> b1(222UL);
    // 以字串初始化 bitset
	string s = "1001101";
    bitset<10> b2(s);

    b[1] = b1[1]; // b[0] is LSB

    b = ~b1;
    b ^= b1;
    b1 &= b2;
    b2 |= b1;
    
    b <<= 2;
    b1 >>= 3;

    cout << a.size() << endl;
    cout << a.any() << endl; // whether there is 1 in bitset
    cout << a.none() << endl; // wheter there is no 1 in bitset
    cout << a.count() << endl; // number of 1 in bitset
    cout << a.size() - a.count() << endl; // number of 0 in bitset

    cout << a << endl;
    cout << a.to_string() << endl; // to string
    cout << a.to_ulong() << endl; // to unsigned long int

    b.set(); // set every bit to 1
    b.reset(); // set every bit to 0
    b.set(0); // b[0] = 1 or b.set(0, 1)
    b.reset(0); // b[0] = 0 or b.set(0, 0)
    b.flip(1); // or b[1] = ~b[1]
    b.flip(); // or b = ~b
}