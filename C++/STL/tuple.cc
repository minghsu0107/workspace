#include <iostream>
#include <tuple>
#include <string>
#include <vector>

using namespace std;
using return_type = tuple<int, string>; // define <int, string> as return_type

return_type test(void) {
  return make_tuple(1, "str");  // 返回一个元组
}

int main()
{
  std::tuple<int, double, const char*> t(1, 84.1, "YOO");

  std::cout << std::get<0>(t) << ", "
            << std::get<1>(t) << ", "
            << std::get<2>(t) << '\n';

  std::vector<double> v{1.1, 2.2, 3.3, 689.2, 9.2};
  auto t1 = std::make_tuple(3, std::string("AABBCCDD"), v);

  auto integer  = std::get<0>(t1);
  std::string s = std::get<1>(t1);
  auto myvector = std::get<2>(t1);

  std::cout << integer << '\n'
            << s << '\n'
            << myvector.size() << '\n';
  
  // change the value in tuple
  std::string &s1 = std::get<1>(t1);
  auto &myvector1 = std::get<2>(t1);

  std::get<1>(t1) += "xxx";
  s1              += "yyy";
  std::get<2>(t1).push_back(666);

  std::cout << s1 << '\n'
            << myvector1.size() << '\n';
  
  // unpacked tuple
  auto t2 = std::make_tuple(1, "GMA20", "PoeTek");
  const char* s2;
  int i;
  std::tie(i, std::ignore, s2) = t2;
  // after unpacked, the values in t2 are assigned to variable in tie
  std::cout << i << ", " << s2 << '\n';
  // output: 1, PoeTek

  auto res_test = test();
  cout << std::get<0>(res_test) << endl;

  std::tuple<int, float> test1(7, 1.5);
  std::tuple<string, bool> test2("str", true);
  auto test3 = std::tuple_cat(test1, test2); // concatenate two tuples
  
  // get the type of the 0_th element in test3; res1 is an integer (int)
  tuple_element<0, decltype(test3)>::type res1 = get<0>(test3);
  cout << res1 << endl;
  // get the number of elements in test3
  auto num = std::tuple_size<decltype(test3)>::value;
  cout << num << endl;
}
/*
std::tie 的回傳值是一個 tuple of reference
也就是說你丟了什麼值進去 std::tie 他就作出一個 tuple
然後裡面的值是你傳進去所有值的 lvalue reference
*/