#include <iostream>
#include <vector>
using namespace std;

const int OP_NODE = 0;
const int NUM_NODE = 1;
struct Node {
  int type; // 0 if op, 1 if num
  string op;
  int num;
  int parent=-1;
  vector<int> children;
};

vector<Node> nodes;

int eval(int node, vector<Node>& nodes){
  Node &n = nodes[node];
  if (n.type == NUM_NODE) return n.num;

  int left = eval(n.children[0], nodes);
  int right = eval(n.children[1], nodes);
  if (n.op == "+") {
    return left + right;
  } else {
    return left * right;
  }
}

void postorder(int node, vector<Node>& nodes){
  Node &n = nodes[node];
  for (int child:n.children){
    postorder(child, nodes);
  }
  cout<<node<<" ";
}

void posix(int node, vector<Node>& nodes, vector<Node> &vec){
  Node &n = nodes[node];
  for (int child:n.children){
    posix(child, nodes, vec);
  }
  vec.push_back(n);
}

void preorder(int node, vector<Node>& nodes){
  Node &n = nodes[node];
  cout<<node<<" ";
  for (int child:n.children){
    preorder(child, nodes);
  }
}

void inorder(int node, vector<Node>& nodes){
  Node &n = nodes[node];
  if(n.children.size()>0){
    inorder(n.children[0],nodes);
    cout<<node<<" ";
    inorder(n.children[1],nodes);
  }
  else{
    cout<<node<<" ";
  }

}
int main() {
  int n;
  cin >> n;
  for(int i=0;i<n;i++){
    Node n;
    string type;
    cin >> type;
    if (type == "op") {
      n.type = OP_NODE;
      cin >> n.op;
    } else {
      n.type = NUM_NODE;
      cin >> n.num;
    }
    int nchild;
    cin >> nchild;
    for(int j=0;j<nchild;j++){
      int k;
      cin>>k;
      (n.children).push_back(k);
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
  cout<<Root<<endl;
  cout << eval(Root, nodes) << endl;
  postorder(Root,nodes);
  cout<<endl;
  inorder(Root,nodes);
  cout<<endl;
  preorder(Root, nodes);
  cout<<endl;

  vector<Node> vec;
  posix(Root, nodes, vec);
  for (Node &n : vec) {
    if (n.type == OP_NODE) {
      cout << n.op << " ";
    } else {
      cout << n.num << " ";
    }
  }
  //cout << eval_posix(vec) << endl;
}

//input
//5
//op * 2 3 1
//op + 2 2 4
//n 2 0
//n 1 0
//n 3 0