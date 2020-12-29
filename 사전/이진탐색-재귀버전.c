#include<stdio.h>
int BinarySearch(int l, int r, int k);
int rBS(int l, int r, int k);

int *arr;
int main() {
	int n, k;
	int ind;

	scanf("%d %d", &n, &k);

	arr = (int*)malloc(sizeof(int)*n);

	//정렬되어 있는 배열 입력
	for (int i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}

	ind = BinarySearch(0, n - 1, k);
	printf(" %d", ind);
}

int BinarySearch(int l, int r, int k) {
	return rBS(l, r, k);
}

int rBS(int l, int r, int k) {
	int ind = (l + r) / 2;
	if (l > r) {			//x ≤ k 를 만족하는 사전의 키 x 중 가장 큰 값의 위치(즉, 인덱스) 출력
		return r;
	}
	if (arr[ind] == k) {
		return ind;
	}
	else if (arr[ind] > k) {
		BinarySearch(l, ind - 1, k);
	}
	else {
		BinarySearch(ind + 1, r, k);
	}
}
