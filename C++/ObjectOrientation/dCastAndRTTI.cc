#include <iostream> 
#include <typeinfo> 
using namespace std; 

//Run-Time Type Information 使用typeid()來取得物件於執行時期的資訊
//typeid()使用時傳入一個物件: typeid(object); typeid()會傳回一個type_info物件 其擁有幾個成員
//const char *name(); // 取得物件型態名稱 
//bool before(const type_info &ob);  // 當物件的名稱順序位於ob之前時，傳回true 
//bool operator==(const type_info &ob);  // 比較物件型態是否相同 
//bool operator!=(const type_info &ob); // 比較物件型態是否不同


class Base { 
public: 
    virtual void foo() = 0;
}; 

class Derived1 : public Base { 
public: 
    void foo() { 
        cout << "Derived1" << endl; 
    } 
 
    void showOne() {
        cout << "Yes! It's Derived1." << endl;
    }
}; 

class Derived2 : public Base { 
public: 
    void foo() { 
        cout << "Derived2" << endl; 
    } 
 
    void showTwo() {
        cout << "Yes! It's Derived2." << endl;
    }
}; 

void showWho(Base *base) {
    base->foo();
 
    if(typeid(*base) == typeid(Derived1)) {
        Derived1 *derived1 = static_cast<Derived1*>(base);
        derived1->showOne();
    }
    else if(typeid(*base) == typeid(Derived2)) {
        Derived2 *derived2 = static_cast<Derived2*>(base);
        derived2->showTwo(); 
    } 
}

//dynamic_cast用來將一個基底類別的指標轉型至衍生類別指標 稱 為「安全向下轉型」（Safe downcasting）
//它在執行時期進行型態轉換 首先確定轉換目標與來源是否屬同一個類別階層 接著才真正進行轉換
//如果是一個指標 則轉換成功時傳回位址 失敗的話會傳回0
//如果是參考 轉換失敗會丟出 bad_cast例外
void showWho2(Base *base) {
    base->foo();
    
    if(Derived1 *derived1 = dynamic_cast<Derived1*>(base)) {
        derived1->showOne();
    }
    else if(Derived2 *derived2 = static_cast<Derived2*>(base)) {
        derived2->showTwo();    
    } 
}

void showWho3(Base &base) {
    try {
        Derived1 &derived1 = dynamic_cast<Derived1&>(base);
        base.foo();
        derived1.showOne();
    }
    catch(bad_cast) {
        cout << "bad_cast 轉型失敗" << endl;
    }
}
int main() { 
    Base *ptr; // 基底類別指標 
    Derived1 derived1;
    Derived2 derived2;

    ptr = &derived1; 
    cout << "ptr 指向 " 
         << typeid(*ptr).name() 
         << endl; 

    ptr = &derived2; 
    cout << "ptr 指向 " 
         << typeid(*ptr).name() 
         << endl;

    showWho(&derived1);
    showWho2(&derived2);
    showWho3(derived1);
    showWho3(derived2);
}