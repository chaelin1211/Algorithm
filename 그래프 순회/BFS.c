#include<stdio.h>
typedef struct Vertices {
	int ind;
	int ele;
	struct Vertices* Next;
	int flag;
	//0: fresh;
	//1: visited;
}ver;

typedef struct VerList {
	struct Vertices *first;
}verList;

typedef struct Edges {
	struct Vertices *ptrVer1;
	struct Vertices *ptrVer2;
	struct Edges *Next;
	int flag;
	//0: fresh;
	//1: visited;
	//2: Tree;
	//3: Back;
}edg;

typedef struct EdgList {
	struct Edges *first;
}edgList;

typedef struct Node {
	struct Vertices *ver;
	struct Node* Next;
}node;

typedef struct List {
	struct Node* nodeList;
	struct List* Next;
}list;

verList* initVerList();
edgList* initEdgList();
ver* initVertex(int ele);
edg* initEdge(int v, int w);

void insertVertex(int ele);
void insertEdge(int v, int w);

ver* findVertex(int ele);
edg* findEdg(int ele1, int ele2);

edg** adjacentVertices(int v, int verNum);
int oppositeElement(edg* matCell, int ele);
/*
void modifyEdge(int v, int w, int o);
void deleteEdge(edg * edg);
*/

void BFS(verList* vers, int s, int verNum);
void BFS1(ver* ve, int verNum);

edgList* edgs;
verList* vers;
edg***mat;
int main() {
	char c;
	int n, m, s;		//정점, 간선, 순회 시작 정점
	int a, b;			//간선 시작-끝
	edgs = initEdgList();
	vers = initVerList();

	/*-------데이터 입력-------*/
	scanf("%d %d %d", &n, &m, &s);

	mat = (edg***)malloc(sizeof(edg**)*n);
	for (int i = 0; i < n; i++) {
		mat[i] = (edg**)malloc(sizeof(edg*)*n);
		for (int j = 0; j < n; j++) {
			mat[i][j] = NULL;
		}
	}


	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		insertEdge(a, b);
	}
	/*------------------------*/

	/*----------순회-----------*/
	BFS(vers, s, n);
	/*------------------------*/
}

verList* initVerList() {
	verList*newVers;
	newVers = (verList*)malloc(sizeof(verList));
	newVers->first = NULL;
	return newVers;
}

edgList* initEdgList() {
	edgList*newEdgs;
	newEdgs = (edgList*)malloc(sizeof(edgList));
	newEdgs->first = NULL;
	return newEdgs;
}

ver* initVertex(int ele) {
	ver* newVer;

	newVer = (ver*)malloc(sizeof(ver));
	newVer->ele = ele;
	newVer->ind = -1;
	newVer->Next = NULL;
	newVer->flag = 0;

	return newVer;
}

edg* initEdge(int v, int w) {
	ver*ver1, *ver2;
	edg* newEdg;
	ver1 = findVertex(v);
	ver2 = findVertex(w);

	newEdg = (edg*)malloc(sizeof(edg));
	newEdg->Next = NULL;
	newEdg->ptrVer1 = ver1;
	newEdg->ptrVer2 = ver2;
	newEdg->flag = 0;

	mat[ver1->ind][ver2->ind] = newEdg;
	mat[ver2->ind][ver1->ind] = newEdg;
	return newEdg;
}

ver* findVertex(int ele) {
	ver* ptrver = vers->first;
	while (ptrver != NULL) {
		if (ptrver->ele == ele) {
			return ptrver;
		}
		ptrver = ptrver->Next;
	}
	return ptrver;
}

edg* findEdg(int ele1, int ele2) {
	edg*ptredg = edgs->first;
	while (ptredg != NULL) {
		if (ptredg->ptrVer1->ele == ele1 && ptredg->ptrVer2->ele == ele2) {
			return ptredg;
		}
		else if (ptredg->ptrVer1->ele == ele2 && ptredg->ptrVer2->ele == ele1) {
			return ptredg;
		}
		ptredg = ptredg->Next;
	}
	return ptredg;
}

void insertEdge(int v, int w) {
	edg* newEdg;
	edg*tmp;

	if (findVertex(v) == NULL) {
		insertVertex(v);
	}

	if (findVertex(w) == NULL) {
		insertVertex(w);
	}

	newEdg = initEdge(v, w);
	if (edgs->first == NULL) {
		edgs->first = newEdg;
	}
	else {
		tmp = edgs->first;
		edgs->first = newEdg;
		newEdg->Next = tmp;
	}
}

void insertVertex(int ele) {
	ver* newVer = initVertex(ele);
	ver* tmp = initVertex(0);
	int i = 0;
	if (vers->first == NULL) {
		newVer->ind = i++;
		vers->first = newVer;
		return;
	}

	i++;

	tmp = vers->first;
	while (tmp->Next != NULL) {
		newVer->ind = i++;
		tmp = tmp->Next;
	}

	newVer->ind = i++;
	tmp->Next = newVer;
}

edg** adjacentVertices(int v, int verNum) {
	ver*vertex;

	vertex = findVertex(v);

	if (vertex == NULL) {
		printf("-1\n");
		return;
	}
	return mat[vertex->ind];
}

int oppositeElement(edg* matCell, int ele) {
	if (matCell->ptrVer1->ele == ele)return matCell->ptrVer2->ele;
	else return matCell->ptrVer1->ele;
}

void BFS(verList* vers, int s, int verNum) {
	ver *firstVer = findVertex(s);
	ver *ve = firstVer;
	while (1) {
		if (ve->flag == 0) {		//fresh
			BFS1(ve, verNum);
		}
		ve = ve->Next;
		if (ve == NULL) {
			ve = vers->first;
		}
		if (ve == firstVer) {
			break;
		}
	}
}
list*initList() {
	list*L;
	L = (list*)malloc(sizeof(list));
	L->nodeList = (node*)malloc(sizeof(node));
	L->nodeList->ver = NULL;
	L->nodeList->Next = NULL;
	L->Next = NULL;

	return L;
}

node* initNode() {
	node*nod;
	nod = (node*)malloc(sizeof(node));
	nod->Next = NULL;
	nod->ver = NULL;
}
void insertListVer(node*nL, ver*ver) {
	node*tmp, *newNode;
	newNode = (node*)malloc(sizeof(node));
	newNode->ver = ver;
	int v = ver->ele;
	tmp = nL;
	
	while (tmp->Next != NULL) {
		if (tmp->Next->ver->ele < v) {
			tmp = tmp->Next;
		}
		else {
			break;
		}
	}
	newNode->Next = tmp->Next;
	tmp->Next = newNode;
}

void BFS1(ver* ve, int verNum) {
	list *L, *L1, *L2;
	node* nod,*nod2, *tmpNode;
	edg** adm, *tmp;
	ver * adVer;
	int v, w;

	//list 초기화
	L = initList();
	insertListVer(L->nodeList, ve);
	/*
	L->nodeList->ver = NULL;
	L->nodeList->Next = (node*)malloc(sizeof(node));
	L->nodeList->Next->ver = NULL;
	*/
	L1 = L;
	ve->flag = 1;
	
	while (1) {		
		L1->Next = initList();
		L2 = L1->Next;
		
		nod = L1->nodeList->Next;
		nod2 = L2->nodeList;
		while (1) {		
			printf("%d\n", nod->ver->ele);
			ve = nod->ver;
			v = ve->ele;

			adm = adjacentVertices(v, verNum);
			tmpNode = initNode();
			for (int i = 0; i < verNum; i++) {
				tmp = adm[i];
				if (tmp != NULL) {
					w = oppositeElement(tmp, v);
					adVer = findVertex(w);
					if (adVer->flag == 0) {
						tmp->flag = 2;
						adVer->flag = 1;
						insertListVer(tmpNode, adVer);
						/*nod2->ver = adVer;
						nod2->Next = (node*)malloc(sizeof(node));
						nod2->Next->ver = NULL;
					
						nod2 = nod2->Next;*/
					}
					else {
						tmp->flag = 3;
					}
				}
			}
			nod2->Next = tmpNode->Next;
			while (nod2->Next != NULL)
				nod2 = nod2->Next;

			nod = nod->Next;
			if (nod == NULL)
				break;
		}
		L1 = L2;
		L2 = NULL;

		//Empty
		if (L1->nodeList->Next== NULL) {
			break;
		}
	}

}