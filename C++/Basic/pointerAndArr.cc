#include <iostream>
#include <math.h>
//#include <string>
using namespace std;

int main(){
    char carr[10] = {'\0'}; //字元自動初始為空字元
    bool barr[10] = {false};//boolean數自動初始為false
    
    int a[100]={};
    printf("%p ",a);
    cout<<a<<endl;
    cout<<&a<<endl;
    cout<<&a[0]<<endl<<endl;;
    
    int b[3][2]={};
    cout<<&b[1][0]<<endl;
    cout<<b[1]<<endl;
    cout<<&b[2][0]<<endl;
    cout<<b[2]<<endl<<endl;
    
    int num=10;
    int *p=&num;
    *p=5;
    int *q=0;
    q=&num;
    int *k=NULL;
    cout<<"p: "<<p<<endl;//num的位址
    cout<<"&p: "<<&p<<endl;
    cout<<"*p: "<<*p<<endl;
    printf("%s: q: %p, &q: %p, *q: %d\n","Here are the answers",q,&q,*q);
    cout<<"k: "<<k<<endl;
    cout<<"&k: "<<&k<<endl;
    //cout<<"*k: "<<*k<<endl;//compiler error
    
    int n1=1;
    int n2=2;
    int *x = &n1;
    cout<<"*x: "<<*x<<endl;
    int &y = n1;// y -> 1, y為n1的參考變數
    cout<<"address of y(&y): "<<&y<<" address of n1(&n1): "<<&n1<<endl; //參考變數與本身記憶體位址相同
    y=3;
    cout<<"y: "<<y<<", n1: "<<n1<<endl;//y變數其實是n1變數的別名, 使用y變數和n1變數會有相同的效果
    x = &n2;
    cout<<"*x: "<<*x<<endl;
    
    int arr[] = { 1, 2, 3, 4, 5 };
    int *ptr;
    ptr = &arr[0];//等價於ptr = arr
    for (int i=0; i<5; i++) {
      cout << ptr << ':';
      cout << ptr[i] <<' '<<*ptr<<" "<<*(arr+i)<<" ";
      ptr++;
    }
    cout<<endl;
    
    int *array;   //動態配置一維陣列
    int size=5;                   //int *pointr = new int(100);動態配置一個int型態大小的記憶體 儲存值設定為100
    array = new int[size];        // or int*array=new int[size];
    for (int i=0;i<size;i++){
      array[i]=i;                 //配置了5個int大小的空間
      cout<<array[i]<<" "<<*(array+i)<<" "; 
    }
    cout<<endl<<array<<endl;//並回傳空間的第一個位址
    delete [] array;//回收int型態記憶體
    
    
    int m=4;
    int n=5;
    int *potr = new int[m*n]; 
 
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            *(potr + n*i + j) = i+j;
        }
    }

    for(int i = 0; i < m; i++) { 
        for(int j = 0; j < n; j++) {
            cout << *(potr+n*i+j) << "\t"; 
        } 
        cout << endl; 
    } 

    delete [] potr; 
    
    
}