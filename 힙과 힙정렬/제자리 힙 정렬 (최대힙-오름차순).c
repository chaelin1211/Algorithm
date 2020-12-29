#include<stdio.h>
#include<stdlib.h>
#define ARRAYSIZE 100
int H[ARRAYSIZE];
int n;

void inPlaceHeapSort();
void printArray();
void downHeap(int i);
void rBuildHeap(int i);
void buildHeap();

int main(void) {
	scanf("%d", &n);

	//���� ����Ʈ H ����
	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}

	//���ڸ� �� ����
	inPlaceHeapSort();

	printArray();
}

void printArray() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}

void inPlaceHeapSort() {
	int i = 1, N = n;
	int tmp;

	//1��: �ִ��� ���� (����� - ���)
	rBuildHeap(i);

	//2��: �������� ����
	while (n >= 1) {
		tmp = H[n];
		H[n] = H[1];
		H[1] = tmp;

		n--;					//�ں��� ū ������ ���ĵȴ�.

		downHeap(1);
	}
	n = N;
}

void downHeap(int i) {
	//i�� ���� �ε���
	//�ִ��� ����
	int max, tmp;
	if (i * 2 <= n) {				//���� �ڽ� ����
		max = i * 2;
	}
	else {
		return;
	}
	if ((i * 2) + 1 <= n) {		//�� �ڽ� ��� ����
		max = H[i * 2] > H[i * 2 + 1] ? i * 2: i * 2 + 1;
	}
	if (H[i] < H[max]) {
		tmp = H[i];
		H[i] = H[max];
		H[max] = tmp;
		downHeap(max);
	}
	return;
}

void rBuildHeap(int i) {
	if (i > n) return;
	rBuildHeap(i * 2);
	rBuildHeap(i * 2 + 1);
	downHeap(i);
}

void buildHeap() {
	for (int i = n / 2; i >= 1; i--) {
		//i=n/2�� ���γ����� �������� �ǹ�
		downHeap(i);
	}
}