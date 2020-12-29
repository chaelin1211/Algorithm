#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <Windows.h>
void swapElements(int*p, int *q) {
	int tmp;
	tmp = *p;
	*p = *q;
	*q = tmp;
}

void reverse(int* arr, int N) {
	int tmp = 0, *pmax;
	for (int *pi = arr; pi < arr + N - 1; pi++) {
		pmax = pi;
		for (int *pj = pi + 1; pj < arr + N; pj++) {
			if (*pmax > *pj) {
				pmax = pj;
			}
		}
		tmp = *pi;
		*pi = *pmax;
		*pmax = tmp;
	}
}
void selectionSort(int* arr, int N) {
	int maxIndex = 0, tmp = 0, *pmax;
	for (int *pi = arr + N - 1; pi > arr; pi--) {
		pmax = pi;
		for (int *pj = arr; pj < pi; pj++) {
			if (*pmax < *pj) {
				pmax = pj;
			}
		}
		//swapElements(pi, pmax);
		tmp = *pi;
		*pi = *pmax;
		*pmax = tmp;
	}
}
void insertionSort(int* arr, int N) {
	int tmp = 0, *pj;
	for (int *pi = arr + 1; pi < arr + N; pi++) {
		pj = pi - 1;
		tmp = *pi;
		while (tmp < *pj && pj >= arr) {
			*(pj + 1) = *pj;
			//swapElements(pj + 1, pj);
			pj--;
		}
		*(pj + 1) = tmp;
	}
}
int main() {
	int N, j;
	int *A, *B;
	srand(time(NULL));
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	scanf("%d", &N);
	A = (int *)malloc(sizeof(int)*N);
	B = (int *)malloc(sizeof(int)*N);

	for (int i = 0; i < N; i++) {
		A[i] = ((((long)rand() << 15) | rand()) % 100000) + 1;
		B[i] = A[i];
	}

	//������ �迭
	printf("A\n");
	//���� ���� ����ð�
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	///////////////////////////////////////////////
	selectionSort(B, N);
	///////////////////////////////////////////////
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("��������:%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);

	//���� ���� ����ð�
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	///////////////////////////////////////////////
	insertionSort(A, N);
	///////////////////////////////////////////////
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("��������:%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);

	//���ĵ� ����
	printf("B\n");
	//���� ���� ����ð�
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	///////////////////////////////////////////////
	selectionSort(B, N);
	///////////////////////////////////////////////
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("��������:%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);

	//���� ���� ����ð�
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	///////////////////////////////////////////////
	insertionSort(A, N);
	///////////////////////////////////////////////
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("��������:%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);

	//������ ����
	reverse(A, N);
	reverse(B, N);

	printf("C\n");
	//���� ���� ����ð�
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	///////////////////////////////////////////////
	selectionSort(B, N);
	///////////////////////////////////////////////
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("��������:%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);

	//���� ���� ����ð�
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	///////////////////////////////////////////////
	insertionSort(A, N);
	///////////////////////////////////////////////
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("��������:%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);


}