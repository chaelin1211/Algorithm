#include<stdio.h>
int BinarySearch(int l, int r, int k);
int rBS(int l, int r, int k);

int *arr;
int main() {
	int n, k;
	int ind;

	scanf("%d %d", &n, &k);

	arr = (int*)malloc(sizeof(int)*n);

	//���ĵǾ� �ִ� �迭 �Է�
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
	if (l > r) {			//x �� k �� �����ϴ� ������ Ű x �� ���� ū ���� ��ġ(��, �ε���) ���
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
