#include <iostream> 
#include <cstdarg>
using namespace std; 

double area(double, double=3.14); //預設引數(arguement)一旦出現在參數列，則其右邊的參數也必須設定預設引數
void foo(int, ...);       // ... 表示將使用不定長度引數，而之前必須告知將傳遞幾個不定長度引數(int)
void foo2(int*,int,int,...);

int main() { 
    double R, PI; //R,PI為引數(arguememnt)
    cout << "輸入半徑與PI: "; 
    cin >> R >> PI; 

    cout << "面積(自訂PI): " << area(R, PI)
         << endl; 
    cout << "面積(default): " << area(R) 
         << endl<<endl;
         
    double x = 1.1, y = 2.1, z = 3.9; 
    double a = 0.1, b = 0.2, c = 0.3; 

    cout << "三個引數：" << endl; 
    foo(3, x, y, z); 

    cout << "六個引數：" << endl; 
    foo(6, x, y, z, a, b, c); 
    cout<<endl;
    
    int m=4,n=3;
    int *mat=new int[m*n];
    foo2(mat,m,n,1,1,1,2,2,2,3,3,3,5,5,5);
    delete mat;
} 

double area(double r, double pi) { //r,pi為參數(parameter)
    return r*r*pi; 
}
void foo(int i, ...) { 
    // 宣告num_list 用來存不定長度引數
    va_list num_list; //va_list為一個特殊的型態（type）在va_start、 va_arg與va_end三個巨集（macro）時當作參數使用

    va_start(num_list, i);//啟始不定長度引數的巨集
    
    //double arr[i];
    //int len=0;
    
    //for(int j = 0; j < i; j++){
    //    arr[len]=va_arg(num_list, double);
    //    len++;
        //讀取不定長度引數的巨集 使用va_arg巨集取出引數內容 並指定將以何種資料型態取出
        //從num_list取出引數後 num_list為空(皆為0)
    //}
    //for (int k=0;k<len;k++){
    //    cout<<arr[k]<<endl;
    //}
    double sum=0;
    for (int k=0;k<i;k++){
        sum+=va_arg(num_list, double);
    }
    cout<<sum<<endl;
    
    va_end(num_list); //終止不定長度引數的巨集 將va_list重置為null
}
void foo2(int* mat,int m, int n,...){
    va_list p;
    va_start(p, m*n);
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            *(mat + n*i + j)=va_arg(p,int);
        }
    }
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            cout<< *(mat + n*i + j)<<" ";
        }
        cout<<endl;
    }
    va_end(p);
}
