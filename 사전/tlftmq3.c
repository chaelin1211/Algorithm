#include<stdio.h>
int findK(int a, int b, int N);
void func(int *a, int *b, char c);
int main() {
	int a, b, N;
	int k;
	char c;

	scanf("%d %d %d", &a, &b, &N);
	getchar();

	k = findK(a, b, N);
	printf("%d", k);
}

int findK(int a, int b,int N) {
	char c;
	for (int i = 0; i < N; i++) {
		scanf("%c", &c);
		func(&a, &b, c);
	}
	return a;
}
void func(int *a, int *b, char c) {
	int m;
	m = (*a + *b) / 2;
	if (c == 'Y') {		// k >m
		*a = m + 1;
	}
	else {//{ans[i]=='N'}	//k <= m
		*b = m;
	}
}