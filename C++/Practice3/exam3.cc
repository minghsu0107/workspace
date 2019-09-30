#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<int>Seq;
vector<int>Math;
vector<int>Total;

struct compare{
    bool operator() (int a, int b){
      if(Total[a-1]==Total[b-1]){
         return Math[a-1] < Math[b-1];
      }
      return Total[a-1]<Total[b-1];
    }
};
bool cmp(int a, int b){
    if(Total[a-1]==Total[b-1]){
         return Math[a-1] > Math[b-1];
      }
    return Total[a-1] > Total[b-1];
}


void exam(vector<int> &Seq){
   priority_queue<int, vector<int>, compare> q;
   for(int i=0;i<Seq.size();i++){
       q.push(Seq[i]);
   }
   for(int i=0;i<Seq.size();i++){
       cout<<q.top()<<endl;
       q.pop();
   }
}
void exam2(vector<int> &Seq){
    sort(Seq.begin(),Seq.end(),cmp);
    for(int i=0;i<Seq.size();i++){
        cout<<Seq[i]<<endl;
    }
}
int main(){
    int n;
    cin>>n;
    
    for(int i=0;i<n;i++){
      int seq,lit,eng,math,phy,chem;
      cin>>seq>>lit>>eng>>math>>phy>>chem;
      int total=lit+eng+math+phy+chem;
      Seq.push_back(seq);
      Math.push_back(math);
      Total.push_back(total);
    }
    exam(Seq);
}