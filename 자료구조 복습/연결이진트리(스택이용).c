#include <stdio.h>
typedef struct Node{
	int ele;		//data
	struct Node* left, *right;
}Node;

typedef struct Stack {
	struct Node* ele;
	struct Stack*prev, *next;
}Stack;

Node* init(int e) {
	Node *node;
	node = (Node*)malloc(sizeof(Node));
	node->ele = e;
}
Stack* initStack() {
	Stack* h,*t;
	h = (Stack*)malloc(sizeof(Stack));
	t = (Stack*)malloc(sizeof(Stack));
	h->ele = NULL;
	h->next = t;
	t->prev = h;
	h->prev = NULL;
	t->next = NULL;
	return h;
}
void push(Stack *top,Node*node) {
	Stack* newSt = (Stack*)malloc(sizeof(Stack));
	Stack*p = top;

	newSt->ele = node;

	p->next->prev = newSt;
	newSt->prev = p;
	newSt->next = p->next;
	p->next = newSt;
}
Node* pop(Stack*st) {
	Node*p = (Node*)malloc(sizeof(Node));
	Stack*pst = st;
	if (st->next->next != NULL) {
		p = st->next->ele;
		pst = st->next;
		pst->prev->next = pst->next;
		pst->next->prev = pst->prev;
	}
	free(pst);
	return p;
}
void searchTree(Node*root, char*str) {
	Node* pnode = root;
	char* p = str;
	printf(" %d", pnode->ele);
	while (*p != 0) {
		if (*p == 'R') {
			pnode = pnode->right;
			printf(" %d", pnode->ele);
		}
		else {
			pnode = pnode->left;
			printf(" %d", pnode->ele);
		}
		p = p + 1;
	}
}
int main() {
	int N, x, y, z;
	char str[101];
	Node* Root, *pointer;
	Stack* st_tree = initStack();

	Root = (Node*)malloc(sizeof(Node));
	pointer = Root;
	push(st_tree, pointer);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		pointer = pop(st_tree);
		scanf("%d %d %d", &x, &y, &z);
		pointer->ele = x;
		pointer->left = init(y);
		pointer->right = init(z);

		if (z != 0)
			push(st_tree, pointer->right);
		if (y != 0)
			push(st_tree, pointer->left);
	}

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", str);
		searchTree(Root, str);
		printf("\n");
	}
}
