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

//정점과 간선을 표현하는데 필요한 함수
//초기화
Vertices* initVertices();
VerNode* initVer(int key);
Edges* initEdges();
EdgNode*initEdg(int w);
InciList*initInciLIst();
InciNode*initInciNode();
//생성, 삽입
VerNode* insertVer(Vertices*ver, int key);
EdgNode*insertEdg(Edges*edgs, VerNode*ver1, VerNode* ver2, int w);
InciNode* insertInciNode(VerNode*ver1, EdgNode*edg);
void creatEdge(Vertices*vers, Edges*edgs, int a, int b, int w);
//검색
VerNode* findVer(Vertices* vers, int a);
VerNode* opposite(EdgNode*edg, VerNode* ver);


//힙(우선순위 큐) 관련 함수
//초기화
Heap* initHeap();
HeapNode* initHeapNode(VerNode*ver);
//삽입
void insertHeap(Heap*Heap, VerNode*ver);
//정렬
void upHeap(Heap*Heap, int  i);
void downHeap(Heap*Heap, int i);
void replaceKey(Heap*Heap, VerNode* z);
//탐색
int isEmpty(Heap*Heap);
HeapNode*removeMin(Heap*Heap);
int contain(Heap*Heap, VerNode*z);

//무방향 양의 가중그래프에서 최단거리 찾기
void DijkstraShortestPaths(Vertices*vers, int s);

//최단거리 출력
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
	//input: 모든 정점들을 저장한 구조체, 모든 간선들을 저장한 구조체, 시작 정점의 Key
	Heap* Heap = initHeap();
	VerNode* tmpNode, *u, *z;
	InciNode*tmpInciNode;
	EdgNode* inciEdg;
	int count = 0;
	
	tmpNode = vers->first->nextVer;

	//우선순위 큐 Heap에 모든 정점 삽입
	//모든 정점의 label d는 무한대로 설정
	//시작 정점의 label d는 0
	while (tmpNode != NULL) {
		if (tmpNode->key == s) {
			//시작 정점의 label d는 0
			tmpNode->d = 0;
		}
		else {
			//d의 값을 최대 가중치 * 최대 간선 수를 초과하는 충분히 큰 값으로 설정
			tmpNode->d = maxW * maxEdgs;
		}
		//우선순위 큐에 삽입
		insertHeap(Heap, tmpNode);
		tmpNode = tmpNode->nextVer;
	}

	while (!isEmpty(Heap)) {
		//Heap에서 Key값이 최소인 노드 u 반환
		u = removeMin(Heap)->verNode;

		//u의 부착 간선 모두 순회
		tmpInciNode = u->inciList->first->next;
		while (tmpInciNode != NULL) {
			//u와 z의 간선 - inciEdg
			inciEdg = tmpInciNode->edgNode;

			z = opposite(inciEdg, u);

			//우선순위 큐에 포함되어 있다면 - 배낭에 들어가지 않은 상태
			if (contain(Heap, z) > 0 ) {
				//z의 label보다 최소 루트라면 갱신
				if ((u->d + inciEdg->w) < z->d) {
					z->d = u->d + inciEdg->w;

					//우선순위 큐 순위 재정의
					replaceKey(Heap, z);
				}
			}
			tmpInciNode = tmpInciNode->next;
		}
	}
}

void printVersD(Vertices *vers) {
	//input: 정점들을 저장한 구조체 포인터
	VerNode*tmpNode = vers->first->nextVer;
	while (tmpNode != NULL) {
		if(tmpNode->d!=0)
			printf("%d %d\n", tmpNode->key, tmpNode->d);
		tmpNode = tmpNode->nextVer;
	}
}
Vertices* initVertices() {
	//output: 정점들을 저장하는 구조체  포인터
	Vertices* vers = (Vertices*)malloc(sizeof(Vertices));

	vers->first = initVer(-1);

	return vers;
}

VerNode* initVer(int key) {
	//input: 생성할 정점의 key
	//output: 새로 생성된 정점 구조체 포인터
	VerNode* newVer;

	newVer = (VerNode*)malloc(sizeof(VerNode));
	newVer->inciList = initInciLIst();
	newVer->key = key;
	newVer->nextVer = NULL;

	return newVer;
}

Edges* initEdges() {
	//output: 간선들을 저장하는 구조체  포인터
	Edges* edgs = (Edges*)malloc(sizeof(Edges));

	edgs->first = initEdg(-1);

	return edgs;
}

EdgNode*initEdg(int w) {
	//input: 생성할 간선의 가중치
	//output: 새로 생성된 간선 구조체 포인터
	EdgNode* newEdg = (EdgNode*)malloc(sizeof(EdgNode));

	newEdg->next = NULL;
	newEdg->verNode1 = NULL;
	newEdg->verNode2 = NULL;
	newEdg->w = w;
}

InciList*initInciLIst() {
	//output: 인접 리스트 구조체 포인터
	InciList*newInciList = (InciList*)malloc(sizeof(InciList));

	newInciList->first = initInciNode();

	return newInciList;
}

InciNode*initInciNode() {
	//output: 인접 리스트 구조체 노드 포인터
	InciNode*newInciNode = (InciNode*)malloc(sizeof(InciNode));

	newInciNode->edgNode = NULL;
	newInciNode->next = NULL;

	return newInciNode;
}

VerNode* insertVer(Vertices*vers, int key) {
	//input: 정점들을 저장한 구조체 포인터(삽입될 구조체), 삽입할 정점의 key
	//output: 새로 생성된 정점 구조체 포인터

	//정점 생성
	VerNode*newNode = initVer(key);
	VerNode*tmpNode = vers->first;

	//정점을 key를 기준으로 오름차순으로 저장 - 접근시 오름차순으로 이루어진다
	while (tmpNode->nextVer != NULL && tmpNode->nextVer->key < newNode->key) {
		tmpNode = tmpNode->nextVer;
	}

	//삽입
	newNode->nextVer = tmpNode->nextVer;
	tmpNode->nextVer = newNode;

	return newNode;
}

EdgNode*insertEdg(Edges*edgs, VerNode*ver1, VerNode* ver2, int w) {
	//input: 간선들을 저장한 구조체 포인터(삽입될 구조체), 연결될 정점 포인터 두개, 생성할 간선의 가중치
	//output: 새로 생성된 간선 구조체 포인터

	//간선 생성
	EdgNode*newEdgNode = initEdg(w);
	EdgNode*tmpEdgNode = edgs->first->next;

	//간선 구조체 설정
	newEdgNode->verNode1 = ver1;
	newEdgNode->verNode2 = ver2;
	newEdgNode->next = tmpEdgNode;

	edgs->first->next = newEdgNode;

	//인접리스트에 내용 추가
	insertInciNode(ver1, newEdgNode);
	insertInciNode(ver2, newEdgNode);

	return newEdgNode;
}

InciNode* insertInciNode(VerNode*ver1, EdgNode*edg) {
	//input: 내용을 추가할 인접 리스트의 간선 포인터, 추가된 간선 포인터
	//output: 추가한 인접 리스트 노드 포인터

	//인접 리스트 구조체 생성
	InciNode*newInciNode = initInciNode();
	InciNode* tmpInciNode = ver1->inciList->first->next;

	newInciNode->edgNode = edg;

	newInciNode->next = tmpInciNode;
	ver1->inciList->first->next = newInciNode;
}

void creatEdge(Vertices*vers, Edges*edgs, int a, int b, int w) {
	//input: 정점들을 저장한 구조체 포인터, 간선들을 저장한 구조체 포인터, 간선의 두 정점의 key, 간선의 가중치
	VerNode* ver1, *ver2;

	//존재하는 정점인지 확인
	ver1 = findVer(vers, a);
	ver2 = findVer(vers, b);

	//존재하지 않는다면 정점 삽입
	if (ver1 == NULL) {
		ver1 = insertVer(vers, a);
	}
	if (ver2 == NULL) {
		ver2 = insertVer(vers, b);
	}

	//간선들을 저장한 구조체에 간선 삽입
	insertEdg(edgs, ver1, ver2, w);
}

VerNode* findVer(Vertices* vers, int a) {
	//input: 정점들을 저장한 구조체 포인터, 탐색할 정점의 key
	//output: 검색된 정점 구조체 포인터
	VerNode* ptrVer;

	ptrVer = vers->first->nextVer;

	//순회
	while (ptrVer != NULL) {
		if (ptrVer->key == a) {
			return ptrVer;
		}
		ptrVer = ptrVer->nextVer;
	}
	return ptrVer;
}

VerNode* opposite(EdgNode*edg, VerNode* ver) {
	//input: 간선 구조체 포인터, 간선의 한 쪽을 이루는 정점의 구조체 포인터
	//output: 입력 받은 간선에서 입력받은 정점의 반대편 정점 구조체	
	if (edg->verNode1 == ver) {
		return edg->verNode2;
	}
	return edg->verNode1;
}

Heap* initHeap() {
	//output: 새로 생성한 힙 포인터
	Heap*newHeap = (Heap*)malloc(sizeof(Heap));

	//모든 정점을 저장하는 Array -> 크기 100
	//1<= n <=100
	newHeap->heapArr = (HeapNode**)malloc(sizeof(HeapNode*) * 100);
	newHeap->lastIndex = 0;

	return newHeap;
}

HeapNode* initHeapNode(VerNode*ver) {
	//input: 힙 노드에 추가할 정점 구조체 포인터
	//output: 새로 생성한 힙 노드 포인터
	HeapNode*newHeap = (HeapNode*)malloc(sizeof(HeapNode));
	newHeap->verNode = ver;
	return newHeap;
}

void insertHeap(Heap*Heap, VerNode*ver) {
	//input: 힙 포인터, 추가할 정점 구조체 포인터
	int* index = &(Heap->lastIndex);

	//힙노드를 새로 생성해 힙에 저장
	Heap->heapArr[++(*index)] = initHeapNode(ver);

	//재배치
	upHeap(Heap, *index);
}

void upHeap(Heap*Heap, int  i) {//재귀
	//input: 힙 포인터, 재배치할 위치 인덱스
	//우선순위 큐의 key: 정점의 d
	HeapNode* tmp;

	if (i / 2 < 1) {					//부모 노드가 있는지 확인
		return;
	}

	//우선순위 큐의 key인 정점의 d를 기준으로 배치
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
	//input: 힙 포인터
	//output: 비어있는 힙인지 아닌지 확인하는 수
	//0: 비어있음
	//1: 비어있지 않음
	if (Heap->lastIndex == 0)
		return 1;
	return 0;
}

HeapNode*removeMin(Heap*Heap) {
	//input: 힙 포인터
	//output: 힙의 가장 위에 위치하는 최솟값을 가진 노드 포인터
	
	//최솟값을 가진 노드의 포인터
	HeapNode *tmp = Heap->heapArr[1];

	int* ind = &(Heap->lastIndex);

	//가장 바깥쪽에 저장된 노드를 루트로 가져옴
	Heap->heapArr[1] = Heap->heapArr[*ind];
	(*ind)--;

	//재배치
	downHeap(Heap, 1);
	return tmp;
}

void downHeap(Heap*Heap, int i) {		//재귀
	//input: 힙 포인터, 재배치할 위치 인덱스

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

	//우선순위 큐의 key인 정점의 d를 기준으로 배치
	if (Heap->heapArr[i]->verNode->d > Heap->heapArr[ind]->verNode->d) {		//down 수행
		tmp = Heap->heapArr[i];
		Heap->heapArr[i] = Heap->heapArr[ind];
		Heap->heapArr[ind] = tmp;
	}

	downHeap(Heap, ind);
}


void replaceKey(Heap*Heap, VerNode* z) {
	//input: 힙 포인터, 정점 구조체 포인터
	
	//힙에서 정점이 저장된 인덱스
	int i = contain(Heap, z);

	//재배치
	upHeap(Heap, i);
	downHeap(Heap, i);
}

int contain(Heap*Heap, VerNode*z) {
	//input: 힙 포인터, 정점 구조체 포인터
	//output: 힙에서의 인덱스
	//힙에 포함되지 않은 경우 -1

	HeapNode* tmpNode;

	for (int i = 1; i <= Heap->lastIndex; i++) {
		tmpNode = Heap->heapArr[i];
		if (tmpNode->verNode == z) {
			return i;
		}
	}
	return -1;
}
