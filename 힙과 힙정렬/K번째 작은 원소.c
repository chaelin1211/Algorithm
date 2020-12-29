#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
int* buildList(int n, int min, int max);		//난수로 형성된 n크기의 리스트 L 생성 (난수 limit: min~max)
int findKthSmallest(int* L, int n, int k);	//n크기의 리스트 L에서 k번째로 큰 수 반환
void writeList(int* L, int n);							//리스트 내용 한 줄로 출력
void buildHeap(int*L, int n);					//리스트 L을 통해 힙 생성
void downHeap(int*L,int i, int n);			//힙의 i를 아래로 순서에 맞게 정렬
int removeMin(int *L, int n);					//힙의 가장 작은 수 (root) 반환
int main() {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;		//시긴 측정을 위한 변수
	double t;
	int *L, *copyL, n, e;
	int *output;										//findKthSmallList 결과값 저장 행렬
	int karray[4] = { 1, 100, 99900, 99999 };
	/*-------------------------------------------------------
	mini test runs	
	>> n =10		
	>> k = 1,2,3
	>> min = 1
	>> max = 100
	-------------------------------------------------------*/
	n = 10;
	output = (int*)malloc(sizeof(int) * 3);
	L = buildList(n, 1, 100);

	writeList(L,n);

	//리스트 L의 초기 무순 상태를 저장하는 배열 생성 및 복사
	copyL = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		copyL[i] = L[i];
	}

	for (int k = 1; k <= 3; k++) {
		output[k] = findKthSmallest(L, n, k);
		 //힙으로 변환된 L을 초기 상태의 무순 리스트로 변환
		for (int i = 1; i <= n; i++) {
			L[i] = copyL[i];
		}
	}

	writeList(output,3);
	/*-------------------------------------------------------
	main test runs
	>> n = 100000		
	>> k = 1, 100, 99900, 99999
	>> min = 1
	>> max = 1000000
	-------------------------------------------------------*/
	n = 100000;
	output = (int*)malloc(sizeof(int) * 4);
	L = buildList(n, 1, 1000000);

	//리스트 L의 초기 무순 상태를 저장하는 배열 생성 및 복사
	copyL = (int*)malloc(sizeof(int) * (n+1));
	for (int i = 1; i <= n; i++) {
		copyL[i] = L[i];
	}

	// karray[4] = { 1, 100, 99900, 99999 };
	for (int k = 0; k <= 3; k++) {
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);

		/////////시간을 측정할 작업////////
		e = findKthSmallest(L, n, karray[k]);
		/////////////////////////////////////

		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;	//측정 값으로 실행시간 계산
		t = (double)diff.QuadPart / (double)ticksPerSec.QuadPart;
		t *= 1000;														//ms로 변환
		printf("%d\t%fms\n", e, t);

		//힙으로 변환된 L을 초기 상태의 무순 리스트로 변환
		for (int i = 1; i <= n; i++) {			
			L[i] = copyL[i];				
		}
	}

}
int* buildList(int n, int min, int max) {
	int *arr;
	int randT;
	arr = (int*)malloc(sizeof(int)*(n+1));		//n+1길이의 배열 생성
	srand(time(NULL));								//시드 설정 - 현재 초수로 난수 기준 값 설정
	
	for (int i = 1; i <= n; i++) {
		arr[i] = ((((long)rand() << 15) | rand()) % (max - min + 1) ) + min;
		//arr[i] = rand()* % (max - min + 1) + min;
		//min~ max까지의 난수 생성
		//기존 rand()보다 큰 값이 필요한 경우를 위해 shift 연산 수행을 해준다.
	}

	return arr;
}

void downHeap(int *L, int i, int n) {		//재귀
	int ind, tmp;					//ind: 현재 i 노드와 비교할 자식 노드의 인덱스를 저장

	if (i * 2 > n) {					//해당 노드의 자식 노드가 없으면 종료
		return;
	}

	if (i * 2 + 1 > n) {			//해당 노드의 자식 노드가 left만 존재
		ind = i * 2;					
	}
	else {
		ind = L[i * 2] < L[i * 2 + 1] ? i * 2 : i * 2 + 1;	//값이 작은 자식 노드의 index 저장
	}
	if (L[i] > L[ind]) {			//현재 i노드와 자식 노드 중 작은 것과 swap
		tmp = L[i];
		L[i] = L[ind];
		L[ind] = tmp;
	}
	downHeap(L, ind, n);
}

void buildHeap(int*L,int n) {	
	for (int i = n / 2; i >= 1; i--) {	//내부 노드이면 downHeap을 통해 정렬
		downHeap(L, i, n);	
	}
}

int removeMin(int *L, int n) {
	int min = L[1];
	L[1] = L[n];
	n--;
	downHeap(L, 1, n);
	return min;
}

int findKthSmallest(int* L, int n, int k) {
	int min;

	//1. 리스트 L을 이진트리로 보고 HeapSort()		-O(n)
	buildHeap(L, n);

	//2. removeMin()을 k번 수행								-O(klogn)
	for (int i = 0; i < k; i++) {
		min = removeMin(L, n);			//removeMin의 big-O는 O(logn)
	}

	return min;
}

void writeList(int *L,int n) {
	for (int i=1; i <= n;i++) {
		printf("%d ", L[i]);
	}
	printf("\n");
}