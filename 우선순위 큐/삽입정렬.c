#include<stdio.h>
#include<stdlib.h>
void swapElements(int*p, int *q) {
	int tmp;
	tmp = *p;
	*p = *q;
	*q = tmp;
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
	int *arr;

	scanf("%d", &N);
	arr = (int *)malloc(sizeof(int)*N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	insertionSort(arr, N);

	for (int i = 0; i < N; i++) {
		printf(" %d", arr[i]);
	}
}