#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
void inPlaceQuickSort(int* L, int l, int r);
int findPivot(int*L, int l, int r);
int* inPlacePartition(int* L, int l, int r, int k);
void printList(int* L);


int n;
int main() {
	int *L; 
	srand(time(NULL));								//시드 설정 - 현재 초수로 난수 기준 값 설정

	
	scanf("%d", &n);
	L = (int*)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++) {
		scanf("%d", L+i);
	}	
	inPlaceQuickSort(L, 0, n);
	printList(L);
}
void inPlaceQuickSort(int* L, int l, int r) {
	int k;
	int* arr;
	if (l >= r) {
		return;
	}
	
	k = findPivot(L, l, r);
	
	arr = inPlacePartition(L, l, r, k);

	inPlaceQuickSort(L, l, arr[0]);
	inPlaceQuickSort(L, arr[1]+1, r);
}

int findPivot(int*L, int l, int r) {
	int k;
	k = rand() % (r - l) + l;
	return k;
}

int* inPlacePartition(int* L, int l, int r, int k) {
	int *arr, tmp, p;
	int i, j;
	arr = (int*)malloc(sizeof(int) * 2);
	
	p = L[k];

	tmp = L[r-1];
	L[r - 1] = L[k];
	L[k] = tmp;
	//배열의 마지막에 pivot 이동
	
	i = l;
	j = r - 1;
	while (i < j) {
		while (i < j && L[i] <= p) {
			i++;
		}
		while (i < j && L[j] >= p) {
			j--;
		}
		if (i < j) {
			tmp = L[i];
			L[i] = L[j];
			L[j] = tmp;
		}
	}
	arr[0] = i;
	arr[1] = j;

	if (i < r - 1) {
		tmp = L[i];
		L[i] = L[r-1];
		L[r-1] = tmp;
	}
	
	return arr;
}

void printList(int* L) {
	for (int i = 0; i < n; i++) {
		printf("%d ", L[i]);
	}
	printf("\n");
}