//#include<stdio.h>
//#include<stdlib.h>
#include <iostream>
using namespace std;

struct _Node{
	int data;
	//struct _Node* last;
	_Node* last;
};
typedef struct _Node Node;

Node* createNode(){
	//Node *newNode = (Node*)malloc(sizeof(Node));
	Node *newNode = new Node;
	//if (newNode == NULL){
	//	printf("No available Memory!\n");
	//}
	return newNode;
}

bool isEmpty(Node* stack){
	return stack == NULL;
}
void Push(int entry, Node* &stack){
	// stack saves the toppest datum
	Node* newNode = createNode();
	newNode->data = entry;
	newNode->last = stack;
    //newNode->last saves the originally toppest datum
	stack = newNode;
}

int Pop(Node* &stack){
	Node* tmpNode;
	int tmp=0;
	if (isEmpty(stack)){
		printf("Stack is empty!\n");
		return -1;
	}
	else{
    	tmpNode = stack; //tmpNode duplicates pointer stack
    	tmp=tmpNode->data;
    	stack = stack->last;
    	delete tmpNode; //利用刪除指向new的指標 釋放先前createNode()動態配置出的記憶體空間
    	return tmp;
	}
}
void clearStack(Node* &stack){
	Node* tmpNode;
	while (stack != NULL){
		tmpNode = stack;
		stack = stack->last;
		//free(tmpNode);
		delete tmpNode;
	}
	cout<<"Stack cleared!"<<endl;
}

void printStack(Node* &stack){
	if (isEmpty(stack)) return;

	printf("Stack:\n");
	while(stack != NULL){
		printf("%d\n", stack->data);
		stack = stack->last;
	}
}

int main(){
	int intArr[] = { 1, 3, 7, 5, 8, 2 }; //自訂一數值陣列
	Node* stack = NULL;
	
	//將陣列中每個值 Push進stack裡
	for (int i = 0; i < (sizeof(intArr)/sizeof(int)); i++){	
		Push(intArr[i], stack);
	}

	cout<<Pop(stack)<<endl; //第一次Pop
	cout<<Pop(stack)<<endl; //第二次Pop
	
	Push(10, stack);//Push 10進stack

	printStack(stack); //列出stack

	clearStack(stack);//清除stack

}

