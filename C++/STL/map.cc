#include <iostream>
#include <map>
#include <string>
using namespace std;

// using R-B tree

int main(){
  std::map<string,int> cnts;

  cnts["def"]=30;
  cnts["abc"]=10;
  cout << "abc: " << cnts["abc"] << endl; // O(log size)
  cout << "def: " << cnts["def"] << endl;
  cout << "xxx: " << cnts["xxx"] << endl;
  
  int cnt = cnts.count("yyy"); //if map contains "yyy", then return 1; else then return 0
  cout << "yyy: " << (cnt > 0 ? cnts["yyy"] : 0) << endl;
  
  //map 的 key 值會照順序排列，因此用 for loop 列舉內容時會照此順序
  for(auto& pair : cnts) {
    cout << "[" << pair.first << "] " << pair.second << endl;
  }
  
    map<char, int> mymap;

    // 插入單個值
    mymap.insert(pair<char, int>('a', 100));
    mymap.insert(std::pair<char, int>('z', 200));
    
    //返回插入位置以及是否插入成功 插入位置已經存在值時，插入失敗
    pair<map<char, int>::iterator, bool> ret;
    ret = mymap.insert(pair<char, int>('z', 500));
    if (ret.second == false) {
        cout << "element 'z' already existed"
        << " with a value of " << (ret.first)->second << endl;
    }
    
    //指定位置插入 不同位置插入效率是不一樣的，因為涉及到重排
    map<char, int>::iterator it = mymap.begin();
    mymap.insert(it, pair<char, int>('b', 300));  //效率更高
    mymap.insert(it, pair<char, int>('c', 400));  //效率非最高
    
    cout << "mymap: "<< endl;
    for(auto& pair : mymap) {
      cout << "[" << pair.first << "] " << pair.second << endl;
    }
    cout<<endl;
    
    //範圍多值插入[l, u)
    map<char, int> anothermap;
    anothermap.insert(mymap.begin(), mymap.find('c'));
    
    //列表形式插入
    anothermap.insert({ { 'd', 100 }, {'e', 200},{'f',700 } });
    cout<<anothermap.empty()<<endl;
    cout<<anothermap.size()<<endl;

    cout << "anothermap: "<< endl;
    for(auto& pair : anothermap) {
      cout << "[" << pair.first << "] " << pair.second << endl;
    }

    //Exchanges the content of the container by the content of x, 
    //which is another map of the same type
    anothermap.swap(mymap);
    anothermap.clear();
    //用迭代器範圍刪除 : 把整個map清空 anothermap.erase(anothermap.begin(), anothermap.end());
    cout<<anothermap.size()<<endl;
    cout<<mymap.size()<<endl;
    
    map<char,int> mymap2;
    map<char,int>::key_compare compFunc = mymap2.key_comp();
    
    mymap2['a']=100;
    mymap2['b']=200;
    cout<<compFunc('a', 'b')<<endl;  // a排在b前面 因此返回true
    
    std::map<char,int> mymap3;
    std::map<char,int>::iterator is;
    
    mymap3['a']=50;
    mymap3['b']=100;
    mymap3['c']=150;
    mymap3['d']=200;
    
    //返回資料pair所在位置，如果沒有，返回 iter 與 end() 函數的返回值相同
    is = mymap3.find('b');
    if (is != mymap3.end()){
        cout<<is->first<<" "<<(*is).second<<endl;  //iterator為pair物件的指標
        mymap3.erase (is);       // b被成功删除  to delete, we can also do: mymap3.erase('b') 
                                 //如果刪除了會返回1，否則返回0
    }
    for(auto& pair : mymap3) {
      cout << "[" << pair.first << "] " << pair.second << endl;
    }
    
    map<string, string> mapStudent;
    map<string, string>::iterator iter;
    map<string, string>::reverse_iterator rIter;
    
    mapStudent.insert(pair<string, string>("r000", "student_zero"));
    mapStudent["r123"] = "student_first";
    mapStudent["r456"] = "student_second";
    
    for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++){
                cout<<iter->first<<" "<<iter->second<<endl;
    }
    cout<<endl;
    for(rIter = mapStudent.rbegin(); rIter != mapStudent.rend(); rIter++){
                cout<<rIter->first<<" "<<rIter->second<<endl;
    }
    map<string, string>::iterator l = mapStudent.lower_bound("r123");
    map<string, string>::iterator u = mapStudent.upper_bound("r123");
    for (auto i = l; i != u; i++) {
       cout<< i->first << " " << i->second <<endl;
    }
    // delete [begin, end)
    mapStudent.erase(mapStudent.begin(), mapStudent.end());
    cout << (mapStudent.empty() == 1 ? "empty" : "not empty") << endl;
}
