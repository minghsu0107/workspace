#include <iostream>
#include <memory>
#include <string>
using namespace std;

//auto_ptr協助動態管理new建立的物件
//它可以指向一個以new建立的物件 當auto_ptr的生命週期結束後 所指向的物件之資源也會被釋放
//auto_ptr的資源維護動作以inline的方式完成 (在編譯時會被擴展開來) 所以使用auto_ptr並不會犧牲效率
//auto_ptr不能用來管理動態配置的陣列 結果將不可預期

int main(){
    auto_ptr<int> iPtr (new int(100));
    auto_ptr<string> sPtr (new string("caterpillar")); 
      
    cout << *iPtr << endl; // 顯示100
    
    if(sPtr->empty()) {
       cout << "字串為空" << endl;
    }
    else cout<<*sPtr<<endl;
    
    
    //判斷它是否有指向物件: 使用get()函式傳回所指向物件的位址(不能直接呼叫iPtr2) 如果傳回0 表示不指向任何物件
    //可以使用reset() 讓它指向一個物件
    auto_ptr<int> iPtr2;
    if(iPtr2.get() == 0) {
        iPtr2.reset(new int(200));
    }
    cout<<*iPtr2<<endl;
    
    
    auto_ptr<int> ptr1(new int(19));
    //auto_ptr可以使用另一個auto_ptr來建立，這會造成所有權的轉移
    //當使用ptr1來建立ptr2時 ptr1不再對所指向物件的資源釋放負責 職責交給了ptr2
    //ptr2所指向的物件會先被delete 然後ptr1的屬性會複製至ptr2
    auto_ptr<int> ptr2(ptr1);
    cout<<*ptr2<<endl;
}