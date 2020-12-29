#include<stdio.h>
#include<stdlib.h>
typedef struct VerNode {
	int d;
}VerNode;

typedef struct EdgNode {
	struct VerNode*verNode1;
	struct VerNode*verNode2;

	int w;

	struct EdgNode*next;
}EdgNode;

//������ ������ ǥ���ϴµ� �ʿ��� �Լ�
void creatEdge(VerNode*vers, EdgNode*edgs, int a, int b, int w, int i);

//���� ���߱׷������� �ִܰŸ� ã��
void BellmanFordShortestPaths(VerNode*vers, EdgNode*edgs, int s);

//�ִܰŸ� ���
void printVersD(VerNode *vers, int s);

VerNode*vers;
EdgNode*edgs;

int n, m;
int Max = 30 * 1000;

int main() {
	int s;
	int a, b, w;

	scanf("%d %d %d", &n, &m, &s);

	vers = (VerNode*)malloc(sizeof(VerNode)*n + 1);
	edgs = (EdgNode*)malloc(sizeof(EdgNode)*m);


	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &w);
		creatEdge(vers, edgs, a, b, w, i);
	}

	BellmanFordShortestPaths(vers, edgs, s);
	printVersD(vers, s);
}

void BellmanFordShortestPaths(VerNode*vers, EdgNode*edgs, int s) {
	//input: ��� �������� ������ ����ü, ���� ������ Key
	VerNode*u, *z;

	//d label�� ���Ѵ�� ����
	for (int i = 1; i <= n; i++) {
		vers[i].d = Max;
	}

	//���� ������ label d�� 0
	vers[s].d = 0;

	for (int i = 1; i <= n - 1; i++) {
		for (int j = 0; j < m; j++) {
			u = edgs[j].verNode1;
			z = edgs[j].verNode2;

			//�ִ� ��η� ����
			if (z->d > (u->d + edgs[j].w) && u->d != Max) {
				z->d = u->d + edgs[j].w;
			}
		}
	}
}

void printVersD(VerNode *vers, int s) {
	for (int i = 1; i <= n; i++) {
		if (i != s && vers[i].d < Max)
			printf("%d %d\n", i, vers[i].d);
	}
}

void creatEdge(VerNode*vers, EdgNode*edgs, int a, int b, int w, int i) {
	//input: �������� ������ ����ü ������, �������� ������ ����ü ������, ������ �� ������ key, ������ ����ġ

	vers[a].d = Max;
	vers[b].d = Max;

	edgs[i].verNode1 = vers + a;
	edgs[i].verNode2 = vers + b;
	edgs[i].w = w;
}
