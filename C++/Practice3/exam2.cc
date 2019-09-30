#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Test
{
  int seq;
  int math;
  int total;
};

bool compare1(const Test &a, const Test &b){
    return a.total > b.total;
}

bool compare2(const Test &a, const Test &b){
    return a.math > b.math;
}
bool compare(const Test &a, const Test &b){
    if(a.total==b.total){
         return a.math > b.math;
      }
    return a.total > b.total;
}

void exam(vector<Test> &tests){
   sort(tests.begin(), tests.end(), compare1);
   int i=0;
   int pos=0;
   bool count=false;
   int len=0;
   for(int i=0;i<tests.size()-1;i++){
      if(tests[i].total==tests[i+1].total){
          if(count==false){
              pos=i;
              len+=2;
              count=true;
          }
          else{
              len++;
          }
      }
      else if(tests[i].total!=tests[i+1].total && count==true){
          sort(&tests[pos],&tests[pos+len],compare2);
          count=false;
          len=0;
      }
   }
   if(count==true){
      sort(&tests[pos],&tests[pos+len],compare2); 
   }
   for(int i=0;i<tests.size();i++){
       cout<<tests[i].seq<<endl;
   }
}

void exam2(vector<Test> &arr){
    int flag = 1; 
    for(int i = 0; i < arr.size()-1 && flag == 1; i++) { 
        flag = 0; 
        for(int j = 0; j < arr.size()-i-1; j++) { 
            if(compare(arr[j+1], arr[j])) { 
                Test t=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=t;
                flag = 1; 
            } 
        } 
    }
    for(int i=0;i<arr.size();i++){
        cout<<arr[i].seq<<endl;
    }
}
void exam3(vector<Test> &arr){
    sort(arr.begin(),arr.end(),compare);
    for(int i=0;i<arr.size();i++){
        cout<<arr[i].seq<<endl;
    }
}
int main(){
    int n;
    cin>>n;
    vector<Test> tests;

    for(int i=0;i<n;i++){
     
     int seq,lit,eng,math,phy,chem;
     cin>>seq>>lit>>eng>>math>>phy>>chem;
     int total=lit+eng+math+phy+chem;
     Test test;
     test.seq=seq;
     test.math=math;
     test.total=total;
     tests.push_back(test);
    }
    exam3(tests);
}