#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
struct old_same : std::binary_function<int, int, bool>
{
    bool operator()(int a, int b) const { return a == b; }
    // "const" at the rightmost: 使成員函式只能讀取成員，不能修改資料成員
};
 
struct new_same
{
    bool operator()(int a, int b) const { return a == b; }
};
 
bool same_fn(int a, int b)
{
    return a == b;
}
 
// size_t == unsigned int
/* uint8_t  : unsigned char      (hhu)
   uint16_t : unsigned short     (hu)
   uint32_t : unsigned int       (u)
   uint64_t : unsigned long long (ull)
*/ 
int main()
{
    std::vector<int> v1{0, 1, 2};
    std::vector<int> v2{2, 1, 0};
    std::vector<bool> v3(v1.size());
 
    std::cout << "negating a binary_function:\n";
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
                   std::not2(old_same()));
 
    std::cout << std::boolalpha;
    for (std::size_t i = 0; i < v1.size(); ++i)
        std::cout << v1[i] << ' ' << v2[i] << ' ' << v3[i] << '\n';
 
    std::cout << "negating a standard functor:\n";
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
                   std::not2(std::equal_to<int>()));
 
    for (std::size_t i = 0; i < v1.size(); ++i)
        std::cout << v1[i] << ' ' << v2[i] << ' ' << v3[i] << '\n';
 
    std::cout << "negating a std::function:\n";
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
                   std::not2(std::function<bool(int,int)>(new_same())));
 
    for (std::size_t i = 0; i < v1.size(); ++i)
        std::cout << v1[i] << ' ' << v2[i] << ' ' << v3[i] << '\n';
 
    std::cout << "negating a std::reference_wrapper:\n";
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
                   std::not2(std::ref(same_fn)));
 
    for (std::size_t i = 0; i < v1.size(); ++i)
        std::cout << v1[i] << ' ' << v2[i] << ' ' << v3[i] << '\n';
    
    std::cout << "lambda expression:\n";
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
                   [](int a, int b){ return a != b; });
    for (std::size_t i = 0; i < v1.size(); ++i)
        std::cout << v1[i] << ' ' << v2[i] << ' ' << v3[i] << '\n';    
}