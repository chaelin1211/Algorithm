#include<stdio.h>
typedef struct Node {
	struct Edges* ptrEdg;
	struct Node *Next;
}node;

typedef struct inciList {
	struct Node* Head;
}inciList;

typedef struct Vertices {
	struct inciList* ptrList;
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

verList* initVerList();
edgList* initEdgList();
inciList* initInciList();
ver* initVertex(int ele);
edg* initEdge(int v, int w);

void insertVertex(int ele);
void insertEdge(int v, int w);

ver* findVertex(int ele);
edg* findEdg(int ele1, int ele2);
void addInciList(edg* Edg);
void addInciListOnce(ver* ver1, ver*ver2, edg* Edg);
int oppositeElement(node* nod, int ele);

node* adjacentVertices(int v);

void DFS(verList* vers, int s);
void rDFS(ver* ver);

edgList* edgs;
verList* vers;
int main() {
	char c;
	int n, m, s;		//정점, 간선, 순회 시작 정점
	int a, b;			//간선 시작-끝
	edgs = initEdgList();
	vers = initVerList();

	/*-------데이터 입력-------*/
	scanf("%d %d %d", &n, &m, &s);
	
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		insertEdge(a, b);
	}
	/*------------------------*/

	/*----------순회-----------*/
	DFS(edgs, vers, s);
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

inciList* initInciList() {
	node*head;
	inciList* list;
	head = (node*)malloc(sizeof(node));
	head->ptrEdg = NULL;
	head->Next = NULL;

	list = (inciList*)malloc(sizeof(inciList));
	list->Head = head;
	return list;
}

ver* initVertex(int ele) {
	ver* newVer;

	newVer = (ver*)malloc(sizeof(ver));
	newVer->ele = ele;
	newVer->ptrList = initInciList();
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

	if(findVertex(v)==NULL)
		insertVertex(v);
	if(findVertex(w)==NULL)
		insertVertex(w);

	newEdg = initEdge(v, w);

	if (edgs->first == NULL) {
		edgs->first = newEdg;
	}
	else {
		tmp = edgs->first;
		edgs->first = newEdg;
		newEdg->Next = tmp;
	}
	addInciList(newEdg);
}

void insertVertex(int ele) {
	ver* newVer = initVertex(ele);
	ver* tmp;

	if (vers->first == NULL) {
		vers->first = newVer;
	}
	else {
		tmp = vers->first;
		vers->first = newVer;
		newVer->Next = tmp;
	}
}

void addInciList(edg* Edg) {
	int ele;
	ver* ver1, *ver2;
	node*newNode, *tmp;
	ver1 = Edg->ptrVer1;
	ver2 = Edg->ptrVer2;

	addInciListOnce(ver1, ver2, Edg);
	if (ver1->ele == ver2->ele) return;
	addInciListOnce(ver2, ver1, Edg);
}

void addInciListOnce(ver* ver1, ver*ver2, edg* Edg) {
	int ele;
	node*newNode, *tmp;

	if (ver1->ptrList->Head == NULL) {
		ver1->ptrList = initInciList();
	}

	tmp = ver1->ptrList->Head;
	if (tmp->ptrEdg == NULL) {
		tmp->ptrEdg = Edg;
		tmp->Next = NULL;
	}
	else {
		newNode = (node*)malloc(sizeof(node));
		newNode->ptrEdg = Edg;

		tmp = ver1->ptrList->Head;
		ele = oppositeElement(tmp, ver1->ele);
		if (ele > ver2->ele) {
			ver1->ptrList->Head = newNode;
			newNode->Next = tmp;
		}
		else {
			while (tmp->Next != NULL) {
				ele = oppositeElement(tmp->Next, ver1->ele);
				if (ele > ver2->ele) break;
				tmp = tmp->Next;
			}
			newNode->Next = tmp->Next;
			tmp->Next = newNode;
		}
	}
}

int oppositeElement(node* nod, int ele) {
	int tmp = nod->ptrEdg->ptrVer1->ele;
	if (tmp != ele)return tmp;
	return nod->ptrEdg->ptrVer2->ele;
}

node* adjacentVertices(int v) {
	ver*vert;

	vert = findVertex(v);
	if (vert == NULL) {
		printf("-1\n");
		return;
	}
	return vert->ptrList->Head;
}

void DFS(verList* vers, int s) {
	ver *firstVer = findVertex(s);
	ver *ve = firstVer;
	while (1) {
		if (ve->flag == 0) {		//fresh
			rDFS(ve);
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

void rDFS(ver* ve) {
	int v = ve->ele, w;
	node* adverNode = adjacentVertices(v);
	ver* adVer;
	edg* adEdg;

	ve->flag = 1;
	printf("%d\n", ve->ele);
	while (adverNode != NULL) {
		w = oppositeElement(adverNode, v);
		adEdg = findEdg(v, w);

		if (adEdg->flag == 0) {
			adVer = findVertex(w);
			if (adVer->flag == 0) {
				adEdg->flag = 2;
				rDFS(adVer);
			}
			else {
				adEdg->flag = 3;
			}
		}
		adverNode = adverNode->Next;
	}
}