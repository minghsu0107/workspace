#include <iostream> 
#include "Point.h"
using namespace std; 
using d2d::Point2D; // using namespace d2d;

int main() { 
    Point2D p1(10, 10); // or d2d::Point2D p1(10, 10); 

    cout << "(x , y) : (" 
         << p1.x() << ", " 
         << p1.y() << ")"
         << endl; 
 
    return 0; 
} 
/*
可以使用"using"關鍵字指明所要使用的名稱空間或其下的成員

還可以定義一種未命名的名稱空間，這可以建立唯一的識別字
只允許您在同一個檔案中使用這些識別字

namespace {
	int i j, k;
}

如果在檔案中如上宣告，則i, j, k等都只限於該檔案中使用
在其它檔案中就無法使用這些識別字
*/
