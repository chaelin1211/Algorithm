#include<stdio.h>
#include<stdlib.h>
int H[100];							//100미만의 크기인 배열 H
int n = 0;							//총 항목 수
void rBuildHeap(i);				//재귀 방식으로 상향식 힙 생성
void BuildHeap(i);				//상향식 힙 생성
void downHeap(int i);			// i에 저장된 키를 크기에 맞는 위치로 하향 이동
void printHeap();
int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}
	//rBuildHeap(1);			//루트부터 시작해서 아래로
	BuildHeap(n);
	printHeap();
}
void rBuildHeap(int i) {		//재귀
	if (i > n) {
		return;
	}
	rBuildHeap(i * 2);		//left 자식
	rBuildHeap(i * 2 + 1);	//right 자식
	downHeap(i);				//현재 부트리의 힙 생성 
	return;
}
void BuildHeap(int n) {
	for (int i = n / 2; i >= 1; i--) {		
		//i=n/2는 내부노드부터 시작함을 의미
		downHeap(i);
	}
}
void downHeap(int i) {		//재귀
	int tmp;
	int ind;						//down되어질 자리 index
	if (i*2 > n) {				//자식 노드가 있는지 확인
		return;					//left, right 자식 다 없음
	}
	if (i * 2 + 1 <= n) {		//left, right 자식 다 있음
		ind = H[i * 2] > H[i * 2 + 1] ? i * 2 : i * 2 + 1;
	}	
	else {						//left 자식만 있음
		ind = i * 2;
	}

	if (H[i] < H[ind]) {		//down 수행
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