#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Complex{
public:
  Complex(double a, double b){
    this->_real=a;
    (*this)._img=b;
  }
  Complex add(const Complex &x){//"&" 傳參考 不複製省記憶體 可更改變數
    double r = _real + x._real;//"const"修飾後只讓物件提供資訊 不改變物件
    double i = _img + x._img;
    return Complex(r, i);
  }
  Complex operator+(Complex &x) {
    double r = _real + x._real;
    double i = _img + x._img;
    return Complex(r, i);
  }
  
  Complex minus(Complex &x){
    double r = _real - x._real;
    double i = _img - x._img;
    return Complex(r, i);
  }
  Complex times(Complex &x){
    double r = (_real*x._real) - (_img*x._img);
    double i = (_img*x._real) + (_real*x._img);
    return Complex(r, i);
  }
  string label(){
    if (_img > 0){
      return(to_string(_real)+ "+"+ to_string((int)(_img)) + "i");
    }
    else if (_img == 0){
      return(to_string(_real));
    }
    else{
      return(to_string(_real) + ""+ to_string((int)_img) +"i");
    }
  }
  Complex& operator=(const Complex&); // reload the "=" operator 
                                      // 回傳值為參考(Complex&)
private:
 double _real;
 double _img;
};

Complex& Complex::operator=(const Complex &x){
    double *r = new double(x._real);
    double *i = new double(x._img);
    _real=*r;
    _img=*i;
    delete r;
    delete i;
    return *this;
}
 
int main() {
  
  Complex num(2,3);
  Complex num2(1,2);
  Complex &q=(num=num2); //指定q為num1的參考 (num1=num2)傳回num1的參考值
  cout<<q.label()<<" "<<num.label()<<" "<<num2.label()<<endl;
  q=q+num2;
  cout<<q.label()<<" "<<num.label()<<" "<<num2.label()<<endl;
  num=num+num2;
  cout<<q.label()<<" "<<num.label()<<" "<<num2.label()<<endl; 
  double x = 1, y = 2;
  Complex c(x, y);
  Complex d(3, -4);
  

  cout<<c.label()<<endl; // (1 + 2i)

  Complex e = c.add(d);
  //Complex e = c + d;
  cout<<e.label()<<endl; // (4 - 2i)
  cout<<c.label()<<endl; // (1 + 2i)
  cout<<d.label()<<endl; // (3 - 4i)

  Complex f = c.times(d);
  //Complex f = c * d;
  cout<<f.label()<<endl; // (11 + 2i)

  d = d.times(d);
  cout<<d.label()<<endl; 
}
