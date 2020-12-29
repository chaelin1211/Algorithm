#include<stdio.h>
#include<stdlib.h>

typedef struct Vertice {
	struct Node *incidenceList;
	char Value;
	int inDegree;
}Vertice;

typedef struct Node {
	int idx;
	struct Node*next;
}Node;

typedef struct Edge {
	int idx1, idx2;
}Edge;

typedef struct DirectedGraph {
	struct Vertice* vers;
	struct Edge* edgs;
}DirectedGraph;

typedef struct QueueNode {
	struct QueueNode*Next;
	int indexOfVertice;
}QueueNode;

typedef struct Queue {
	struct QueueNode *Head;
}Queue;

DirectedGraph G;
Queue Q;
int topOrder[101];
int n, m;

void buildGraph();
void initializeGraph();
void insertVertext(int i, char c);
void insertDirectedEgde(char u, char w, int i);
int index(char u);
void addFirst(Vertice*ver, int idx);
void topologicalSort();
void initialQ();
int isEmpty();
void enqueue(int idx);
int dequeue();
int isOutEdge(int idxOfVertice, Node*incidentNode);

int main() {
	buildGraph();
	topologicalSort();

	if (topOrder[0] == 0) {
		printf("0\n");
		return;
	}
	else {
		for (int i = 1; i <= n; i++) {
			printf("%c ", G.vers[topOrder[i]].Value);
		}
		printf("\n");
		return;
	}
}

void buildGraph() {
	char c, u, w;

	initializeGraph();

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		getchar();
		scanf("%c", &c);
		insertVertext(i, c);
	}

	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		getchar();
		scanf("%c %c", &u, &w);
		insertDirectedEgde(u, w, i);
	}

}

void initializeGraph() {
	G.vers = (Vertice*)malloc(sizeof(Vertice) * 100);
	G.edgs = (Edge*)malloc(sizeof(Edge) * 100);
}

void insertVertext(int i, char c) {
	G.vers[i].Value = c;
	G.vers[i].incidenceList = (Node*)malloc(sizeof(Node));
	G.vers[i].incidenceList->idx = -1;
	G.vers[i].incidenceList->next = NULL;
	G.vers[i].inDegree = 0;
}

void insertDirectedEgde(char u, char w, int i) {
	int idxU, idxW;

	idxU = index(u);
	idxW = index(w);

	G.edgs[i].idx1 = idxU;
	G.edgs[i].idx2 = idxW;

	addFirst(G.vers + idxU, i);
	addFirst(G.vers + idxW, i);

	G.vers[idxW].inDegree++;
}

int index(char u) {
	for (int i = 0; i < n; i++) {
		if (G.vers[i].Value == u) {
			return i;
		}
	}
	return -1;
}

void addFirst(Vertice*ver, int idx) {
	Node *node, *tmp;

	node = (Node*)malloc(sizeof(Node));
	node->idx = idx;

	tmp = ver->incidenceList->next;

	node->next = tmp;
	ver->incidenceList->next = node;
}

void topologicalSort() {
	int in[100];
	int t, idx, tmp;
	int e, w;
	Edge*edg;
	Node*incidentList;

	initialQ();

	for (int i = 0; i < n; i++) {		//모든 정점 개수
		in[i] = G.vers[i].inDegree;
		if (in[i] == 0) {
			enqueue(i);
		}
	}

	t = 1;

	while (!isEmpty()) {
		tmp = dequeue();		//vertice의 index
		topOrder[t] = tmp;
		t++;

		incidentList = G.vers[tmp].incidenceList->next;

		while (incidentList != NULL) {
			if (isOutEdge(tmp, incidentList)) {
				e = incidentList->idx;
				w = G.edgs[e].idx2;
				in[w] --;
				if (in[w] == 0) {
					enqueue(w);
				}
			}
			incidentList = incidentList->next;
		}
	}
	if (t <= n) {				//DAG가 아님
		topOrder[0] = 0;
	}
	else {					//DAG
		topOrder[0] = 1;
	}
	return;
}

void initialQ() {
	Q.Head = (QueueNode*)malloc(sizeof(QueueNode));
	Q.Head->Next = NULL;
	Q.Head->indexOfVertice = -1;
}

int isEmpty() {
	QueueNode* tmpQ;
	tmpQ = Q.Head;
	if (tmpQ->Next == NULL)
		return 1;
	return 0;
}

void enqueue(int idx) {
	QueueNode* tmpQ;
	tmpQ = Q.Head;
	while (tmpQ->Next != NULL) {
		tmpQ = tmpQ->Next;
	}
	tmpQ->Next = (QueueNode*)malloc(sizeof(QueueNode));
	tmpQ = tmpQ->Next;

	tmpQ->Next = NULL;
	tmpQ->indexOfVertice = idx;
}

int dequeue() {
	int idx = -1;
	QueueNode* tmpQ;

	if (isEmpty()) {
		return idx;
	}

	idx = Q.Head->Next->indexOfVertice;

	tmpQ = Q.Head->Next;
	Q.Head->Next = Q.Head->Next->Next;

	return idx;
}

int isOutEdge(int idxOfVertice, Node*incidentNode) {
	Edge edg = G.edgs[incidentNode->idx];

	if (edg.idx1 == idxOfVertice) {
		return 1;
	}

	return 0;
}