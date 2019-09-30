#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
using namespace std;
class HuffmanCodes {
private:
   struct Node {
      char data;
      size_t freq;
      Node *left;
      Node *right;
      Node(char data, size_t freq) : data(data), freq(freq), 
                                     left(nullptr), right(nullptr) {}
      ~Node() {
        delete left;
        delete right;
      }
   };
   struct compare {
      bool operator()(Node* l, Node* r) {
          return (l->freq > r->freq);
      }
   };
void printCode(Node* root, std::string str) {
   if (root == nullptr) return;
   if (root->data != '$') {
      cout << root->data << " : " << str << "\n";
   }
   printCode(root->left, str + "0");
   printCode(root->right, str + "1");
}
public:
  HuffmanCodes() {};
  ~HuffmanCodes() {}
  void GenerateCode(std::vector<char>& data, std::vector<size_t>& freq) {
     Node *left;
     Node *right;
     std::priority_queue<Node*, std::vector<Node*>, compare > minHeap;

     for (size_t i = 0; i < data.size(); ++i) {
         minHeap.push(new Node(data[i], freq[i]));
     }

      while (minHeap.size() != 1) {
            left = minHeap.top();
            minHeap.pop();

            right = minHeap.top();
            minHeap.pop();

            Node* top = new Node('$', left->freq + right->freq);
            top->left  = left;
            top->right = right;
            minHeap.push(top);
      }
      printCode(minHeap.top(), "");
  }
};
int main() {
  HuffmanCodes set1;
  std::vector<char> data({'d', 'e', 'b', 'c', 'a', 'f'});
  std::vector<size_t> freq({16, 9, 13, 12, 45, 5});
  set1.GenerateCode(data, freq);
  return 0;
}
/* 

          100
         /   \
        /    55
       /    /  \ 
      /    /    \
     /    /      \
    /    /       30       
   /    /       /  \       
  /    25      14   \     
 /    /  \    /  \   \   
a    c    b   f   e   d  
45   12   13  5   9   16

sum of frequency: left node < right node
none of the codes will be a prefix of another one

*/