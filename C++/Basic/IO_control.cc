#include <iostream> 
#include <iomanip> 
using namespace std; 
                                                                                
int main() {
    cout << oct << 50 << endl    // 8進位顯示 
         << hex << 50 << endl;   // 16進位顯示 
                                                                                
    // 九九乘法表 
    for(int j = 1; j < 10; j++) { 
       for(int i = 2; i < 10; i++) { 
           cout << i << "*" << j << "=" << dec << setw(2) << i*j; 
           cout << "  "; 
       } 
       cout << endl; 
    }
    
    bool boolnum; 

    boolnum = true; 
    cout << boolalpha << boolnum << endl; 

    boolnum = false; 
    cout << boolalpha << boolnum << endl;  
    return 0; 
}
/*
boolalpha 	       讓bool輸出時顯示true與false
dec 	           10進位顯示
endl  	           輸出new line字元
ends 	           輸出Null字元
fixed 	           以正常的數字格式顯示
flush 	           清除串流
hex 	           16進位顯示
left 	           靠左對齊
oct 	           8進位顯示
right 	           靠右顯示
scientific 	       科學記號表示
setbase(int b) 	   指定數字基底
setfill(int c) 	   指定填充字元
setprecision(int p)指定顯示精確度
setw(int w)  	   指定欄位寬度，並以16進位顯示
showbase 	       顯示數字基底，例如0x11
showpoint  	       顯示小數
showpos 	       正數顯示+號
skipws 	           忽略輸入的空白字元
upperbase 	       字母大寫
ws 	               忽略前導的空白字元
noboolalpha 	   關閉boolalpha的使用
noshowbase 	       關閉showbase的使用
noshowpoint 	   關閉showpoint的使用
noshowpos  	       關閉showpos的使用
noskipws 	       關閉skipws的使用
nouppercase 	   關閉uppercase的使用
*/