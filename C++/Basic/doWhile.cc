#include <iostream> 
using namespace std;

bool more(){
    bool replay = false; 
    cout << "繼續(1:繼續 0:結束)？"; 
    cin >> replay; 
    return replay;
}

void game(){
    do {
        int input;
        cout << "輸入整數值："; 
        cin>>input;
        cout << "輸入數為奇數？" << ((input % 2) ? 'Y': 'N') << "\n"; 
        
    } while(more()); 
}
int main() { 
    game();
}