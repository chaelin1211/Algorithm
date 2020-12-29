#include<stdio.h>
int BinarySearch(int l, int r, int k);
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

	ind = BinarySearch(0, n-1, k);
	printf(" %d", ind);
}

int BinarySearch(int l, int r, int k) {
	int ind;
	while (l <= r) {
		ind = (l + r) / 2;
		if (arr[ind] == k) {
			return ind;
		}
		else if (arr[ind] > k) {
			r = ind - 1;
			continue;
		}
		else {
			l = ind + 1;
			continue;
		}
	}
	return l;
}