typedef int Data;
struct listnode {
    Data data;
    struct listnode *next;
};
typedef struct listnode Listnode;

typedef struct {
	Listnode *top;
} Stack;
void init_stack(Stack *s);
int stack_full(Stack *s);
int stack_empty(Stack *s);
void push_stack(Stack *s, Data data);
Data pop_stack(Stack *s);