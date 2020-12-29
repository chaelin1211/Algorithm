#include<stdio.h>
#define verNum 6
typedef struct Vertices {
	int ind;
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
ver* initVertex(int ele);
edg* initEdge(int v, int w, int o);

void insertVertex(int ele);
void insertEdge(int v, int w, int o);

ver* findVertex(int ele);
edg* findEdg(int ele1, int ele2);

void adjacentVertices(int v);
int oppositeElement(edg* matCell, int ele);
void modifyEdge(int v, int w, int o);
void deleteEdge(edg * edg);

edgList* edgs;
verList* vers;
edg*mat[verNum][verNum];
int main() {
	char c;
	int a, b, w;

	edgs = initEdgList();
	vers = initVerList();

	/*-------데이터 입력-------*/
	for (int i = 1; i <= verNum; i++) {
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

ver* initVertex(int ele) {
	ver* newVer;

	newVer = (ver*)malloc(sizeof(ver));
	newVer->ele = ele;
	newVer->ind = -1;
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

void adjacentVertices(int v) {
	ver*vertex;
	edg*tmp;

	vertex = findVertex(v);

	if (vertex == NULL) {
		printf("-1\n");
		return;
	}

	for (int i = 0; i < verNum; i++) {
		tmp = mat[vertex->ind][i];
		if (tmp != NULL) {
			printf(" %d %d", oppositeElement(tmp, vertex->ele), tmp->Val);
		}
	}
	printf("\n");
}

int oppositeElement(edg* matCell, int ele) {
	if (matCell->ptrVer1->ele == ele)return matCell->ptrVer2->ele;
	else return matCell->ptrVer1->ele;
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
	edg *tmp;

	//delete inform (mat)
	ver1 = pedg->ptrVer1;
	ver2 = pedg->ptrVer2;
	mat[ver1->ind][ver2->ind] = NULL;
	mat[ver2->ind][ver1->ind] = NULL;

	//delete Edge ( EgdList )
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