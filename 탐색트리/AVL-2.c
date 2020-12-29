#include <stdio.h>
typedef struct node {
	struct node* lChild;
	struct node* rChild;
	struct node* parent;
	int key;
	int height;
}node;

node* initialTree();
node* initialNode();
int findElement(int k);
void insertItem(int k);
node* treeSearch(int k);
int removeElement(int k);
int isExternal(node* w);
int isInternal(node* w);
node*inOrderSucc(node*w);
void expandExternal(node*w);
void printTree(node*pnode);
node* reduceExternal(node*znode);
node*sibling(node*w);
int isRoot(node*w);
void searchAndFixAfterInsertion(node *w);
void searchAndFixAfterRemoval(node *w);
int isBalanced(node* w);
int updateHeight(node*pnode);
int rHeight(node*w);
node* unBalanced(node*w);
node* restructure(node*a, node*b, node*c);

node *tree;
int main() {
	char input = 0;
	int k, tmp;

	tree = initialNode();
	initialTree();

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
			printTree(tree->rChild);
			printf("\n");
			break;
		case'q':
			break;
		}
	}
}

void expandExternal(node*w) {
	w->lChild = initialNode();
	w->rChild = initialNode();

	w->lChild->parent = w;
	w->rChild->parent = w;

}

node* initialTree() {
	node* newnode;
	newnode = initialNode();
	newnode->parent = tree;
	tree->rChild = newnode;
	return newnode;
}

node* initialNode() {
	node* newnode;
	newnode = (node*)malloc(sizeof(node));
	newnode->key = -1;
	newnode->parent = NULL;
	newnode->lChild = NULL;
	newnode->rChild = NULL;
	newnode->height = 0;
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
		updateHeight(pnode);
		searchAndFixAfterInsertion(pnode);
	}
}

int findElement(int k) {
	node *pnode = treeSearch(k);
	return pnode->key;
}
node* treeSearch(int k) {
	node*pnode = tree->rChild;
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

void printTree(node*pnode) {
	if (isExternal(pnode)) {
		return;
	}
	printf(" %d", pnode->key);
	printTree(pnode->lChild);
	printTree(pnode->rChild);
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


int removeElement(int k) {
	node* wnode = treeSearch(k);
	node* ynode, *znode, *zsnode;
	int x;
	x = wnode->key;

	//k 없음
	if (isExternal(wnode)) {
		return wnode->key;
	}

	znode = wnode->lChild;
	if (isInternal(znode)) {
		znode = wnode->rChild;
	}
	if (isExternal(znode)) {
		zsnode = reduceExternal(znode);
	}
	else {
		ynode = inOrderSucc(wnode);
		znode = ynode->lChild;
		wnode->key = ynode->key;
		zsnode = reduceExternal(znode);
	}

	searchAndFixAfterRemoval(zsnode->parent);
	return x;
}

node* reduceExternal(node*znode) {
	//znode - empty!!!
	node*wnode = znode->parent;
	node*zsibling = sibling(znode);
	node*gnode = wnode->parent;
	zsibling->parent = wnode->parent;

	if (isRoot(wnode)) {
		tree->rChild= zsibling;
	}
	else {
		if (gnode->lChild == wnode) {
			gnode->lChild = zsibling;
		}
		else {
			gnode->rChild = zsibling;
		}
	}
	updateHeight(znode);
	free(znode);
	free(wnode);
	return zsibling;
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

void searchAndFixAfterInsertion(node *w) {
	node*z = unBalanced(w);
	node*y, *x;

	if (z == NULL) {				//균형을 이룬다
		return;
	}
	//y 선정
	if (z->rChild->height > z->lChild->height) {
		y = z->rChild;
	}
	else {
		y = z->lChild;
	}

	//x 선정
	if (y->rChild->height > y->lChild->height) {
		x = y->rChild;
	}
	else {
		x = y->lChild;
	}
	restructure(x, y, z);
}

void searchAndFixAfterRemoval(node *w) {
	node*z;
	node*y, *x;

	while ((z = unBalanced(w)) != NULL) {
		//y 선정
		if (z->rChild->height > z->lChild->height) {
			y = z->rChild;
		}
		else {
			y = z->lChild;
		}

		//x 선정
		if (y->rChild->height > y->lChild->height) {
			x = y->rChild;
		}
		else {
			x = y->lChild;
		}
		z = restructure(x, y, z)->parent;
	}
}

node* unBalanced(node*w) {
	if (w == tree) {
		return NULL;
	}
	if (isBalanced(w)) {		//균형을 이룸
		w = w->parent;
		unBalanced(w);
	}
	else
		return w;
}
int isBalanced(node*w) {
	int lh = w->lChild->height;
	int rh = w->rChild->height;
	if (lh > rh&&lh - rh >= 2) {
		return 0;
	}
	else if (lh < rh&&rh - lh >= 2) {
		return 0;
	}
	else return 1;
}

int updateHeight(node*pnode) {
	int h;
	while (1) {
		h = rHeight(pnode);
		if (h != pnode->height) {
			pnode->height = h;
		}
		if (isRoot(pnode)) {
			return 0;
		}
		pnode = pnode->parent;
	}
	return 1;
}

int rHeight(node*w) {
	int r = 0, l = 0;
	if (isExternal(w)) {
		return 0;
	}
	r = 1 + rHeight(w->rChild);
	l = 1 + rHeight(w->lChild);
	if (r < l)return l;
	else return r;
}
node* restructure(node*x, node*y, node*z) {
	node**Ts;
	node*a, *b, *c;
	int i = 0;
	Ts = (node**)malloc(sizeof(node*) * 4);
	if (z->rChild == y) {
		a = z;
		Ts[i++] = a->lChild;
		if (y->rChild == x) {		//single rotation1
			b = y;
			c = x;
			Ts[i++] = b->lChild;
			Ts[i++] = c->lChild;
			Ts[i++] = c->rChild;
		}
		else {						//double rotation1
			c = y;
			b = x;
			Ts[i++] = b->lChild;
			Ts[i++] = b->rChild;
			Ts[i++] = c->rChild;
		}
	}
	else {
		c = z;
		if (y->lChild == x) {		//single rotation2
			b = y;
			a = x;
			Ts[i++] = a->lChild;
			Ts[i++] = a->rChild;
			Ts[i++] = b->rChild;
		}
		else {						//double rotation2
			a = y;
			b = x;
			Ts[i++] = a->lChild;
			Ts[i++] = b->lChild;
			Ts[i++] = b->rChild;
		}
		Ts[i++] = c->rChild;
	}

	b->parent = z->parent;
	if (!isRoot(z)) {
		if (z->parent->lChild == z) {
			z->parent->lChild = b;
		}
		else {
			z->parent->rChild = b;
		}
	}
	else {
		z->parent->rChild = b;
	}
	i = 0;
	a->parent = b;
	b->lChild = a;

	a->lChild = Ts[i];
	Ts[i]->parent = a;
	i++;

	a->rChild = Ts[i];
	Ts[i]->parent = a;
	i++;

	c->parent = b;
	b->rChild = c;

	c->lChild = Ts[i];
	Ts[i]->parent = c;
	i++;

	c->rChild = Ts[i];
	Ts[i]->parent = c;

	updateHeight(a);
	updateHeight(c);

	return b;
}

int isRoot(node*w) {
	if (w->parent == tree)
		return 1;
	return 0;
}