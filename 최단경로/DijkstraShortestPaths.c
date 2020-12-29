#include<stdio.h>
#include<stdlib.h>
typedef struct Vertices {
	struct VerNode*first;
}Vertices;

typedef struct VerNode {
	struct VerNode* nextVer;
	int key;
	int d;
	struct InciList *inciList;
}VerNode;

typedef 	struct InciList {
	struct InciNode*first;
}InciList;

typedef 	struct InciNode {
	struct EdgNode *edgNode;

	struct InciNode*next;
}InciNode;

typedef struct Edges {
	struct EdgNode*first;
}Edges;

typedef struct EdgNode {
	struct VerNode*verNode1;
	struct VerNode*verNode2;

	int w;

	struct EdgNode*next;
}EdgNode;

typedef struct Heap {
	struct HeapNode **heapArr;
	int lastIndex;
}Heap;

typedef struct HeapNode {
	struct VerNode* verNode;
}HeapNode;

//������ ������ ǥ���ϴµ� �ʿ��� �Լ�
//�ʱ�ȭ
Vertices* initVertices();
VerNode* initVer(int key);
Edges* initEdges();
EdgNode*initEdg(int w);
InciList*initInciLIst();
InciNode*initInciNode();
//����, ����
VerNode* insertVer(Vertices*ver, int key);
EdgNode*insertEdg(Edges*edgs, VerNode*ver1, VerNode* ver2, int w);
InciNode* insertInciNode(VerNode*ver1, EdgNode*edg);
void creatEdge(Vertices*vers, Edges*edgs, int a, int b, int w);
//�˻�
VerNode* findVer(Vertices* vers, int a);
VerNode* opposite(EdgNode*edg, VerNode* ver);


//��(�켱���� ť) ���� �Լ�
//�ʱ�ȭ
Heap* initHeap();
HeapNode* initHeapNode(VerNode*ver);
//����
void insertHeap(Heap*Heap, VerNode*ver);
//����
void upHeap(Heap*Heap, int  i);
void downHeap(Heap*Heap, int i);
void replaceKey(Heap*Heap, VerNode* z);
//Ž��
int isEmpty(Heap*Heap);
HeapNode*removeMin(Heap*Heap);
int contain(Heap*Heap, VerNode*z);

//������ ���� ���߱׷������� �ִܰŸ� ã��
void DijkstraShortestPaths(Vertices*vers, int s);

//�ִܰŸ� ���
void printVersD(Vertices *vers);

Vertices* vers;
Edges*edgs;
int maxW;
int maxEdgs;

int main() {
	int n, m, s;
	int a, b, w; 
	
	maxW = 0;

	vers = initVertices();
	edgs = initEdges();

	scanf("%d %d %d", &n, &m, &s);
	maxEdgs = n * (n - 1) / 2;

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &w);
		if (w > maxW) {
			maxW = w;
		}
		creatEdge(vers, edgs, a, b, w);
	}

	DijkstraShortestPaths(vers, s);
	printVersD(vers);
}

void DijkstraShortestPaths(Vertices*vers, int s) {
	//input: ��� �������� ������ ����ü, ��� �������� ������ ����ü, ���� ������ Key
	Heap* Heap = initHeap();
	VerNode* tmpNode, *u, *z;
	InciNode*tmpInciNode;
	EdgNode* inciEdg;
	int count = 0;
	
	tmpNode = vers->first->nextVer;

	//�켱���� ť Heap�� ��� ���� ����
	//��� ������ label d�� ���Ѵ�� ����
	//���� ������ label d�� 0
	while (tmpNode != NULL) {
		if (tmpNode->key == s) {
			//���� ������ label d�� 0
			tmpNode->d = 0;
		}
		else {
			//d�� ���� �ִ� ����ġ * �ִ� ���� ���� �ʰ��ϴ� ����� ū ������ ����
			tmpNode->d = maxW * maxEdgs;
		}
		//�켱���� ť�� ����
		insertHeap(Heap, tmpNode);
		tmpNode = tmpNode->nextVer;
	}

	while (!isEmpty(Heap)) {
		//Heap���� Key���� �ּ��� ��� u ��ȯ
		u = removeMin(Heap)->verNode;

		//u�� ���� ���� ��� ��ȸ
		tmpInciNode = u->inciList->first->next;
		while (tmpInciNode != NULL) {
			//u�� z�� ���� - inciEdg
			inciEdg = tmpInciNode->edgNode;

			z = opposite(inciEdg, u);

			//�켱���� ť�� ���ԵǾ� �ִٸ� - �賶�� ���� ���� ����
			if (contain(Heap, z) > 0 ) {
				//z�� label���� �ּ� ��Ʈ��� ����
				if ((u->d + inciEdg->w) < z->d) {
					z->d = u->d + inciEdg->w;

					//�켱���� ť ���� ������
					replaceKey(Heap, z);
				}
			}
			tmpInciNode = tmpInciNode->next;
		}
	}
}

void printVersD(Vertices *vers) {
	//input: �������� ������ ����ü ������
	VerNode*tmpNode = vers->first->nextVer;
	while (tmpNode != NULL) {
		if(tmpNode->d!=0)
			printf("%d %d\n", tmpNode->key, tmpNode->d);
		tmpNode = tmpNode->nextVer;
	}
}
Vertices* initVertices() {
	//output: �������� �����ϴ� ����ü  ������
	Vertices* vers = (Vertices*)malloc(sizeof(Vertices));

	vers->first = initVer(-1);

	return vers;
}

VerNode* initVer(int key) {
	//input: ������ ������ key
	//output: ���� ������ ���� ����ü ������
	VerNode* newVer;

	newVer = (VerNode*)malloc(sizeof(VerNode));
	newVer->inciList = initInciLIst();
	newVer->key = key;
	newVer->nextVer = NULL;

	return newVer;
}

Edges* initEdges() {
	//output: �������� �����ϴ� ����ü  ������
	Edges* edgs = (Edges*)malloc(sizeof(Edges));

	edgs->first = initEdg(-1);

	return edgs;
}

EdgNode*initEdg(int w) {
	//input: ������ ������ ����ġ
	//output: ���� ������ ���� ����ü ������
	EdgNode* newEdg = (EdgNode*)malloc(sizeof(EdgNode));

	newEdg->next = NULL;
	newEdg->verNode1 = NULL;
	newEdg->verNode2 = NULL;
	newEdg->w = w;
}

InciList*initInciLIst() {
	//output: ���� ����Ʈ ����ü ������
	InciList*newInciList = (InciList*)malloc(sizeof(InciList));

	newInciList->first = initInciNode();

	return newInciList;
}

InciNode*initInciNode() {
	//output: ���� ����Ʈ ����ü ��� ������
	InciNode*newInciNode = (InciNode*)malloc(sizeof(InciNode));

	newInciNode->edgNode = NULL;
	newInciNode->next = NULL;

	return newInciNode;
}

VerNode* insertVer(Vertices*vers, int key) {
	//input: �������� ������ ����ü ������(���Ե� ����ü), ������ ������ key
	//output: ���� ������ ���� ����ü ������

	//���� ����
	VerNode*newNode = initVer(key);
	VerNode*tmpNode = vers->first;

	//������ key�� �������� ������������ ���� - ���ٽ� ������������ �̷������
	while (tmpNode->nextVer != NULL && tmpNode->nextVer->key < newNode->key) {
		tmpNode = tmpNode->nextVer;
	}

	//����
	newNode->nextVer = tmpNode->nextVer;
	tmpNode->nextVer = newNode;

	return newNode;
}

EdgNode*insertEdg(Edges*edgs, VerNode*ver1, VerNode* ver2, int w) {
	//input: �������� ������ ����ü ������(���Ե� ����ü), ����� ���� ������ �ΰ�, ������ ������ ����ġ
	//output: ���� ������ ���� ����ü ������

	//���� ����
	EdgNode*newEdgNode = initEdg(w);
	EdgNode*tmpEdgNode = edgs->first->next;

	//���� ����ü ����
	newEdgNode->verNode1 = ver1;
	newEdgNode->verNode2 = ver2;
	newEdgNode->next = tmpEdgNode;

	edgs->first->next = newEdgNode;

	//��������Ʈ�� ���� �߰�
	insertInciNode(ver1, newEdgNode);
	insertInciNode(ver2, newEdgNode);

	return newEdgNode;
}

InciNode* insertInciNode(VerNode*ver1, EdgNode*edg) {
	//input: ������ �߰��� ���� ����Ʈ�� ���� ������, �߰��� ���� ������
	//output: �߰��� ���� ����Ʈ ��� ������

	//���� ����Ʈ ����ü ����
	InciNode*newInciNode = initInciNode();
	InciNode* tmpInciNode = ver1->inciList->first->next;

	newInciNode->edgNode = edg;

	newInciNode->next = tmpInciNode;
	ver1->inciList->first->next = newInciNode;
}

void creatEdge(Vertices*vers, Edges*edgs, int a, int b, int w) {
	//input: �������� ������ ����ü ������, �������� ������ ����ü ������, ������ �� ������ key, ������ ����ġ
	VerNode* ver1, *ver2;

	//�����ϴ� �������� Ȯ��
	ver1 = findVer(vers, a);
	ver2 = findVer(vers, b);

	//�������� �ʴ´ٸ� ���� ����
	if (ver1 == NULL) {
		ver1 = insertVer(vers, a);
	}
	if (ver2 == NULL) {
		ver2 = insertVer(vers, b);
	}

	//�������� ������ ����ü�� ���� ����
	insertEdg(edgs, ver1, ver2, w);
}

VerNode* findVer(Vertices* vers, int a) {
	//input: �������� ������ ����ü ������, Ž���� ������ key
	//output: �˻��� ���� ����ü ������
	VerNode* ptrVer;

	ptrVer = vers->first->nextVer;

	//��ȸ
	while (ptrVer != NULL) {
		if (ptrVer->key == a) {
			return ptrVer;
		}
		ptrVer = ptrVer->nextVer;
	}
	return ptrVer;
}

VerNode* opposite(EdgNode*edg, VerNode* ver) {
	//input: ���� ����ü ������, ������ �� ���� �̷�� ������ ����ü ������
	//output: �Է� ���� �������� �Է¹��� ������ �ݴ��� ���� ����ü	
	if (edg->verNode1 == ver) {
		return edg->verNode2;
	}
	return edg->verNode1;
}

Heap* initHeap() {
	//output: ���� ������ �� ������
	Heap*newHeap = (Heap*)malloc(sizeof(Heap));

	//��� ������ �����ϴ� Array -> ũ�� 100
	//1<= n <=100
	newHeap->heapArr = (HeapNode**)malloc(sizeof(HeapNode*) * 100);
	newHeap->lastIndex = 0;

	return newHeap;
}

HeapNode* initHeapNode(VerNode*ver) {
	//input: �� ��忡 �߰��� ���� ����ü ������
	//output: ���� ������ �� ��� ������
	HeapNode*newHeap = (HeapNode*)malloc(sizeof(HeapNode));
	newHeap->verNode = ver;
	return newHeap;
}

void insertHeap(Heap*Heap, VerNode*ver) {
	//input: �� ������, �߰��� ���� ����ü ������
	int* index = &(Heap->lastIndex);

	//����带 ���� ������ ���� ����
	Heap->heapArr[++(*index)] = initHeapNode(ver);

	//���ġ
	upHeap(Heap, *index);
}

void upHeap(Heap*Heap, int  i) {//���
	//input: �� ������, ���ġ�� ��ġ �ε���
	//�켱���� ť�� key: ������ d
	HeapNode* tmp;

	if (i / 2 < 1) {					//�θ� ��尡 �ִ��� Ȯ��
		return;
	}

	//�켱���� ť�� key�� ������ d�� �������� ��ġ
	if (Heap->heapArr[i]->verNode->d < Heap->heapArr[i / 2]->verNode->d) {
		tmp = Heap->heapArr[i];
		Heap->heapArr[i] = Heap->heapArr[i / 2];
		Heap->heapArr[i / 2] = tmp;
		i /= 2;
	}
	else {						//���ڸ��� ã������ ����
		return;
	}
	upHeap(Heap, i);
}

int isEmpty(Heap*Heap) {
	//input: �� ������
	//output: ����ִ� ������ �ƴ��� Ȯ���ϴ� ��
	//0: �������
	//1: ������� ����
	if (Heap->lastIndex == 0)
		return 1;
	return 0;
}

HeapNode*removeMin(Heap*Heap) {
	//input: �� ������
	//output: ���� ���� ���� ��ġ�ϴ� �ּڰ��� ���� ��� ������
	
	//�ּڰ��� ���� ����� ������
	HeapNode *tmp = Heap->heapArr[1];

	int* ind = &(Heap->lastIndex);

	//���� �ٱ��ʿ� ����� ��带 ��Ʈ�� ������
	Heap->heapArr[1] = Heap->heapArr[*ind];
	(*ind)--;

	//���ġ
	downHeap(Heap, 1);
	return tmp;
}

void downHeap(Heap*Heap, int i) {		//���
	//input: �� ������, ���ġ�� ��ġ �ε���

	HeapNode* tmp;
	int n = Heap->lastIndex;
	int ind;						//down�Ǿ��� �ڸ� index
	if (i * 2 > n) {				//�ڽ� ��尡 �ִ��� Ȯ��
		return;					//left, right �ڽ� �� ����
	}
	if (i * 2 + 1 <= n) {		//left, right �ڽ� �� ����
		ind = Heap->heapArr[i * 2]->verNode->d < Heap->heapArr[i * 2 + 1]->verNode->d ? i * 2 : i * 2 + 1;
	}
	else {						//left �ڽĸ� ����
		ind = i * 2;
	}

	//�켱���� ť�� key�� ������ d�� �������� ��ġ
	if (Heap->heapArr[i]->verNode->d > Heap->heapArr[ind]->verNode->d) {		//down ����
		tmp = Heap->heapArr[i];
		Heap->heapArr[i] = Heap->heapArr[ind];
		Heap->heapArr[ind] = tmp;
	}

	downHeap(Heap, ind);
}


void replaceKey(Heap*Heap, VerNode* z) {
	//input: �� ������, ���� ����ü ������
	
	//������ ������ ����� �ε���
	int i = contain(Heap, z);

	//���ġ
	upHeap(Heap, i);
	downHeap(Heap, i);
}

int contain(Heap*Heap, VerNode*z) {
	//input: �� ������, ���� ����ü ������
	//output: �������� �ε���
	//���� ���Ե��� ���� ��� -1

	HeapNode* tmpNode;

	for (int i = 1; i <= Heap->lastIndex; i++) {
		tmpNode = Heap->heapArr[i];
		if (tmpNode->verNode == z) {
			return i;
		}
	}
	return -1;
}
