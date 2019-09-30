#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;
int main(){
  double x=13.111;
  cout<<fixed<<x<<endl;
  cout<<setprecision(2)<<x<<endl;

  float y=31.012;
  cout<<y<<endl;
  cout<<x<<endl;
  cout<<setprecision(4)<<x<<endl;
  cout<<setprecision(5)<<y<<endl;

  cout.unsetf(ios::fixed);//close fixed
  cout<<y<<endl;
  printf("%e\n",y);
  cout<<scientific<<y<<endl;
  cout<<setprecision(2)<<y<<endl;
  cout<<setprecision(3)<<y<<endl;
}