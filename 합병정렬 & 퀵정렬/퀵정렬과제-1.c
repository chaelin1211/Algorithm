#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>

int n = 10;							//배열 크기
int Limit;									//현재 Limit을 저장
int Limits[4] = { 1, 100 , 500, 1000 };
char* mode;
char* modes[4] = { "deterministic1", "deterministic3", "randomized1", "randomized3" };

//mode	0	=	deterministic1
//mode	1	=	deterministic3
//mode	2	=	randomized1
//mode	3	=	randomized3

int* createArray();														//배열 생성
void quickSort(int* A, int n);											//퀵정렬 수행
void rQuickSort(int* A, int l, int r);									//재귀로 퀵정렬
int findPivot(int* A, int l, int r);										//pivot을 찾는 알고리즘
void inPlacePartition(int* A, int l, int r, int k, int*arr);		//제자리 분류
void insertionSort(int *A, int n);										//삽입 정렬
int findIndexOfMedianOfThree(int *A, int a, int b, int c);	//중간 값 찾기
void printList(int* L);

int main() {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;		//시긴 측정을 위한 변수
	double t;
	int * A;

	A = createArray();
	printList(A);
	printf("Limit\t결정적1   \t결정적3   \t무작위1   \t무작위3\n");
	for (int i = 0; i < 4; i++) {
		printf("%d\t", Limit);
		for (int j = 0; j < 4; j++) {
			Limit = Limits[i];
			mode = modes[j];
			quickSort(A, n);
			printList(A);
		}
		printf("\n");
	}
}

void printList(int* L) {
	for (int i = 0; i < n; i++) {
		printf("%d ", L[i]);
	}
	printf("\n");
}

int* createArray() {
	int *A;
	int max = n, min = 1;

	A = (int*)malloc(sizeof(int)*(n));			//n길이의 배열 생성
	srand(time(NULL));								//시드 설정 - 현재 초수로 난수 기준 값 설정

	for (int i = 0; i < n; i++) {
		A[i] = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
		//arr[i] = rand() % (max - min + 1) + min;
		//min~ max까지의 난수 생성
		//기존 rand()보다 큰 값이 필요한 경우를 위해 shift 연산 수행을 해준다.
	}

	return A;
}

void quickSort(int* A, int n) {
	//----------------------------------
	//Limit보다 부리스 크기가 클 때
	rQuickSort(A, 0, n - 1);
	//	>> Limit보다 부리스트 크기가 작아질때 까지만 진행
	//	>> 그 이후는 삽입 정렬
	//----------------------------------

	if (Limit > 1) {
		insertionSort(A, n);
		//Limit보다 크키가 부리스트의 크기가 작아졌다는 것은 
		//정렬이 어느정도 진행되었을 경우라 보고 거의 정렬된 
		//배열에 대해선 더 성능이 좋은 삽입 정렬 수행
	}
	return;
}
void rQuickSort(int* A, int l, int r) {			//재귀
	int k, arr[2];
	if (r - l >= Limit) {								//부리스트의 크기가 Limit보다 클때 진행
		k = findPivot(A, l, r);

		inPlacePartition(A, l, r, k, arr);			//arr[0]: pivot과 같은 수가 저장된 범위 시작 인덱스
															//arr[1]: pivot과 같은 수가 저잔된 범위 끝

		rQuickSort(A, l, arr[0] - 1);
		rQuickSort(A, arr[1] + 1, r);
	}
}

int findPivot(int* A, int l, int r) {
	int max = r, min = l;
	int a, b, c;
	if (mode == "deterministic1") {
		return r;
	}
	else if (mode == "randomized1") {
		return ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
	}
	if (r - l == 1) {
		return l;
	}

	if (mode == "deterministic3") {
		a = l;
		b = (l + r) / 2;
		c = r;
	}
	else if (mode == "randomized3") {
		a = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
		b = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
		c = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
	}
	return findIndexOfMedianOfThree(A, a, b, c);
}


void inPlacePartition(int* A, int l, int r, int k, int*arr) {
	int tmp, p;
	int i, j;
	int a, b;
	r--;

	p = A[k];

	a = (r + l) / 2;
	b = (r + l) / 2;
	tmp = A[b];
	A[b] = A[k];
	A[k] = tmp;
	//배열의 마지막에 pivot 이동

	i = l;
	j = r;
	while (i != a || j != b) {
		while (A[i] <= p) {
			if (A[i] == p) {
				if (A[i + 1] == p) {
					a = i;
					break;
				}
				tmp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = tmp;
			}
			else i++;
		}
		while (p <= A[j]) {
			if (A[j] == p) {
				if (A[j - 1] == p) {
					b = j;
					break;
				}
				tmp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = tmp;
			}
			else j--;
		}
		tmp = A[i];
		A[i] = A[j];
		A[j] = tmp;
	}
	arr[0] = a;
	arr[1] = b;
}

void insertionSort(int *A, int n) {
	int tmp = 0, *pj;
	for (int *pi = A + 1; pi < A + n; pi++) {
		pj = pi - 1;
		tmp = *pi;
		while (tmp < *pj && pj >= A) {
			*(pj + 1) = *pj;
			//swapElements(pj + 1, pj);
			pj--;
		}
		*(pj + 1) = tmp;
	}
}

int findIndexOfMedianOfThree(int *A, int a, int b, int c) {
	int med = a;
	if (A[a] > A[b] && A[a] > A[c]) {
		if (A[b] > A[c]) {			//[a][b][c]
			med = b;
		}
		else {							//[a][c][b]
			med = c;
		}
	}

	if (A[b] > A[a] && A[b] > A[c]) {
		if (A[a] > A[c]) {			//[b][a][c]
			med = a;
		}
		else {							//[b][c][a]
			med = c;
		}
	}

	if (A[c] > A[a] && A[c] > A[b]) {
		if (A[a] > A[b]) {			//[c][a][b]
			med = a;
		}
		else {							//[c][b][a]
			med = b;
		}
	}
	return med;
}