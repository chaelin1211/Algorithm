#include <stdio.h>
typedef struct node {
	struct node* lChild;
	struct node* rChild;
	struct node* parent;
	int key;
}node;

node* initialTree();
int findElement(int k);
void insertItem(int k);
node* treeSearch(int k);
int removeElement(int k);
int isExternal(node* w);
int isInternal(node* w);
node*inOrderSucc(node*w);
void expandExternal(node*w);
void printTree(node*pnode);
void reduceExternal(node*znode);
node*sibling(node*w);
int isRoot(node*w);

node *tree;
int main() {
	char input=0;
	int k, tmp;

	tree = initialTree();

	while (input != 'q') {
		scanf("%c", &input);
		getchar();

		switch (input) {
		case 'i':
			scanf("%d", &k);
			getchar();
			insertItem(k);
			break;
		case'd':
			scanf("%d", &k);
			getchar();
			tmp = removeElement(k); 
			if (tmp == -1) {
				printf("X\n");
			}
			else {
				printf("%d\n", tmp);
			}
			break;
		case 's':
			scanf("%d", &k);
			getchar();
			tmp = findElement(k);
			if (tmp == -1) {
				printf("X\n");
			}
			else {
				printf("%d\n", tmp);
			}
			break;
		case'p':
			printTree(tree);
			printf("\n");
			break;
		case'q':
			break;
		}
	}
}
node* initialTree() {
	node* newnode;
	newnode = (node*)malloc(sizeof(node));
	newnode->key = -1;
	newnode->parent = NULL;
	newnode->lChild = NULL;
	newnode->rChild = NULL;
	return newnode;
}

void insertItem(int k) {
	node*pnode = treeSearch(k);
	if (isInternal(pnode)) {
		return;	//이미 존재
	}
	else {
		expandExternal(pnode);
		pnode->key = k;
	}
}

int findElement(int k) {
	node *pnode = treeSearch(k);
	return pnode->key;
}
node* treeSearch(int k) {
	node*pnode = tree;
	while (isInternal(pnode)) {
		if (k == pnode->key) {
			return pnode;
		}
		else if (k < pnode->key) {
			pnode = pnode->lChild;
		}
		else {
			pnode = pnode->rChild;
		}
	}
	return pnode;
}

void expandExternal(node*w) {
	w->lChild = initialTree();
	w->rChild = initialTree();

	w->lChild->parent = w;
	w->rChild->parent = w;
	
	return w;
}

int isExternal(node* w) {
	if (w->lChild == NULL && w->rChild == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

int isInternal(node* w) {
	if (w->lChild != NULL || w->rChild != NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

void printTree(node*pnode) {
	if (isExternal(pnode)) {
		return;
	}
	printf(" %d", pnode->key);
	printTree(pnode->lChild);
	printTree(pnode->rChild);
}

int removeElement(int k) {
	node* wnode = treeSearch(k);
	node* ynode, *znode;
	int x;
	x = wnode->key;

	if (isExternal(wnode)) {
		return wnode->key;
	}

	znode = wnode->lChild;
	if (isInternal(znode)) {
		znode = wnode->rChild;
	}

	//w의 모든 자식이 내부노드일 때.
	if (isInternal(znode)){
		ynode = inOrderSucc(wnode);
		znode = ynode->lChild;
		wnode->key = ynode->key;
		reduceExternal(znode);
	}
	//내 - 외
	else {
		reduceExternal(znode);
	}
	return x;
}

void reduceExternal(node*znode) {
	//znode - empty!!!
	node*wnode = znode->parent;
	node*zsibling = sibling(znode);
	node*gnode = wnode->parent;
	zsibling->parent = wnode->parent;

	if (isRoot(wnode)) {
		tree = zsibling; 
	}
	else {
		if (gnode->lChild = wnode) {
			gnode->lChild = zsibling;
		}
		else {
			gnode->rChild = zsibling;
		}
	}
	free(znode);
	free(wnode);
}

node*inOrderSucc(node*w) {
	w = w->rChild;
	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	return w;
}

node*sibling(node*w) {
	if (isRoot(w)) {
		return NULL;
	}
	if (w->parent->lChild == w) {
		return w->parent->rChild;
	}
	else
		return w->parent->lChild;
}
int isRoot(node*w) {
	if (w->parent == NULL)
		return 1;
	return 0;
}