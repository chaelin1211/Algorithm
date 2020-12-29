#include <stdio.h>
typedef struct Node{
	char ele;		//data
	struct Node* prev, *next;
}Node;

Node* initNode() {
	Node* head, *trailer;
	head = (Node*)malloc(sizeof(Node));
	trailer = (Node*)malloc(sizeof(Node));
	head->next = trailer;
	head->prev = NULL;
	
	trailer->prev = head;
	trailer->next = NULL;
	return head;
}
void add(Node*H, int r, char e) {
	Node* pointer = H;
	Node* newNode;
	newNode = (Node*)malloc(sizeof(Node));
	newNode->ele = e;
	for (int i = 0; i < r; i++) {
		pointer = pointer->next;
		if (pointer == NULL) {
			printf("invalid position\n");
			return;
		}
	}
	newNode->next = pointer;
	pointer->prev->next = newNode;
	newNode->prev = pointer->prev;
	pointer->prev = newNode;
}

void print(Node*H) {
	Node*pointer = H->next;
	
	while (pointer != NULL) {
		printf("%c", pointer->ele);
		pointer = pointer->next;
	}
	printf("\n");
}

void delete(Node*H, int r) {
	Node* pointer = H;
	for (int i = 0; i < r; i++) {
		pointer = pointer->next;
		if (pointer->next == NULL) {
			printf("invalid position\n");
			return;
		}
	}
	pointer->prev->next = pointer->next;
	pointer->next->prev = pointer->prev;
	free(pointer);
}

void get_entry(Node*H, int r) {
	Node* pointer = H;
	for (int i = 0; i < r; i++) {
		pointer = pointer->next;
		if (pointer->next == NULL) {
			printf("invalid position\n");
			return;
		}
	}
	printf("%c\n", pointer->ele);
}
int main() {
	int N, r;
	char C, e;
	Node* List;
	List = initNode();

	scanf("%d\n", &N);

	for (int i = 0; i < N; i++) {
		scanf("%c", &C);
		if (C == '\n') {
			i--;
			continue;
		}
		if (C == 'P') {
			print(List);
			continue;
		}
		else if(C=='A') {
			scanf("%d %c", &r,&e);
			getchar();
			add(List, r, e);
		}
		else if (C == 'D') {
			scanf("%d", &r);
			getchar();
			delete(List, r);
		}
		else if (C == 'G') {
			scanf("%d", &r);
			getchar();
			get_entry(List, r);
		}
	}
}
