#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>

int n = 10;							//�迭 ũ��
int Limit;									//���� Limit�� ����
int Limits[4] = { 1, 100 , 500, 1000 };
char* mode;
char* modes[4] = { "deterministic1", "deterministic3", "randomized1", "randomized3" };

//mode	0	=	deterministic1
//mode	1	=	deterministic3
//mode	2	=	randomized1
//mode	3	=	randomized3

int* createArray();														//�迭 ����
void quickSort(int* A, int n);											//������ ����
void rQuickSort(int* A, int l, int r);									//��ͷ� ������
int findPivot(int* A, int l, int r);										//pivot�� ã�� �˰���
void inPlacePartition(int* A, int l, int r, int k, int*arr);		//���ڸ� �з�
void insertionSort(int *A, int n);										//���� ����
int findIndexOfMedianOfThree(int *A, int a, int b, int c);	//�߰� �� ã��
void printList(int* L);

int main() {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;		//�ñ� ������ ���� ����
	double t;
	int * A;

	A = createArray();
	printList(A);
	printf("Limit\t������1   \t������3   \t������1   \t������3\n");
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

	A = (int*)malloc(sizeof(int)*(n));			//n������ �迭 ����
	srand(time(NULL));								//�õ� ���� - ���� �ʼ��� ���� ���� �� ����

	for (int i = 0; i < n; i++) {
		A[i] = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
		//arr[i] = rand() % (max - min + 1) + min;
		//min~ max������ ���� ����
		//���� rand()���� ū ���� �ʿ��� ��츦 ���� shift ���� ������ ���ش�.
	}

	return A;
}

void quickSort(int* A, int n) {
	//----------------------------------
	//Limit���� �θ��� ũ�Ⱑ Ŭ ��
	rQuickSort(A, 0, n - 1);
	//	>> Limit���� �θ���Ʈ ũ�Ⱑ �۾����� ������ ����
	//	>> �� ���Ĵ� ���� ����
	//----------------------------------

	if (Limit > 1) {
		insertionSort(A, n);
		//Limit���� ũŰ�� �θ���Ʈ�� ũ�Ⱑ �۾����ٴ� ���� 
		//������ ������� ����Ǿ��� ���� ���� ���� ���ĵ� 
		//�迭�� ���ؼ� �� ������ ���� ���� ���� ����
	}
	return;
}
void rQuickSort(int* A, int l, int r) {			//���
	int k, arr[2];
	if (r - l >= Limit) {								//�θ���Ʈ�� ũ�Ⱑ Limit���� Ŭ�� ����
		k = findPivot(A, l, r);

		inPlacePartition(A, l, r, k, arr);			//arr[0]: pivot�� ���� ���� ����� ���� ���� �ε���
															//arr[1]: pivot�� ���� ���� ���ܵ� ���� ��

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
	//�迭�� �������� pivot �̵�

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