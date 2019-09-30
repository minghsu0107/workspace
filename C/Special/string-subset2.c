#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct Node {
  char s[2505];
  struct Node *left, *right;
} Node;
 
Node* Insert(Node *root, char *s) {
  if (root == NULL) {
    root = malloc(sizeof(Node));
    strcpy(root->s, s);
    root->left = root->right = NULL;
    return root;
  }
  int cmp = strcmp(s, root->s);
  if (cmp < 0) root->left = Insert(root->left, s); 
  else if (cmp > 0) root->right = Insert(root->right, s);
  return root;
}
// in-order: print the smallest first, largest last
void Print(Node *root) {
  if (root == NULL) return;
  Print(root->left);
  printf("%s\n", root->s);
  Print(root->right);
}
 
int main() {
  char s[2505];
  scanf("%s", s);
  int len = strlen(s);
  Node *root = NULL;
  for (int i = 0; i < len; ++i) {
      for (int j = i; j < len; ++j) {
          char buf[2505] = {0};
          int idx = 0;
          for (int k = i; k <= j; ++k)
              buf[idx++] = s[k];
          root = Insert(root, buf);
      }
  }
  Print(root);
}

// construct the subset as a binary tree 