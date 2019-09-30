#include <iostream>
#include <vector>
using namespace std;

struct Node {
  int parent=-1;
  int h;
  vector<int> children;
};
//vector<Node> nodes(100001) ;
vector<Node> nodes;

int height(int node, vector<Node>& nodes){
  Node &n=nodes[node];
  if((n.children).size()==0){
    n.h=0;
    return 0;
  }
  int max=0;
  for(int child: n.children){
    int h=height(child,nodes);
    if(h>max){
      max=h;
    }
  }
  n.h=max+1;
  return max+1;
}
long long int sum(vector<Node>& nodes){
  long long int sum=0;
  for(int i=0;i<nodes.size();i++){
    sum+=nodes[i].h;
  }
  return sum;
}
int main() {
  int n;
  cin >> n;


  for(int i=0;i<n;i++){
    Node n;
    int num;
    cin>>num;
    for(int j=0;j<num;j++){
      int k;
      cin>>k;
      (n.children).push_back(k-1);
    }
    nodes.push_back(n);
  }
  for(int i=0;i<nodes.size();i++){
    for (int child : nodes[i].children) {
      nodes[child].parent=i;
    }
  }


  int Root=-1;
  for(int i=0;i<n;i++){
    if(nodes[i].parent<0){
      Root=i;
      break;
    }
  }
  cout<<Root+1<<endl;
  height(Root,nodes);
  cout<<sum(nodes)<<endl;
}