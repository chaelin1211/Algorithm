#include <stdio.h>
typedef struct node {
	int ele;
	struct node* next;
}Node;

void initBucketArray(Node* arr);
Node* initNode(int x);
void insertElement(int x);
int searchElement(int x);
int deleteElement(int x);
void print(Node*arr);
int findBucket(int x);
int M;
Node * arr;
int main() {
	char c = 'p';
	int x;
	scanf("%d", &M);
	getchar();
	arr = (Node*)malloc(sizeof(Node)*M);

	initBucketArray(arr);

	while (1) {
		scanf("%c", &c);
		getchar(); 
		if (c == 'p') {
			print(arr);
			continue;
		}
		if (c == 'e') {
			break;
		}

		scanf("%d", &x);
		getchar();
		if(c == 'i'){
			insertElement(x);
		}
		else if(c=='s'){
			printf("%d\n", searchElement(x));
		}
		else if (c == 'd') {
			printf("%d\n", deleteElement(x));
		}
	}
}

void initBucketArray(Node* arr) {
	for (int i = 0; i < M; i++) {
		arr[i].ele = 0;
		arr[i].next = NULL;
	}
}
Node* initNode(int x) {
	Node*newnode;
	newnode = (Node*)malloc(sizeof(Node));
	newnode->ele = x;
	newnode->next = NULL;
	return newnode;
}
void insertElement(int x) {
	int b = findBucket(x);
	Node*p = arr[b].next;
	arr[b].next = initNode(x);

	arr[b].next->next = p;
}
int searchElement(int x) {
	Node*p;
	int j = 0;
	for (int i = 0; i < M; i++) {
		p = arr + i;
		while (p->next != NULL) {
			p = p->next;
			j++;
			if (p->ele == x) {
				return j;
			}
		}
		j = 0;
	}
	return j;
}
int deleteElement(int x) {
	Node*p;
	Node*tmp;
	int j = 0;
	for (int i = 0; i < M; i++) {
		p = arr + i;
		while (p->next != NULL) {
			j++;
			if (p->next->ele == x) {
				tmp = p->next;
				p->next = p->next->next;
				free(tmp);
				return j;
			}
			p = p->next;
		}
		j = 0;
	}
	return j;
}
void print(Node*arr) {
	Node*p;
	for (int i = 0; i < M; i++) {
		p = arr + i;
		while (p->next != NULL) {
			p = p->next;
			printf(" %d", p->ele);
		}
	}
	printf("\n");
}
int findBucket(int x) {
	return x % M;
}