#include <iostream> 
using namespace std; 

int main() { 
    cout.unsetf(ios::dec); // 取消10進位顯示 
    cout.setf(ios::hex | ios::scientific); // 16進位顯示或科學記號顯示 
    cout << 12345 << "  " << 100 << endl; 
                                                                                
    cout.setf(ios::showpos | ios::showpoint); // 正數顯示 + 號且顯示小數點 
    cout << 103.0 << ": " << -103.0 << endl; 

    return 0; 
}