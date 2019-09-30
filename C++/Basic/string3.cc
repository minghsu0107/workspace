#include <iostream>
#include <cstring> 
using namespace std;

int main(){
    char str[]={};
    if( ! str[0] ) {      //空字元在作條件判斷時會被視為0
    cout << "字串為空"<<endl;   // 即　if(str[0] == '\0') cout << "字串為空";
    }
    
    char str1[80] = {'\0'}; 
    char str2[] = "caterpillar"; 
    
    char p[50]="world";
    char* q=str2;
    strcpy(p,q); 
    cout<<p<<" "<<q<<endl;

    cout << "str1: " << str1 << endl
         << "str2: " << str2 << endl
         << endl; 

    // 將str2複製給str1 (const char* 轉char*)
    strcpy(str1, str2); //char *strcpy(char *dest, const char *src); 
    cout << "str1: " << str1 << endl
         << "str2: " << str2 << endl
         << endl;

    // 將str2接在str1後 
    strcat(str1, str2); //char *strcat(char *dest, const char *src);
    cout << "str1: " << str1 << endl
         << "str2: " << str2 << endl
         << endl;

    cout << "str1長度：" << strlen(str1) << endl
         << "str2長度：" << strlen(str2) << endl //length doesn't include '0'
         << endl;

    cout << "str1與str2比較：" << strcmp(str1, str2) << endl
         << endl;
    //int strcmp(const char *s1, const char *s2);
    //相同就傳回0，str1大於str2則傳回大於0的值，
    //小於則傳回小於0的值，比較的標準是依字典順序比對
    
}