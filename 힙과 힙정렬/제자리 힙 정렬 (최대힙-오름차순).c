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

	//무순 리스트 H 생성
	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}

	//제자리 힙 정렬
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

	//1기: 최대힙 정렬 (상향식 - 재귀)
	rBuildHeap(i);

	//2기: 오름차순 정렬
	while (n >= 1) {
		tmp = H[n];
		H[n] = H[1];
		H[1] = tmp;

		n--;					//뒤부터 큰 순으로 정렬된다.

		downHeap(1);
	}
	n = N;
}

void downHeap(int i) {
	//i는 현재 인덱스
	//최대힙 생성
	int max, tmp;
	if (i * 2 <= n) {				//왼쪽 자식 존재
		max = i * 2;
	}
	else {
		return;
	}
	if ((i * 2) + 1 <= n) {		//두 자식 모두 존재
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
		//i=n/2는 내부노드부터 시작함을 의미
		downHeap(i);
	}
}