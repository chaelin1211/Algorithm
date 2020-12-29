#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct Node{
	int ele;		//data
	struct Node* left, *right;
}Node;

Node* init(int e) {
	Node *node;
	node = (Node*)malloc(sizeof(Node));
	node->right = NULL;
	node->left = NULL;
	node->ele = e;
	return node;
}

//탐색경로를 입력 받아 경로 출력
void treesearch(Node* root, char * arr) {
	Node * p = root;
	int i = 0;
	printf(" %d", p->ele);
	for (int i = 0; i < strlen(arr); i++) {
		if (arr[i] == 'R') {
			p = p->right;
			printf(" %d", p->ele);
			continue;
		}
		if (arr[i] == 'L') {
			p = p->left;
			printf(" %d", p->ele);
		}
	}
	printf("\n");
}

//재귀를 이용해 전위순회로 트리 입력 받기
void func(Node*root) {
	int x, y, z;
	scanf("%d %d %d", &x, &y, &z);
	root->ele = x;
	root->left = init(y);
	root->right = init(z);
	if(y!=0){
		func(root->left);
	}
	if (z != 0) {
		func(root->right);
	}
}
int main() {
	int N, x, y, z;
	char arr[100];
	Node* Root;
	Root = init(0);

	scanf("%d", &N); 

	//N개의 노드를 가진 트리 입력 
	func(Root);

	//탐색경로를 입력 받아 탐색
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", arr);
		treesearch(Root, arr);
	}
}
