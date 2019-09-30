#include <iostream>
#include <string.h>
//#include "math.h"
using namespace std;

int main(){
    char buf[] = "1.1   2.2";
    char *pEnd ;
    double d1, d2;
    d1 = strtod(buf, &pEnd);
    d2 = strtod(pEnd, NULL);
    cout<<d1<<endl<<d2<<endl;
    
    char buffer[] = "11.22333";
    cout<<atof(buffer)<<endl;
    double a = strtod(buffer, NULL);//double strtod ( const char * str, char ** endptr );轉為倍精度
    cout<<a<<endl;
    
    char mat[]="123";
    int x=atoi(mat);//若是 long atol(const char*s) 則回傳long int
    cout<<x<<endl;  //double atof(const char *s) 回傳浮點數
    
    char mat2='1';
    cout<<atoi(&mat2)<<endl;
    
    char buffer_str[5]={'0'};
    scanf("%s",buffer_str);//只能輸入4個字元 要留一個空間給空字元
    cout<<buffer_str<<endl;
    
    const char *str = "hello"; // 唯讀
    const void *add ; //or *add=0;宣告add為pointer,儲存位址
    add = str; 
    cout << str << "\t" << add << endl;//add=str儲存的位址　即"hello"的位址
    cout << str << "\t" << *(str++) << endl;
    cout << str << "\t" << *(++str) << endl;

    const char *_str = "world"; 
    add = _str; 
    cout << _str << "\t" << add << endl;
    char *s[][2] = {"professor", "Justin",      //指標陣列(陣列中的元素為指標　每個指標存取一個字串常數的位址)
                      "teacher", "Momor", 
                      "student", "Caterpillar"};////括號可有可無 
    for(int i = 0; i < 3; i++) {
        cout << s[i][0] << ": " 
             << s[i][1] << endl; 
    }
    //每一個指標元素指向一個字串常數
                                                      
    for(int i = 0; i < 3; i++) {
        cout << &s[i][0] << ": " //指標元素的位址
             << *(s[i][1]+1) << endl; 
    }
    for(int i = 0; i < 3; i++) {
        s[i][0]="yes";
        cout << &s[i][0] << ": " << *s[i][0] << endl; //指標元素的位址不變 但該指標指向的記憶體的值就不同
    }
    char lf[6] = "abcde";
    char **mem;
    mem= new char*[3];
    for(int i=0;i<3;i++){
        mem[i]= lf;
    }
    for(int i=0;i<3;i++){
        cout<<mem[i]<<" ";
    }
    delete [] mem;
    cout<<endl;
    
    char ***pot; 
    pot = new char**[3]; 
    for (int i=0;i<3;i++){
        pot[i]=new char*[6];
        for (int j=0;j<6;j++){
            pot[i][j] = lf;
        }
    }
    for (int i=0;i<3;i++){
        for (int j=0;j<6;j++){
            cout<<pot[i][j]<<" ";
        }
        cout<<endl;
    }
    delete [] pot;
    cout<<endl;
    
    char **ven;
    ven= new char*[3];
    for(int i=0;i<3;i++){
        ven[i]= new char[4];
        for(int j=0;j<4;j++){
            ven[i][j]='a';
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            cout<<ven[i][j]<<" ";
        }
        cout<<endl;
    }
    delete [] ven;
    
    
    char aa[10]="123456789";
    int bb[10]={0};
    
    int num=strlen(aa);
    for(int i=0;i<num;i++){
      bb[i]=atoi(&aa[i]);  
      cout<<bb[i]<<endl;
    }
    for(int i=0;i<num;i++){
      bb[i]=(aa[i]-'0');
      cout<<bb[i]<<endl;
    }

}