#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>

int n = 10000;								//배열 크기

int Limit;									//현재 Limit을 저장
int Limits[4] = { 1, 100 , 500, 1000 };
//Limit 0 = 1
//Limit 1 = 100
//Limit 2 = 500
//Limit 3 = 1000

char* mode;								//현재 mode
char* modes[4] = { "deterministic1", "deterministic3", "randomized1", "randomized3" };
//mode	0	=	deterministic1
//mode	1	=	deterministic3
//mode	2	=	randomized1
//mode	3	=	randomized3

int* createArray();														//배열 생성 함수
void quickSort(int* A, int n);											//퀵정렬 수행 함수
void rQuickSort(int* A, int l, int r);									//재귀로 퀵정렬
int findPivot(int* A, int l, int r);										//pivot을 찾는 알고리즘
void inPlacePartition(int* A, int l, int r, int k, int*arr);		//제자리 분류
void insertionSort(int *A, int n);										//삽입 정렬
int findIndexOfMedianOfThree(int *A, int a, int b, int c);	//A[a], A[b], A[c] 중 중간값의 인덱스 리턴
void copyArray(int*A, int* A2);										//A->A2로 배열 복사

int main() {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;		//시긴 측정을 위한 변수
	double t;
	int * A;											//초기 배열
	int * A2;											//복사 배열 

	srand(time(NULL));							//시드 설정 - 현재 초수로 난수 기준 값 설정

	A = createArray();
	A2 = (int *)malloc(sizeof(int)*n);

	printf("Limit\t결정적1   \t결정적3   \t무작위1   \t무작위3\n");
	for (int i = 0; i < 4; i++) {
		//Limit 0 = 1
		//Limit 1 = 100
		//Limit 2 = 500
		//Limit 3 = 1000
		Limit = Limits[i];
		printf("%d\t", Limit);
		for (int j = 0; j < 4; j++) {
			//mode	0	=	deterministic1
			//mode	1	=	deterministic3
			//mode	2	=	randomized1
			//mode	3	=	randomized3
			mode = modes[j];

			QueryPerformanceFrequency(&ticksPerSec);
			QueryPerformanceCounter(&start);

			copyArray(A, A2);
			/////////시간을 측정할 작업////////
			quickSort(A2, n);
			/////////////////////////////////////

			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;	//측정 값으로 실행시간 계산
			t = (double)diff.QuadPart / (double)ticksPerSec.QuadPart;
			t *= 1000;														//ms로 변환
			printf("%fms\t", t);
		}
		printf("\n");
	}
}

int* createArray() {
	int *A;
	int max = n, min = 1;

	A = (int*)malloc(sizeof(int)*(n));			//n길이의 배열 생성

	for (int i = 0; i < n; i++) {
		A[i] = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
		//arr[i] = rand() % (max - min + 1) + min;
		//min~ max까지의 난수 생성
		//기존 rand()보다 큰 값이 필요한 경우를 위해 shift 연산 수행을 해준다.
	}

	return A;
}

void copyArray(int*A, int* A2) {
	for (int i = 0; i < n; i++) {
		A2[i] = A[i];
	}
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
void rQuickSort(int* A, int l, int r) {
	int k, arr[2];
	if (r - l >= Limit) {								//부리스트의 크기가 Limit보다 클때 진행
		k = findPivot(A, l, r);

		inPlacePartition(A, l, r, k, arr);			//arr[0]: pivot과 같은 수가 저장된 범위 시작 인덱스
															//arr[1]: pivot과 같은 수가 저장된 범위 끝

		// A[l]			~	A[arr[0]-1]		: LT
		//A[arr[0]]		~	A[arr[1]]			: EQ
		//A[arr[1]+1]	~	A[r]					: GT

		//-----------재귀 수행----------------
		rQuickSort(A, l, arr[0] - 1);				//LT
		rQuickSort(A, arr[1] + 1, r);				//GT
	}
}

int findPivot(int* A, int l, int r) {
	int max = r, min = l;
	int a, b, c;
	if (mode == "deterministic1") {
		//고정된 인덱스 1개 택
		return r;
	}
	else if (mode == "randomized1") {
		//전체 인덱스 중에서 임의의 인덱스 1개 택
		return ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
	}
	if (r - l == 1) {
		return l;
	}

	if (mode == "deterministic3") {
		//고정된 인덱스 3개 택 (처음, 중앙, 끝) - 이 중 중간값 1개 택
		//키값 비교
		a = l;
		b = (l + r) / 2;
		c = r;
	}
	else if (mode == "randomized3") {
		//전체 인덱스 중에서 임의의 인덱스 3개 택 - 이 중 중앙값 이용
		//키값 비교
		a = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
		b = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
		c = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
	}
	return findIndexOfMedianOfThree(A, a, b, c);
}


void inPlacePartition(int* A, int l, int r, int k, int*arr) {
	//LT, EQ, GT 분류
	//EQ의 시작 인덱스, 종료 인덱스를 arr 배열에 저장

	int tmp, p;
	int i, j;
	int a;							//EQ 시작 인덱스
	int c = 0;					//EQ의 크기

	p = A[k];					//피봇

	a = (r + l) / 2;

	//swap(a, k)---------------------
	//a - 배열의 중앙 인덱스
	//k - 현재 pivot의 인덱스
	//		>>배열의 중간에 pivot 이동
	tmp = A[a];
	A[a] = A[k];
	A[k] = tmp;
	//------------------------------

	i = l;
	j = r;
	// l---------a~~a+c------r
	// i                                      j

	//EQ는 가상으로 구분되어 있고 LT와 GT에서 pivot과 같은 수가 존재하면 
	//LT 또는 GT의 크기를 줄이고 EQ에 추가

	//LT에 pivot보다 큰 수가 존재하거나 GT에 pivot보다 작은 수가 존재하면
	//서로 교체

	while (i < j) {
		while (A[i] <= p && i < j &&i < a) {
			if (A[i] == p) {
				//A[i]가 pivot과 같을 때 EQ로 이동
				c++;								//EQ의 크기 증가

				// LT의 크기를 줄이기 위해 a를 앞으로 전진
				tmp = A[a];
				A[a] = A[a - 1];
				A[a - 1] = tmp;

				tmp = A[a];
				A[a] = A[i];
				A[i] = tmp;
				a--;
			}
			else {
				i++;
			}
		}

		while (p <= A[j] && i < j && a + c < j) {
			if (A[j] == p) {
				//A[j]가 pivot과 같을 때 EQ로 이동
				c++;								//EQ의 크기 증가

				//EQ의 뒤에 A[j] 저장
				tmp = A[j];
				A[j] = A[a + c];
				A[a + c] = tmp;
			}
			else {
				j--;
			}
		}

		//i와 j가 EQ에 닿으면 종료 - a~a+c인덱스 내에는 다른 수가 존재하지 않음
		if (i == a && a + c == j)
			break;

		if (i < j) {
			// i나 j가 먼저 EQ에 도달한 경우
			// EQ의 위치를 조정해야한다.

			// --------j가 a+c와 같고 A[i]가 pivot보다 큰 경우 (c>0)------------------
			// 1) A[i]는 먼저 EQ에 도달한 A[j] 와 swap 
			// 2) EQ의 크기를 저장한 c의 크기 조정 -> c--
			// 3) pivot과 같아진 A[i]는 반복문의 수행을 계속하면 다시 EQ에 속하게 된다.

			// --------j가 a+c와 같고 A[i]가 pivot보다 큰 경우 (c=0)------------------
			// 1) A[i]는 먼저 EQ에 도달한 A[j] 와 swap 
			// 2) a의 인덱스를 i로 바꾸어 준다. -> EQ 자체가 이동됨
			// 3) 반복문의 수행을 계속하면 EQ는 바른 자리로 이동된다.

			//i가 a이고 A[j]가 Pivot보다 작은 경우도 위와 유사한 알고리즘으로 진행

			if (c == 0) {
				if (i == a) {
					a = j;
				}
				else if (j == a) {
					a = i;
				}
			}
			else {
				if (i == a) {
					a++;
					c--;
				}
				else if (j == a + c) {
					c--;
				}
			}
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
	}
	arr[0] = a;
	arr[1] = a + c;
}


void insertionSort(int *A, int n) {
	//오름차순으로 정렬하는 삽입정렬 알고리즘
	int tmp = 0, *pj;
	for (int *pi = A + 1; pi < A + n; pi++) {
		pj = pi - 1;
		tmp = *pi;
		while (tmp < *pj && pj >= A) {
			*(pj + 1) = *pj;
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