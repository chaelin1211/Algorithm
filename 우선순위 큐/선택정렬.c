#include<stdio.h>
#include<stdlib.h>
void swapElements(int*p, int *q) {
	int tmp;
	tmp = *p;
	*p = *q;
	*q = tmp;
}
void selectionSort(int* arr, int N) {
	int maxIndex = 0, tmp = 0, *pmax;
	for (int *pi = arr + N-1; pi > arr; pi--) {
		pmax = pi;
		for (int *pj = arr; pj < pi; pj++) {
			if (*pmax < *pj) {
				pmax = pj;
			}
		}
		swapElements(pi, pmax);
	}
}
int main() {
	int N;
	int *arr;

	scanf("%d", &N);
	arr = (int *)malloc(sizeof(int)*N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	selectionSort(arr, N);

	for (int i = 0; i < N; i++) {
		printf(" %d", arr[i]);
	}
}