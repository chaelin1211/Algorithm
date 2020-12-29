#include<stdio.h>
#include<stdlib.h>
int H[100];							//100미만의 크기인 배열 H
int n = 0;							//총 항목 수
void insertItem(int key);		//키 삽입 메소드
void upHeap(int n);				//i에 저장된 키를 크기에 맞는 위치로 상향 이동
int removeMax();					//최대힙의 루트 노드 출력 & 삭제
void downHeap(int i);			// i에 저장된 키를 크기에 맞는 위치로 하향 이동
void printHeap();
int main() {
	char input;						//주어지는 명령
	int key;							//입력 받는 키

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

void upHeap(int i) {			//재귀
	int tmp;
	if(i/2<1){					//부모 노드가 있는지 확인
		return;
	}
	if (H[i] > H[i / 2]) {
		tmp = H[i];
		H[i] = H[i / 2];
		H[i / 2] = tmp;
		i /= 2;
	}
	else {						//제자리를 찾았으면 종료
		return;
	}
	upHeap(i);
}

int removeMax() {
	int Max = H[1];

	H[1] = H[n];				//라스트 노드를 루트 노드로
	n--;

	downHeap(1);
	
	return Max;
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