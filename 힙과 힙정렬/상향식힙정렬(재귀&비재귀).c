#include<stdio.h>
#include<stdlib.h>
int H[100];							//100�̸��� ũ���� �迭 H
int n = 0;							//�� �׸� ��
void rBuildHeap(i);				//��� ������� ����� �� ����
void BuildHeap(i);				//����� �� ����
void downHeap(int i);			// i�� ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
void printHeap();
int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}
	//rBuildHeap(1);			//��Ʈ���� �����ؼ� �Ʒ���
	BuildHeap(n);
	printHeap();
}
void rBuildHeap(int i) {		//���
	if (i > n) {
		return;
	}
	rBuildHeap(i * 2);		//left �ڽ�
	rBuildHeap(i * 2 + 1);	//right �ڽ�
	downHeap(i);				//���� ��Ʈ���� �� ���� 
	return;
}
void BuildHeap(int n) {
	for (int i = n / 2; i >= 1; i--) {		
		//i=n/2�� ���γ����� �������� �ǹ�
		downHeap(i);
	}
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