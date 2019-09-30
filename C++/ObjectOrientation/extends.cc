#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pet {
public:
  Pet(string name, int age);
  void pat();
  virtual string info();
protected: //繼承它的子類別才可用
  string name;
  int age;
};

Pet::Pet(string name, int age): name(name), age(age) {}

void Pet::pat() {
  cout << this->info()  << endl;
}
string Pet::info(){
  return "I am " + name + " age " + to_string(age);
}

class Cat : public Pet {
public:
  Cat(string name, int age, string color) :
    Pet(name, age), color(color) {}
  //virtual 表程式執行才判斷是呼叫哪個物件的函式　而非事先編譯好
  string info() {
    return "This is Cat " + name + "," + to_string(age) + "," + color;
  }
  //void pat() {
  //  cout << this->info() << endl;
  //}
private:
  string color;
};


class Spider {
public:
Spider(){
  cout<<"con1"<<endl; //constructor
}
virtual void act();
virtual void trick();
~Spider(){
  cout<<"des1"<<endl;
}
};
void Spider::act() {
  cout<<"construct1"<<endl;
  cout << "dash ";
  trick();
}
void Spider::trick() {
  cout<<"cons1"<<endl;
  cout << "web ";
}

class SpiderMan : public Spider {
public:
  static int count;
  SpiderMan(char seq);
  char _seq;
  void act();
  void trick();
  ~SpiderMan(){
    cout<<"des2"<<endl;
  }
};

SpiderMan::SpiderMan(char seq): _seq(seq) {
  count++;
  cout<<"con2"<<endl;
}
int SpiderMan:: count=0;
void SpiderMan::act() {
  cout<<"construct2"<<endl;
  Spider::act();
  cout << "jump ";
}
void SpiderMan::trick() {
  cout<<"cons2"<<endl;
  Spider::trick();
  cout << "fluid ";
}


struct Book
{
  string id;
  string title;
  double price;
};

int main() {
  Cat cat("Kitty", 5, "white");
  cat.pat();// 若Pet中的info()不是virtual　則程式直接呼叫Pet中的info()
  cout<<endl;
  
  Spider t;
  t.act();
  cout<<endl<<endl;
  
  SpiderMan x('A');
  x.act();
  cout<<endl<<endl;
  
  Spider *p = new SpiderMan('B'); //一個基底類別的物件指標，可以用來指向其衍生類別物件而不會發生錯誤
  p->act();                       //它只能存取基底類別中有定義的成員 但可以存取衍生類別中的虛擬函式
  cout<<endl;
  cout<<SpiderMan::count<<endl;
  delete p;  //不會執行~spiderMan()
  cout<<endl;
  
  SpiderMan* s = new SpiderMan('C');
  s->act(); // dash web fluid jump
  cout<<endl;
  cout<<SpiderMan::count<<" "<<(*s)._seq<<endl;
  delete s;
  cout<<endl;
  //衍生類別中重新定義虛擬函式時 如果再接下來的衍生類別仍想進行多型操作 則加上virtual
  //如果不打算進行多型操作，則可以不加上
  vector<Book> books;

  Book b1 = { "#aaa", "Hello ABC", 100.0 };
  Book b2 = {};
  b2.id = "#bbb";
  b2.title = "Stone Programming";
  b2.price = 250;

  books.push_back(b1);
  books.push_back(b2);

  for (Book &book : books) {
    cout << "Book " << book.id << " " << book.title;
    cout << " $" << book.price << endl;
  }

}