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

Vertices* initVertices();
VerNode* initVer(int key);
Edges* initEdges();
EdgNode*initEdg(int w);
InciList*initInciLIst();
InciNode*initInciNode();
VerNode* insertVer(Vertices*ver, int key);
EdgNode*insertEdg(Edges*edgs, VerNode*ver1, VerNode* ver2, int w);
InciNode* insertInciNode(VerNode*ver1, EdgNode*edg);
void creatEdge(Vertices*vers, Edges*edgs, int a, int b, int w);
VerNode* findVer(Vertices* vers, int a);
VerNode* opposite(EdgNode*edg, VerNode* ver);


//힙 관련 method
Heap* initHeap();
HeapNode* initHeapNode(VerNode*ver);
void insertHeap(Heap*Heap, VerNode*ver);
void upHeap(Heap*Heap, int  i);
int isEmpty(Heap*Heap);
HeapNode*removeMin(Heap*Heap);
void downHeap(Heap*Heap, int i);
int contain(Heap*Heap, VerNode*z);
void replaceKey(Heap*Heap, VerNode* z, int w);

void prim_jarnik(Vertices*vers, Edges*edgs);

Vertices* vers;
Edges*edgs;

int main() {
	int n, m;
	int a, b, w;

	vers = initVertices();
	edgs = initEdges();

	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &w);
		creatEdge(vers, edgs, a, b, w);
	}

	prim_jarnik(vers, edgs);
}

void prim_jarnik(Vertices*vers, Edges*edgs) {
	Heap* Heap = initHeap();
	VerNode* tmpNode, *u, *z;
	InciNode*tmpInciNode;
	EdgNode* inciEdg;
	int count = 0;

	tmpNode = findVer(vers, 1);
	tmpNode->d = 0;

	tmpNode = vers->first->nextVer;

	while (tmpNode != NULL) {
		insertHeap(Heap, tmpNode);
		tmpNode = tmpNode->nextVer;
	}

	while (!isEmpty(Heap)) {
		u = removeMin(Heap)->verNode;
		printf(" %d", u->key);
		count += u->d;
		tmpInciNode = u->inciList->first->next;
		while (tmpInciNode != NULL) {
			inciEdg = tmpInciNode->edgNode;
			z = opposite(inciEdg, u);
			if (contain(Heap, z) > 0 && (z->d > inciEdg->w)) {
				z->d = inciEdg->w;
				replaceKey(Heap, z, inciEdg->w);
			}
			tmpInciNode = tmpInciNode->next;
		}
	}

	printf("\n%d\n", count);
}

Vertices* initVertices() {
	Vertices* vers = (Vertices*)malloc(sizeof(Vertices));

	vers->first = initVer(-1);

	return vers;
}

VerNode* initVer(int key) {
	VerNode* newVer;

	newVer = (VerNode*)malloc(sizeof(VerNode));
	newVer->inciList = initInciLIst();
	newVer->key = key;
	newVer->d = 10000;
	newVer->nextVer = NULL;

	return newVer;
}

Edges* initEdges() {
	Edges* edgs = (Edges*)malloc(sizeof(Edges));

	edgs->first = initEdg(-1);

	return edgs;
}

EdgNode*initEdg(int w) {
	EdgNode* newEdg = (EdgNode*)malloc(sizeof(EdgNode));

	newEdg->next = NULL;
	newEdg->verNode1 = NULL;
	newEdg->verNode2 = NULL;
	newEdg->w = w;
}

InciList*initInciLIst() {
	InciList*newInciList = (InciList*)malloc(sizeof(InciList));

	newInciList->first = initInciNode();

	return newInciList;
}

InciNode*initInciNode() {
	InciNode*newInciNode = (InciNode*)malloc(sizeof(InciNode));

	newInciNode->edgNode = NULL;
	newInciNode->next = NULL;

	return newInciNode;
}

VerNode* insertVer(Vertices*vesr, int key) {
	VerNode*newNode = initVer(key);
	VerNode*tmpNode = vesr->first->nextVer;

	newNode->nextVer = tmpNode;
	vesr->first->nextVer = newNode;

	return newNode;
}

EdgNode*insertEdg(Edges*edgs, VerNode*ver1, VerNode* ver2, int w) {
	EdgNode*newEdgNode = initEdg(w);
	EdgNode*tmpEdgNode = edgs->first->next;

	newEdgNode->verNode1 = ver1;
	newEdgNode->verNode2 = ver2;
	newEdgNode->next = tmpEdgNode;

	edgs->first->next = newEdgNode;

	insertInciNode(ver1, newEdgNode);
	insertInciNode(ver2, newEdgNode);

	return newEdgNode;
}

InciNode* insertInciNode(VerNode*ver1, EdgNode*edg) {
	InciNode*newInciNode = initInciNode();
	InciNode* tmpInciNode = ver1->inciList->first->next;

	newInciNode->edgNode = edg;

	newInciNode->next = tmpInciNode;
	ver1->inciList->first->next = newInciNode;
}

void creatEdge(Vertices*vers, Edges*edgs, int a, int b, int w) {
	VerNode* ver1, *ver2;
	ver1 = findVer(vers, a);
	ver2 = findVer(vers, b);

	if (ver1 == NULL) {
		ver1 = insertVer(vers, a);
	}
	if (ver2 == NULL) {
		ver2 = insertVer(vers, b);
	}

	insertEdg(edgs, ver1, ver2, w);
}

VerNode* findVer(Vertices* vers, int a) {
	VerNode* ptrVer;

	ptrVer = vers->first->nextVer;

	while (ptrVer != NULL) {
		if (ptrVer->key == a) {
			return ptrVer;
		}
		ptrVer = ptrVer->nextVer;
	}
	return ptrVer;
}

VerNode* opposite(EdgNode*edg, VerNode* ver) {
	if (edg->verNode1 == ver) {
		return edg->verNode2;
	}
	return edg->verNode1;
}

Heap* initHeap() {
	Heap*newHeap = (Heap*)malloc(sizeof(Heap));

	newHeap->heapArr = (HeapNode**)malloc(sizeof(HeapNode*) * 100);
	newHeap->lastIndex = 0;

	return newHeap;
}

HeapNode* initHeapNode(VerNode*ver) {
	HeapNode*newHeap = (HeapNode*)malloc(sizeof(HeapNode));
	newHeap->verNode = ver;
	return newHeap;
}

void insertHeap(Heap*Heap, VerNode*ver) {
	int* index = &(Heap->lastIndex);

	Heap->heapArr[++(*index)] = initHeapNode(ver);

	upHeap(Heap, *index);
}

void upHeap(Heap*Heap, int  i) {//재귀
	HeapNode* tmp;

	if (i / 2 < 1) {					//부모 노드가 있는지 확인
		return;
	}
	if (Heap->heapArr[i]->verNode->d < Heap->heapArr[i / 2]->verNode->d) {
		tmp = Heap->heapArr[i];
		Heap->heapArr[i] = Heap->heapArr[i / 2];
		Heap->heapArr[i / 2] = tmp;
		i /= 2;
	}
	else {						//제자리를 찾았으면 종료
		return;
	}
	upHeap(Heap, i);
}

int isEmpty(Heap*Heap) {
	if (Heap->lastIndex == 0)
		return 1;
	return 0;
}

HeapNode*removeMin(Heap*Heap) {
	HeapNode *tmp = Heap->heapArr[1];
	int* ind = &(Heap->lastIndex);

	Heap->heapArr[1] = Heap->heapArr[*ind];
	(*ind)--;

	downHeap(Heap, 1);
	return tmp;
}

void downHeap(Heap*Heap, int i) {		//재귀
	HeapNode* tmp;
	int n = Heap->lastIndex;
	int ind;						//down되어질 자리 index
	if (i * 2 > n) {				//자식 노드가 있는지 확인
		return;					//left, right 자식 다 없음
	}
	if (i * 2 + 1 <= n) {		//left, right 자식 다 있음
		ind = Heap->heapArr[i * 2]->verNode->d < Heap->heapArr[i * 2 + 1]->verNode->d ? i * 2 : i * 2 + 1;
	}
	else {						//left 자식만 있음
		ind = i * 2;
	}

	if (Heap->heapArr[i]->verNode->d > Heap->heapArr[ind]->verNode->d) {		//down 수행
		tmp = Heap->heapArr[i];
		Heap->heapArr[i] = Heap->heapArr[ind];
		Heap->heapArr[ind] = tmp;
	}

	downHeap(Heap, ind);
}


void replaceKey(Heap*Heap, VerNode* z, int w) {
	int i = contain(Heap, z);
	z->d = w;
	upHeap(Heap, i);
	downHeap(Heap, i);
}

int contain(Heap*Heap, VerNode*z) {
	HeapNode* tmpNode;

	for (int i = 1; i <= Heap->lastIndex; i++) {
		tmpNode = Heap->heapArr[i];
		if (tmpNode->verNode == z) {
			return i;
		}
	}
	return -1;
}
