#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> Id;
vector<string> Title;
vector<double> Price;
vector<int> Pages;
vector<int>Idxes;

bool byId(const int a, const int b) { return Id[a]<Id[b]; };

int bSearch(const vector<int>& idxes,string id,int start, int end){
  if (end>start){
    int t= start+((end-start)/2);
    int idx=idxes[t];
    if (id == Id[idx]) return t;
    else if (id >Id[idx] ){
      return bSearch(idxes,id, t + 1, end);
    }
    else{
      return bSearch(idxes,id, start, t);
    }
  }
  return -1;
}

int main(){
  int n;
  cin>>n;
  for(int i=0;i<n;i++){
    string id;
    string title;
    double price;
    int pages;
    cin>>id>>title>>price>>pages;
    Id.push_back(id);
    Title.push_back(title);
    Price.push_back(price);
    Pages.push_back(pages);
    Idxes.push_back(i);
  }
  sort(Idxes.begin(), Idxes.end(), byId);

  string ID;
  while(cin>>ID){
    int pos=bSearch(Idxes,ID,0,n);
    if(pos==-1){
      cout<<"not found"<<endl;
    }
    else{
      int idx = Idxes[pos];
      cout << Id[idx] << " " << Title[idx]
      << " " << Price[idx] <<" "<<Pages[idx] <<endl;
    }
  }
}
