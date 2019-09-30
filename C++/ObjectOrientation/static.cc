#include <iostream>
using namespace std;

//常數 PI 是屬於 Area 類別的變數(所有人都使用到同一個靜態變數) 不是屬於物件的變數, 
//因為使用它們的時候前面要加上類別的名稱 Area::
//靜態函數是屬於類別的函數
class Area {
public:
  static const double PI;
  static double circle(double radius);
  static double square(double side);
  
};
const double Area::PI = 3.14;
double Area::circle(double radius) {
    return PI * radius * radius;
}
double Area::square(double side) {
    return side * side;
}
  
int main() {
  cout << Area::PI <<endl;
  cout << Area::circle(10) << endl;
  cout << Area::square(10) << endl;
  
  const double *p=&Area::PI;
  cout<<*p<<endl;
  
  double (*fptr)(double)=&Area::circle;
  cout<<fptr(10)<<endl;
}