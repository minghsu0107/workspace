
// C++ program to concatenate two strings using 
// rope data structure. 
#include <bits/stdc++.h> 
#include <string.h>
using namespace std; 
  
// Maximum no. of characters to be put in leaf nodes 
const int LEAF_LEN = 2; 
  
// Rope structure 
class Rope 
{ 
public: 
    Rope *left, *right, *parent; 
    char *str; 
    int lCount; 
}; 
  
// Function that creates a Rope structure. 
// node --> Reference to pointer of current root node 
//   l  --> Left index of current substring (initially 0) 
//   r  --> Right index of current substring (initially n-1) 
//   par --> Parent of current node (Initially NULL) 
void createRopeStructure(Rope *&node, Rope *par, 
                         char a[], int l, int r) 
{ 
    Rope *tmp = new Rope(); 
    tmp->left = tmp->right = NULL; 
   
    // We put half nodes in left subtree 
    tmp->parent = par; 
   
    // If string length is more 
    if ((r-l+1) > LEAF_LEN) 
    { 
        tmp->str = NULL; 
        tmp->lCount = (r-l+1)/2; 
        node = tmp; 
        int m = (l + r)/2; 
        createRopeStructure(node->left, node, a, l, m); 
        createRopeStructure(node->right, node, a, m+1, r); 
    } 
    else
    { 
        node = tmp; 
        tmp->lCount = (r-l+1); 
        int j = 0; 
        tmp->str = new char[LEAF_LEN]; 
        for (int i=l; i<=r; i++) 
            tmp->str[j++] = a[i]; 
    } 
} 
  
// Function that prints the string (leaf nodes) 
void printstring(Rope *r) 
{ 
    if (r==NULL) 
        return; 
    printstring(r->left); 
    if (r->left==NULL && r->right==NULL) 
        cout << r->str; 
    printstring(r->right); 
} 
char* idx(Rope *root, int i) {
    if (i >= root->lCount) return idx(root->right, i - root->lCount);
    if (root->left != NULL) return idx(root->left, i);
    return root->str;
} 
// Function that efficiently concatenates two strings 
// with roots root1 and root2 respectively. n1 is size of 
// string represented by root1. 
// root3 is going to store root of concatenated Rope. 
void concatenate(Rope *&root3, Rope *root1, Rope *root2, int n1) 
{ 
    // Create a new Rope node, and make root1  
    // and root2 as children of tmp. 
    Rope *tmp = new Rope(); 
    tmp->parent = NULL; 
    tmp->left = root1; 
    tmp->right = root2; 
    root1->parent = root2->parent = tmp; 
    tmp->lCount = n1; 
  
    // Make string of tmp empty and update  
    // reference r 
    tmp->str = NULL; 
    root3 = tmp; 
} 
  
// Driver code 
int main() 
{ 
    // Create a Rope tree for first string 
    Rope *root1 = NULL; 
    char a[] =  "Hi This is geeksforgeeks. "; 
    int n1 = sizeof(a)/sizeof(a[0]); 
    createRopeStructure(root1, NULL, a, 0, n1-1); 
  
    // Create a Rope tree for second string 
    Rope *root2 = NULL; 
    char b[] =  "You are welcome here."; 
    int n2 = sizeof(b)/sizeof(b[0]); 
    createRopeStructure(root2, NULL, b, 0, n2-1); 
  
    // Concatenate the two strings in root3. 
    Rope *root3 = NULL; 
    concatenate(root3, root1, root2, n1); 
  
    // Print the new concatenated string 
    printstring(root3); 
    cout << endl; 
    cout << idx(root3, 0) << endl;
    return 0; 
} 
