#include<stdio.h>
#include<stdlib.h>
typedef struct ArrayList {
	struct Node *head;
}ArrayList;

typedef struct Node {
	int ele;
	struct Node* next;
}Node;

ArrayList* initArray();
void push(ArrayList* arr, int ele);
Node* initNode(int ele);
void mergeSort(ArrayList* arr);
void rMergeSort(ArrayList* arr, int l, int r);
void merge(ArrayList* arr, int l, int m, int r);
Node* getNode(ArrayList *arr, int index);
void printArray(ArrayList *arr);

int n;
int main() {
	int ele;
	ArrayList* arr;
	arr = initArray();

	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &ele);
		push(arr, ele);
	}

	mergeSort(arr);

	printArray(arr);
}

ArrayList *initArray() {
	Node *node;
	ArrayList *arr;
	node = (Node*)malloc(sizeof(Node));
	node->ele = 0;
	node->next = NULL;
	arr = (ArrayList*)malloc(sizeof(ArrayList));
	
	arr->head = node;

	return arr;
}

void push(ArrayList* arr, int ele) {
	Node*pnode = arr->head, *node;
	while (pnode->next != NULL) {
		pnode = pnode->next;
	}
	node = initNode(ele);
	pnode->next = node;

	//ù��° ���� ����ִ� ���
	return;
}

Node* initNode(int ele) {
	Node* node;
	node = (Node*)malloc(sizeof(Node));

	node->ele = ele;
	node->next = NULL;

	return node;
}

void mergeSort(ArrayList* arr) {
	//ù��° ���� ����ִ� ���
	rMergeSort(arr, 1, n);
	return;
}
void rMergeSort(ArrayList *arr, int l, int r) {
	//arr
	//[l]------[m] [m+1]-------[r]

	int m;
	if (l < r) {
		m = (l + r) / 2;
		rMergeSort(arr, l, m);
		rMergeSort(arr, m+1, r);
		
		merge(arr, l, m, r);
	}
}
void merge(ArrayList* arr, int l, int m, int r) {
	//arr
	//[l]------[m] [m+1]-------[r]
	// i						j
	int i = l;
	int j = m + 1;
	int tmp;
	Node* inode,* jnode, *prenode;
	
	prenode = getNode(arr, i-1);		//����Ʈ�� ù ���� ����ֱ� ������ ����
	inode = prenode->next;
	jnode = getNode(arr, j-1);			
	//���� ���� �˰��� ���� �� �� ���� ��带 �̿��ؾ� �Ѵ�.
	//���Ͽ��� ����Ʈ�̱� ����
	
	while (i <= m && j <= r) {
		if (inode->ele > jnode->next->ele) {
			//i�� j�� �� ele�� ���� ���� l�� �������� �Űܹ����� (prenode)
			prenode->next = jnode->next;
			jnode->next = jnode->next->next;
			prenode->next->next = inode;
			prenode = prenode->next;
			j++;
		}
		else {
			inode = inode->next;
			prenode = prenode->next;
			i++;
		}
	}
}
Node* getNode(ArrayList *arr, int index) {
	Node *pnode = arr->head;
	for (int i = 0; i < index; i++) {
		pnode = pnode->next;
	}
	return pnode;
}

void printArray(ArrayList *arr) {
	Node* pnode = arr->head->next;
	
	while (pnode != NULL) {
		printf("%d ", pnode->ele);
		pnode = pnode->next;
	}
}