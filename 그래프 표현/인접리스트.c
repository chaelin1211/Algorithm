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
}ver;

typedef struct VerList {
	struct Vertices *first;
}verList;

typedef struct Edges {
	struct Vertices *ptrVer1;
	struct Vertices *ptrVer2;
	int Val;
	struct Edges *Next;
}edg;

typedef struct EdgList {
	struct Edges *first;
}edgList;

verList* initVerList();
edgList* initEdgList();
inciList* initInciList();
ver* initVertex(int ele);
edg* initEdge(int v, int w, int o);

void insertVertex(int ele);
void insertEdge(int v, int w, int o);

ver* findVertex(int ele);
edg* findEdg(int ele1, int ele2);
void addInciList(edg* Edg);
void addInciListOnce(ver* ver1, ver*ver2, edg* Edg);
int oppositeElement(node* nod, int ele);

void adjacentVertices(int v);
void modifyEdge(int v, int w, int o);
void deleteEdge(edg * edg);
void deleteList(edg * edg);
void deleteListOnce(edg * edg, ver*ver1);

edgList* edgs;
verList* vers;
int main() {
	char c;
	int a, b, w;
	edgs = initEdgList();
	vers = initVerList();

	/*-------데이터 입력-------*/
	for (int i = 1; i <= 6; i++) {
		insertVertex(i);
	}
	insertEdge(1, 2, 1);
	insertEdge(1, 3, 1);
	insertEdge(1, 4, 1);
	insertEdge(1, 6, 2);
	insertEdge(2, 3, 1);
	insertEdge(3, 5, 4);
	insertEdge(5, 5, 4);
	insertEdge(5, 6, 3);
	/*------------------------*/

	while (1) {
		scanf("%c", &c);

		if (c == 'q') return;
		if (c == 'a') {
			scanf("%d", &a);
			getchar();

			adjacentVertices(a);
		}
		if (c == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			getchar();

			modifyEdge(a, b, w);
		}
	}
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

	return newVer;
}
edg* initEdge(int v, int w, int o) {
	ver*ver1, *ver2;
	edg* newEdg;
	ver1 = findVertex(v);
	ver2 = findVertex(w);
	newEdg = (edg*)malloc(sizeof(edg));
	newEdg->Val = o;
	newEdg->Next = NULL;
	newEdg->ptrVer1 = ver1;
	newEdg->ptrVer2 = ver2;
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

void insertEdge(int v, int w, int o) {
	edg* newEdg = initEdge(v, w, o);
	edg*tmp;
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

void adjacentVertices(int v) {
	ver*vert;
	node* tmp;

	vert = findVertex(v);
	if (vert == NULL) {
		printf("-1\n");
		return;
	}
	tmp = vert->ptrList->Head;
	while (tmp != NULL) {
		printf(" %d %d", oppositeElement(tmp, v), tmp->ptrEdg->Val);
		tmp = tmp->Next;
	}
	printf("\n");
}

void modifyEdge(int v, int w, int o) {
	edg*ptrEdg;

	if (findVertex(v) == NULL || findVertex(w) == NULL) {
		printf("-1\n");
		return;
	}

	ptrEdg = findEdg(v, w);
	if (ptrEdg == NULL && o != 0) {
		insertEdge(v, w, o);
		return;
	}
	else if (ptrEdg != NULL && o == 0) {
		deleteEdge(ptrEdg);
		return;
	}
	else if (ptrEdg == NULL && o == 0) {
		return;
	}
	else {	//modify
		ptrEdg->Val = o;
		return;
	}
}

void deleteEdge(edg * pedg) {
	ver *ver1, *ver2;
	edg *tmp, *tmp2;
	deleteList(pedg);

	tmp = edgs->first;
	if (tmp == pedg) {
		edgs->first = tmp->Next;
	}
	else {
		while (tmp->Next != NULL) {
			if (tmp->Next == pedg) {
				tmp->Next = tmp->Next->Next;
				break;
			}
			else {
				tmp = tmp->Next;
			}
		}
	}
	free(pedg);
}

void deleteList(edg * edg) {
	ver*ver1, *ver2;
	node*tmp1, *tmp2;
	ver1 = edg->ptrVer1;
	ver2 = edg->ptrVer2;

	deleteListOnce(edg, ver1);
	if (ver1 == ver2) {
		return;
	}
	deleteListOnce(edg, ver2);
}

void deleteListOnce(edg * edg, ver*ver1) {
	node*tmp1, *tmp2;

	tmp1 = ver1->ptrList->Head;
	tmp2 = ver1->ptrList->Head->Next;

	if (tmp1->ptrEdg == edg) {
		ver1->ptrList->Head = tmp2;
		free(tmp1);
	}
	else {
		while (tmp1->Next != NULL) {
			tmp2 = tmp1->Next;
			if (tmp1->Next->ptrEdg == edg) {
				tmp1->Next = tmp1->Next->Next;
				free(tmp2);
				break;
			}
			else {
				tmp1 = tmp1->Next;
			}
		}
	}
}