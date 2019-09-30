#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

const int OP_NODE = 0;
const int NUM_NODE = 1;
const int VAR_NODE = 2;
struct Node {
  int type; // 0 if op, 1 if num
  char op;
  int num;
  char var;
  int left = -1;
  int right = -1;
};

bool isexpr(string &s, int &pos){
  if (s[pos] == '(') {
    pos++;

    bool left = isexpr(s, pos);
    if ( !left ) return false;

    if (s[pos] != '+' and s[pos]!='-' and s[pos]!='*' and s[pos]!='/' ) return false;
    //if (!(ch == '+' or ch == '-' or ch == '*' or ch == '/')) return false;
    pos++;

    bool right = isexpr(s, pos);
    if (!right) return false;

    if (s[pos] != ')') return false;
    pos++;

    return true;
  } else if (s[pos] >= '0' and s[pos] <= '9') {
    while (s[pos] >= '0' and s[pos] <= '9'){
      pos++;
    }
    return true;
  }
  else if (s[pos] >= 'A' and s[pos] <= 'Z') {
    pos++;
    return true;
  }

  return false;
}

int parse(string s, vector<Node> &nodes,int &pos){
  if (s[pos] == '(') {
    pos++;

    Node n;
    n.type=OP_NODE;
    nodes.push_back(n);
    int root = nodes.size()-1;

    int left = parse(s, nodes,pos);
    if (left<0 ) return -1;
    nodes[root].left = left;

    if (s[pos] != '+' and s[pos]!='-' and s[pos]!='*' and s[pos]=='/' ) return -1;
    nodes[root].op = s[pos];
    pos++;


    int right = parse(s, nodes,pos) ;
    if (right<0) return -1;
    nodes[root].right = right;

    if (s[pos] != ')') return -1;
    pos++;

    return root;
  } else if (s[pos] >= '0' and s[pos] <= '9') {
    int num=0;
    while (s[pos] >= '0' and s[pos] <= '9'){
      num*=10;
      num+=s[pos]-'0';
      pos++;
    }
    Node n;
    n.type=NUM_NODE;
    n.num=num;
    nodes.push_back(n);
    return nodes.size()-1;
  }
  else if (s[pos] >= 'A' and s[pos] <= 'Z') {
    Node n;
    n.type=VAR_NODE;
    n.var=s[pos];
    pos++;
    nodes.push_back(n);
    return nodes.size()-1;
  }

  return -1;
}
int parse2(string s, vector<Node> &nodes,int &pos){
  if (s[pos] == '(') {
    pos++;

    int left = parse2(s, nodes,pos);
    if (left<0 ) return -1;

    if (s[pos] != '+' and s[pos]!='-' and s[pos]!='*' and s[pos]!='/' ) return -1;
    char op=s[pos];
    pos++;


    int right = parse2(s, nodes,pos) ;
    if (right<0) return -1;

    if (s[pos] != ')') return -1;
    pos++;

    Node n;
    n.type=OP_NODE;
    n.op=op;
    n.left=left;
    n.right=right;
    nodes.push_back(n);
    return nodes.size()-1;

  } else if (s[pos] >= '0' and s[pos] <= '9') {
    int num=0;
    while (s[pos] >= '0' and s[pos] <= '9'){
      num*=10;
      num+=s[pos]-'0';
      pos++;
    }
    Node n;
    n.type=NUM_NODE;
    n.num=num;
    nodes.push_back(n);
    return nodes.size()-1;
  }
  else if (s[pos] >= 'A' and s[pos] <= 'Z') {
    Node n;
    n.type=VAR_NODE;
    n.var=s[pos];
    pos++;
    nodes.push_back(n);
    return nodes.size()-1;
  }

  return -1;
}

void pr(vector<Node> &nodes) {
  cout << "TREE" << endl;
  for (int i=0; i<nodes.size(); i++) {
    cout << "[" << i << "]" << nodes[i].type
    << " lhs:" << nodes[i].left
    << " rhs: " << nodes[i].right << endl;
  }
  cout << "-----" << endl;
}


int eval(vector<Node> &nodes, int root, map<char,int> &vars) {
   Node &n = nodes[root];
   if(n.type==NUM_NODE){
     return n.num;
   }
   else if (n.type==VAR_NODE){
     return vars[n.var];
   }
   else if(n.type==OP_NODE){
      int left=eval(nodes,n.left,vars);
      int right=eval(nodes,n.right,vars);
      if (n.op=='+') return left+right;
      else if (n.op=='-') return left-right;
      else if (n.op=='*') return left*right;
      else return left/right;
   }
}
int main() {
  string s;
  while(cin >> s){

    vector<Node> nodes;
    int pos=0;
    bool size = isexpr(s, pos);
    if (!size ) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
    pos = 0;
    int k=parse(s,nodes,pos);
    cout<<k<<endl;
    //pr(nodes);

    if (k >= 0) {
      map<char, int> vars;
      vars['A'] = 11;
      vars['B'] = 2;
      cout << eval(nodes, k, vars) << endl;
    }
  }
}