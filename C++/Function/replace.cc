#include<iostream>
#include<string>
using namespace std;
int main()
{   
	//将line中的第一个&替换成1 
	string line = "qwer& &qwer&& &&";
	line = line.replace (line.find("&"), 1, "1");
	cout << line << endl;
    
    //用str替换从指定位置0开始长度为5的字符串
	string line3 = "qwer& &qwer&& &&";
	char* str = "012345";
	line3 = line3.replace (0, 5, str); 
	cout << line3 << endl;
    
    //将line字符串0到5位置上的字符替换为substr的指定子串（从'1'位置开始的3个字符） 
	string line4 = "qwer& &qwer&& &&";
	string substr = "012345";
	line4 = line4.replace(0, 5, substr, substr.find("1"), 3);
	cout << line4 << endl;
}