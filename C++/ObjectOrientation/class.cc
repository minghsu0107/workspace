#include <iostream>
using namespace std;

class DebtCard {
public:
  DebtCard(string name, double balance);  
  string getName();
  double getBalance();
  void deposit(double amount); 
  void withdraw(double amount);
  void setName(string newName);
  void setBalance(double newBalance);
  void modify();
  ~DebtCard();                //destructor(usually using it to delete new memory)
private:                      //如果沒有定義解構函式時 程式會自動建立一個沒有實作內容的解構函式並自動於適當的時機執行
  string name;
  double balance;
  bool overLimit(double amount); //外部無法使用 overLimit() 函數
};
DebtCard::DebtCard(string name, double balance) : name(name), balance(balance) {}

string DebtCard::getName() {
  return name;
}
double DebtCard::getBalance() {
  return balance;
}
void DebtCard::deposit(double amount) {
  if (overLimit(amount)) return;
  balance += amount;
}

void DebtCard::withdraw(double amount) {
  if (overLimit(amount)) return;
  balance -= amount;
}

bool DebtCard::overLimit(double amount) {
  return amount > 20000;
}
void DebtCard::setName(string name) {
  this->name = name;
  // 或是 (*this).name = name;
}
void DebtCard::setBalance(double balance) {
  this->balance = balance;
  // 或是 (*this).balance = balance;
}
void DebtCard::modify(){
    this->deposit(100);
}
DebtCard::~DebtCard(){
    cout<<"end!"<<endl;
}


void modify3(DebtCard *x) {
    x->deposit(100);
}
void modify4(DebtCard &x) {
    x.deposit(100);
}
int main() {
  DebtCard d("Stone", 5000);
  d.deposit(100);
  d.withdraw(350);
  d.deposit(25000);
  d.withdraw(35000);
  //d.overLimit(); // compile error
  // print Stone 4750
  cout << d.getName() << " " << d.getBalance() << endl;
  
  DebtCard d1("Jimmy", 1000);
  DebtCard *d2 = &d1;
  DebtCard &d3 = d1; 

  d1.deposit(150);
  d2->deposit(500);
  d3.deposit(1000);
  //d1, *d2 和 d3 全部都參考到同一個 DebtCard 物件 因此destructor總共只消滅3個物件
  cout << d1.getBalance() << endl;
  cout << (*d2).getBalance() << endl;
  cout << d3.getBalance() << endl;   
  
  DebtCard db("Jimmy", 1000);
  db.modify();
  cout << db.getBalance() << endl;
  modify3(&db);
  cout << db.getBalance() << endl;
  modify4(db);
  cout << db.getBalance() << endl;
}