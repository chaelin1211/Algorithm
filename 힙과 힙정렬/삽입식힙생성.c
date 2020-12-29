#include<stdio.h>
#include<stdlib.h>
int H[100];							//100�̸��� ũ���� �迭 H
int n = 0;							//�� �׸� ��
void insertItem(int key);		//Ű ���� �޼ҵ�
void upHeap(int n);				//i�� ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
int removeMax();					//�ִ����� ��Ʈ ��� ��� & ����
void downHeap(int i);			// i�� ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
void printHeap();
int main() {
	char input;						//�־����� ���
	int key;							//�Է� �޴� Ű

	while (1) {
		scanf("%c", &input);
		if (input == 'i') {
			scanf(" %d", &key);
			getchar();
			insertItem(key);
			continue;
		}

		getchar();
		if (input == 'q') {
			break;
		}
		else if (input == 'p') {
			printHeap();
		}
		else if (input == 'd') {
			printf("%d\n",removeMax());
		}
	}
}

void insertItem(int key) {
	H[++n] = key;
	upHeap(n);
	printf("0\n");
	return;
}

void upHeap(int i) {			//���
	int tmp;
	if(i/2<1){					//�θ� ��尡 �ִ��� Ȯ��
		return;
	}
	if (H[i] > H[i / 2]) {
		tmp = H[i];
		H[i] = H[i / 2];
		H[i / 2] = tmp;
		i /= 2;
	}
	else {						//���ڸ��� ã������ ����
		return;
	}
	upHeap(i);
}

int removeMax() {
	int Max = H[1];

	H[1] = H[n];				//��Ʈ ��带 ��Ʈ ����
	n--;

	downHeap(1);
	
	return Max;
}

void downHeap(int i) {		//���
	int tmp;
	int ind;						//down�Ǿ��� �ڸ� index
	if (i*2 > n) {				//�ڽ� ��尡 �ִ��� Ȯ��
		return;					//left, right �ڽ� �� ����
	}
	if (i * 2 + 1 <= n) {		//left, right �ڽ� �� ����
		ind = H[i * 2] > H[i * 2 + 1] ? i * 2 : i * 2 + 1;
	}	
	else {						//left �ڽĸ� ����
		ind = i * 2;
	}

	if (H[i] < H[ind]) {		//down ����
		tmp = H[i];
		H[i] = H[ind];
		H[ind] = tmp;
	}

	downHeap(ind);
}

void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
	return;
}