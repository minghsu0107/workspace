#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Test
{
  int seq;
  int lit;
  int eng;
  int math;
  int phy;
  int chem;
  int total;
};

bool compare1(const Test* a, const Test* b){
    return a->total > b->total;
}

bool compare2(const Test* a, const Test* b){
    return a->math > b->math;
}

void exam(vector<Test*> ptr){
   sort(ptr.begin(), ptr.end(), compare1);
   int i=0;
   int pos=0;
   bool count=false;
   int len=0;
   for(int i=0;i<ptr.size()-1;i++){
      if(ptr[i]->total==ptr[i+1]->total){
          if(count==false){
              pos=i;
              len+=2;
              count=true;
          }
          else{
              len++;
          }
      }
      else if(ptr[i]->total!=ptr[i+1]->total && count==true){
          sort(&ptr[pos],&ptr[pos+len],compare2);
          count=false;
          len=0;
      }
   }
   if(count==true){
       sort(&ptr[pos],&ptr[pos+len],compare2);
   }
   for(int i=0;i<ptr.size();i++){
       cout<<ptr[i]->seq<<endl;
   }
}

int main(){
    int n;
    cin>>n;
    vector<Test> tests;
    vector<Test*> ptr;
    for(int i=0;i<n;i++){
     Test test;
     cin>>test.seq;
     
     int sum=0;
     cin>>test.lit;
     sum+=test.lit;
     
     cin>>test.eng;
     sum+=test.eng;
     
     cin>>test.math;
     sum+=test.math;
     
     cin>>test.phy;
     sum+=test.phy;
     
     cin>>test.chem;
     sum+=test.chem;
     
     test.total=sum;
     tests.push_back(test);
    }
    for(int i=0;i<n;i++){
      ptr.push_back(&tests[i]);
    }
    exam(ptr);
}