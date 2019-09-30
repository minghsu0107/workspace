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
bool byId(const Book* a, const Book* b) { return a->id < b->id; };

int bSearch(const vector<Book*>& arr,string id,int start, int end){
  if (end>start){
    int t= start+((end-start)/2);
    if (id == arr[t]->id) return t;
    else if (id > arr[t]->id){
      return bSearch(arr,id, t + 1, end);
    }
    else{
      return bSearch(arr,id, start, t);
    }
  }
  return -1;
}
int main(){
  int n;
  cin>>n;
  vector<Book> books;
  vector<Book*> ptr;
  for(int i=0;i<n;i++){
    Book b = {};
    cin>>b.id;
    cin>>b.title;
    cin>>b.price;
    cin>>b.pages;
    books.push_back(b);
    //ptr.push_back(&books[i]);
  }
  for(int i=0;i<n;i++){
    ptr.push_back(&books[i]);
  }
  sort(ptr.begin(), ptr.end(), byId);
  string ID;
  while(cin>>ID){
    int pos=bSearch(ptr,ID,0,books.size());
    if(pos==-1){
      cout<<"not found"<<endl;
    }
    else{
      cout << ptr[pos]->id << " " << ptr[pos]->title
      << " " << ptr[pos]->price <<" "<< ptr[pos]->pages<<endl;
    }
  }
}
