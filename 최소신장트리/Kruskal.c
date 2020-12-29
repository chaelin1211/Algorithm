#include<stdio.h>
#include<stdlib.h>
typedef struct Vertices {
	struct VerNode*first;
}Vertices;

typedef struct VerNode {
	struct VerNode* nextVer;
	int key;
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

typedef struct EdgHeap {
	struct EdgHeapNode **heapArr;
	int lastIndex;
}EdgHeap;

typedef struct EdgHeapNode {
	struct EdgNode* edgNode;
}EdgHeapNode;

typedef struct VerHeap {
	struct VerHeapNode **heapArr;
	int lastIndex;
}VerHeap;

typedef struct VerHeapNode {
	struct VerNode* verNode;
}VerHeapNode;

typedef struct VerHeapList {
	struct VerHeapListNode*first;
}VerHeapList;

typedef struct VerHeapListNode {
	struct VerHeap*verHeap;
	struct VerHeapListNode*next;
}VerHeapListNode;

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
EdgHeap* initEdgHeap(int m);
EdgHeapNode* initEdgHeapNode(EdgNode*edg);
void insertEdgHeap(EdgHeap*Heap, EdgNode*edg);
void upEdgHeap(EdgHeap*Heap, int  i);
int isEmptyEdg(EdgHeap*Heap);
EdgHeapNode*removeMinEdg(EdgHeap*Heap);
void downEdgHeap(EdgHeap*Heap, int i);
int containEdg(EdgHeap*Heap, EdgNode*z);


//힙 관련 method
VerHeap* initVerHeap();
VerHeapNode* initHeapNode(VerNode*ver);
void insertVerHeap(VerHeap*Heap, VerNode*ver);
void upVerHeap(VerHeap*Heap, int  i);
int isEmptyVer(VerHeap*Heap);
VerHeapNode*removeMinVer(VerHeap*Heap);
void downVerHeap(VerHeap*Heap, int i);
int containVer(VerHeap*Heap, VerNode*z);
void replaceKey(VerHeap*Heap, VerNode* z, int w);
int findVerHeap(VerHeap*verHeap, VerNode*ver);

//힙리스트 관련
VerHeapList*initVerHeapList();
VerHeapListNode*initVerHeapListNode(VerHeap*verHeap);
void insertVerHeapList(VerHeapList* HeapList, VerNode*ver);
void removeVerHeapList(VerHeapList* HeapList, VerHeap*verHeap);
void mergeHeapListNode(VerHeapList*HeapList, VerHeapListNode* sack1, VerHeapListNode*sack2);
VerHeapListNode*findSack(VerHeapList*HeapList, VerNode*ver);


//void replaceKey(EdgHeap*Heap, EdgNode* z, int w);

void KruskalMST(Vertices*vers, Edges*edgs, int n, int m);

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

	KruskalMST(vers, edgs, n, m);
}


void KruskalMST(Vertices*vers, Edges*edgs, int n, int m) {
	EdgHeap*edgHeap = initVerHeap(m), *tmpHeap;
	EdgHeap*T = initVerHeap(m);
	EdgNode* tmpEdg, *z;
	VerNode*tmpVer, *u, *v;
	InciNode*tmpInciNode;
	EdgNode* inciEdg;
	VerHeapList *verHeapList = initVerHeapList();
	VerHeapListNode *sack1, *sack2;
	int count = 0, num=0;

	//모든 edge를 Heap에 넣기
	tmpEdg = edgs->first->next;
	while (tmpEdg != NULL) {
		insertEdgHeap(edgHeap, tmpEdg);
		tmpEdg = tmpEdg->next;
	}

	//모든 Vertice를 각각의 Heap에 저장
	tmpVer = vers->first->nextVer;
	while (tmpVer != NULL) {
		insertVerHeapList(verHeapList, tmpVer);
		tmpVer = tmpVer->nextVer;
	}

	while (T->lastIndex < n-1) {
		tmpEdg = removeMinEdg(edgHeap)->edgNode;
		sack1 = findSack(verHeapList, tmpEdg->verNode1);
		sack2 = findSack(verHeapList, tmpEdg->verNode2);
		if (sack1 != sack2) {
			insertEdgHeap(T, tmpEdg);
			mergeHeapListNode(verHeapList, sack1, sack2);
		}
	}
	for (int i = 1; i <= T->lastIndex; i++) {
		num = T->heapArr[i]->edgNode->w;
		count += num;
		printf(" %d", num);
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

EdgHeap* initEdgHeap(int m){
	EdgHeap*newHeap = (EdgHeap*)malloc(sizeof(EdgHeap));

	newHeap->heapArr = (EdgHeapNode**)malloc(sizeof(EdgHeapNode*) * m);
	newHeap->lastIndex = 0;

	return newHeap;
}

EdgHeapNode* initEdgHeapNode(EdgNode*edg) {
	EdgHeapNode*newHeap = (EdgHeapNode*)malloc(sizeof(EdgHeapNode));
	newHeap->edgNode = edg;
	return newHeap;
}

void insertEdgHeap(EdgHeap*Heap, EdgNode*edg) {
	int* index =&(Heap->lastIndex);

	Heap->heapArr[++(*index)] = initEdgHeapNode(edg);

	upEdgHeap(Heap, *index);
}

void upEdgHeap(EdgHeap*Heap, int  i) {//재귀
	EdgHeapNode* tmp;

	if (i / 2 < 1) {					//부모 노드가 있는지 확인
		return;
	}
	if (Heap->heapArr[i]->edgNode->w < Heap->heapArr[i / 2]->edgNode->w) {
		tmp = Heap->heapArr[i];
		Heap->heapArr[i] = Heap->heapArr[i/2];
		Heap->heapArr[i / 2] = tmp;
		i /= 2;
	}
	else {						//제자리를 찾았으면 종료
		return;
	}
	upEdgHeap(Heap, i);
}

int isEmptyEdg(EdgHeap*Heap) {
	if (Heap->lastIndex==0)
		return 1;
	return 0;
}

EdgHeapNode*removeMinEdg(EdgHeap*Heap) {
	EdgHeapNode *tmp = Heap->heapArr[1];
	int* ind =&( Heap->lastIndex);

	Heap->heapArr[1] = Heap->heapArr[*ind];
	(*ind)--;

	downEdgHeap(Heap, 1);
	return tmp;
}

void downEdgHeap(EdgHeap*Heap, int i) {		//재귀
	EdgHeapNode* tmp;
	int n = Heap->lastIndex;
	int ind;						//down되어질 자리 index
	if (i * 2 > n) {				//자식 노드가 있는지 확인
		return;					//left, right 자식 다 없음
	}
	if (i * 2 + 1 <= n) {		//left, right 자식 다 있음
		ind = Heap->heapArr[i * 2]->edgNode->w < Heap->heapArr[i * 2 + 1]->edgNode->w ? i * 2 : i * 2 + 1;
	}
	else {						//left 자식만 있음
		ind = i * 2;
	}

	if (Heap->heapArr[i]->edgNode->w > Heap->heapArr[ind]->edgNode->w) {		//down 수행
		tmp = Heap->heapArr[i];
		Heap->heapArr[i] = Heap->heapArr[ind];
		Heap->heapArr[ind] = tmp;
	}

	downEdgHeap(Heap, ind);
}

int containEdg(EdgHeap*Heap, EdgNode*z) {
	EdgHeapNode* tmpNode;

	for (int i = 1; i <= Heap->lastIndex; i++) {
		tmpNode = Heap->heapArr[i];
		if (tmpNode->edgNode == z) {
			return i;
		}
	}
	return -1;
}

/*
void replaceKey(EdgHeap*Heap, EdgNode* z, int w) {
	int i = contain(Heap, z);
	z->d = w;
	upHeap(Heap, i);
	downHeap(Heap, i);
}
*/
VerHeap* initVerHeap() {
	VerHeap*newHeap = (VerHeap*)malloc(sizeof(VerHeap));

	newHeap->heapArr = (VerHeapNode**)malloc(sizeof(VerHeapNode*) * 100);
	newHeap->lastIndex = 0;

	return newHeap;
}

VerHeapNode* initVerHeapNode(VerNode*ver) {
	VerHeapNode*newHeap = (VerHeapNode*)malloc(sizeof(VerHeapNode));
	newHeap->verNode = ver;
	return newHeap;
}

void insertVerHeap(VerHeap*Heap, VerNode*ver) {
	int* index = &(Heap->lastIndex);

	Heap->heapArr[++(*index)] = initVerHeapNode(ver);

	upVerHeap(Heap, *index);
}

void upVerHeap(VerHeap*Heap, int  i) {//재귀
	VerHeapNode* tmp;

	if (i / 2 < 1) {					//부모 노드가 있는지 확인
		return;
	}
	if (Heap->heapArr[i]->verNode->key < Heap->heapArr[i / 2]->verNode->key) {
		tmp = Heap->heapArr[i];
		Heap->heapArr[i] = Heap->heapArr[i / 2];
		Heap->heapArr[i / 2] = tmp;
		i /= 2;
	}
	else {						//제자리를 찾았으면 종료
		return;
	}
	upVerHeap(Heap, i);
}

int isEmptyVer(VerHeap*Heap) {
	if (Heap->lastIndex == 0)
		return 1;
	return 0;
}

VerHeapNode*removeMinVer(VerHeap*Heap) {
	VerHeapNode *tmp = Heap->heapArr[1];
	int* ind = &(Heap->lastIndex);

	Heap->heapArr[1] = Heap->heapArr[*ind];
	(*ind)--;

	downVerHeap(Heap, 1);
	return tmp;
}

void downVerHeap(VerHeap*Heap, int i) {		//재귀
	VerHeapNode* tmp;
	int n = Heap->lastIndex;
	int ind;						//down되어질 자리 index
	if (i * 2 > n) {				//자식 노드가 있는지 확인
		return;					//left, right 자식 다 없음
	}
	if (i * 2 + 1 <= n) {		//left, right 자식 다 있음
		ind = Heap->heapArr[i * 2]->verNode->key < Heap->heapArr[i * 2 + 1]->verNode->key ? i * 2 : i * 2 + 1;
	}
	else {						//left 자식만 있음
		ind = i * 2;
	}

	if (Heap->heapArr[i]->verNode->key > Heap->heapArr[ind]->verNode->key) {		//down 수행
		tmp = Heap->heapArr[i];
		Heap->heapArr[i] = Heap->heapArr[ind];
		Heap->heapArr[ind] = tmp;
	}

	downVerHeap(Heap, ind);
}

int containVer(VerHeap*Heap, VerNode*z) {
	VerHeapNode* tmpNode;

	for (int i = 1; i <= Heap->lastIndex; i++) {
		tmpNode = Heap->heapArr[i];
		if (tmpNode->verNode == z) {
			return i;
		}
	}
	return -1;
}

int findVerHeap(VerHeap*verHeap, VerNode*ver) {
	for (int i = 1; i <= verHeap->lastIndex; i++) {
		if (verHeap->heapArr[i]->verNode == ver) {
			return i;
		}
	}
	return -1;
}

VerHeapList*initVerHeapList() {
	VerHeapList*newHeapList = (VerHeapList*)malloc(sizeof(VerHeapList));
	newHeapList->first = initVerHeapListNode(NULL);
	return newHeapList;
}

VerHeapListNode*initVerHeapListNode(VerHeap*verHeap) {
	VerHeapListNode*newHeapListNode = (VerHeapListNode*)malloc(sizeof(VerHeapListNode));
	newHeapListNode->next = NULL;
	newHeapListNode->verHeap = verHeap;
	return newHeapListNode;
}

void insertVerHeapList(VerHeapList* HeapList, VerNode*ver) {
	VerHeapListNode*tmp = HeapList->first;
	VerHeap * newVerHeap = initVerHeap();
	insertVerHeap(newVerHeap, ver);
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = initVerHeapListNode(newVerHeap);
}

void mergeHeapListNode(VerHeapList*HeapList, VerHeapListNode* sack1, VerHeapListNode*sack2) {
	VerHeap* verHeap1 = sack1->verHeap;
	VerHeap* verHeap2 = sack2->verHeap;
	for (int i = 1; i <= verHeap2->lastIndex; i++) {
		insertVerHeap(verHeap1, verHeap2->heapArr[i]->verNode);
	}
	removeVerHeapList(HeapList, verHeap2);
}

void removeVerHeapList(VerHeapList* HeapList, VerHeap*verHeap) {
	VerHeapListNode*tmp = HeapList->first;
	while (1) {
		if (tmp == NULL)break;
		if (tmp->next->verHeap == verHeap) {
			tmp->next = tmp->next->next;
			break;
		}
		tmp = tmp->next;
	}
}

VerHeapListNode*findSack(VerHeapList*HeapList, VerNode*ver) {
	VerHeapListNode*tmp = HeapList->first->next;
	while (tmp != NULL) {
		if (findVerHeap(tmp->verHeap, ver) >= 0) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return tmp;
}