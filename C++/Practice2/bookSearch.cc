#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Book
{
  string id;
  string title;
  double price;
  int pages;
};
bool byId(const Book &a, const Book &b) { return a.id < b.id; };

int bSearch(const vector<Book>& arr,string id,int start, int end){
  if (end>start){
    int t= start+((end-start)/2);
    if (id == arr[t].id) return t;
    else if (id > arr[t].id){
      return bSearch(arr,id, t + 1, end);
    }
    else{
      return bSearch(arr,id, start, t);
    }
  }
  return -1;
}
int search(const vector<Book>& arr,string id){
  Book b;
  b.id = id;
  auto it = lower_bound(arr.begin(), arr.end(), b, byId);// lower_bound is an iterator 
                                                         // 它回傳第一個小於等於b.id的位址
                                                         // 若找不到則回傳結束位址
  if (it == arr.end() or (*it).id != id) {  //也可用(it->id)            // auto 用來自動初始複雜型態
    return -1;
  } else {
    return it - arr.begin();  //相減後的整數值恰為it所指到元素的陣列位置
  }
}
int main(){
  int n;
  cin>>n;
  vector<Book> books;
  for(int i=0;i<n;i++){
    Book b={};
    cin>>b.id;
    cin>>b.title;
    cin>>b.price;
    cin>>b.pages;
    books.push_back(b);
  }
  sort(books.begin(), books.end(), byId);

  string ID;
  while(cin>>ID){
    //int pos=bSearch(books,ID,0,books.size());
    int pos=search(books,ID);

    if(pos==-1){
      cout<<"not found"<<endl;
    }
    else{
      cout << books[pos].id << " " << books[pos].title
      << " " << books[pos].price <<" "<< books[pos].pages<<endl;
    }
  }
}
