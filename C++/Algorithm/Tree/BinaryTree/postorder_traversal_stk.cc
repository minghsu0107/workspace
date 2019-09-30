// C++ program for iterative post 
// order using two stacks 
#include <bits/stdc++.h> 
using namespace std; 


// Maximum stack size 
#define MAX_SIZE 100 

// A tree node 
class Node 
{ 
	public: 
	int data; 
	Node *left, *right; 
}; 

// Stack type 
class Stack 
{ 
	public: 
	int size; 
	int top; 
	Node** array; 
}; 

// A utility function to create a new tree node 
Node* newNode(int data) 
{ 
	Node* node = new Node(); 
	node->data = data; 
	node->left = node->right = NULL; 
	return node; 
} 

// A utility function to create a stack of given size 
Stack* createStack(int size) 
{ 
	Stack* stack = new Stack(); 
	stack->size = size; 
	stack->top = -1; 
	stack->array = new Node*[(stack->size * sizeof(Node*))]; 
	return stack; 
} 

// BASIC OPERATIONS OF STACK 
int isFull(Stack* stack) 
{ 
	return stack->top - 1 == stack->size; 
} 

int isEmpty(Stack* stack) 
{ 
	return stack->top == -1; 
} 

void push(Stack* stack, Node* node) 
{ 
	if (isFull(stack)) 
		return; 
	stack->array[++stack->top] = node; 
} 

Node* pop(Stack* stack) 
{ 
	if (isEmpty(stack)) 
		return NULL; 
	return stack->array[stack->top--]; 
} 

// An iterative function to do post order 
// traversal of a given binary tree 
void postOrderIterative(Node* root) 
{ 
	if (root == NULL) 
		return; 

	// Create two stacks 
	Stack* s1 = createStack(MAX_SIZE); 
	Stack* s2 = createStack(MAX_SIZE); 

	// push root to first stack 
	push(s1, root); 
	Node* node; 

	// Run while first stack is not empty 
	while (!isEmpty(s1)) 
	{ 
		// Pop an item from s1 and push it to s2 
		node = pop(s1); 
		push(s2, node); 

		// Push left and right children 
		// of removed item to s1 
		if (node->left) 
			push(s1, node->left); 
		if (node->right) 
			push(s1, node->right); 
	} 

	// Print all elements of second stack 
	while (!isEmpty(s2)) { 
		node = pop(s2); 
		cout<<node->data<<" "; 
	} 
} 

// Driver code 
int main() 
{ 
	// Let us construct the tree 
	// shown in above figure 
	Node* root = NULL; 
	root = newNode(1); 
	root->left = newNode(2); 
	root->right = newNode(3); 
	root->left->left = newNode(4); 
	root->left->right = newNode(5); 
	root->right->left = newNode(6); 
	root->right->right = newNode(7); 

	postOrderIterative(root); 

	return 0; 
} 

// This code is contributed by rathbhupendra 
