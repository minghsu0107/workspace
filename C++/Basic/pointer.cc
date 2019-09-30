#include <iostream> 
using namespace std; 

void foo(const int *p) {
    int *v = const_cast<int*> (p); //使用const_cast改變*p指標的唯讀性
    *v = 20; 
}
int main() { 
    int var = 10; 
    void *vptr = &var ; 
 
    // 下面這句不可行，void型態指標不可取值 
    //cout << *vptr << endl;
 
    // 轉型為int型態指標並指定給iptr 
    int *iptr = reinterpret_cast<int*>(vptr);
    cout<<vptr<<endl;
    cout << *iptr << endl;
    int *&ref = iptr; //定義指標型態的參考&ref
    *ref=15;
    cout<<*iptr<<endl;
    
    int **pt=&iptr;
    int **&rf=pt;    //定義雙重指標型態的參考&rf
    cout<<"pt: "<<pt<<"\t"<<"&iptr: "<<&iptr<<endl;
    cout<<"*pt: "<<*pt<<"\t"<<"iptr: "<<iptr<<endl;
    cout<<"**pt: "<<**pt<<"\t"<<"*iptr: "<<*iptr<<"\t"<<"var: "<<var<<endl;
    **rf=30;
    cout<<"**pt: "<<**pt<<"\t"<<"*iptr: "<<*iptr<<"\t"<<"var: "<<var<<endl;
    
    cout << "var = " << var << endl; 
    foo(&var); 
    cout << "var = " << var << endl; 
}