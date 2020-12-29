#include <stdio.h>

void initBucketArray(int* arr);
int insertElement(int x);
int searchElement(int x);
int findBucket(int x);
void print(int*arr);

int M, q;
int * arr;
int main() {
	char c = 'p';
	int x, n, tmp;
	scanf("%d %d %d", &M, &n, &q);
	getchar();
	arr = (int*)malloc(sizeof(int)*M);

	initBucketArray(arr);

	while (1) {
		scanf("%c", &c);
		getchar(); 
		if (c == 'e') {
			print(arr);
			break;
		}
		if (c == 'p') {
			print(arr);
			continue;
		}

		scanf("%d", &x);
		getchar();
		if(c == 'i' && n>0){
			n--;
			printf("%d\n", insertElement(x));
		}
		else if(c=='s'){
			tmp = searchElement(x);
			printf("%d", tmp);
			if(tmp!=-1)
				printf(" %d", arr[tmp]);
			printf("\n");
		}
	}
}

void initBucketArray(int* arr) {
	for (int i = 0; i < M; i++) {
		arr[i] = 0;
	}
}


int insertElement(int x) {
	int b = findBucket(x);
	while (arr[b] != 0) {
		printf("C");
		b += findBucket2(x);
		if (b >= M) {
			b %= M;
		}
	}
	arr[b] = x;
	return b;
}

int searchElement(int x) {
	int j = findBucket(x);
	while (arr[j] != 0) {
		if (arr[j] == x) {
			return j;
		}
		else {
			j += findBucket2(x);
			if (j >= M) {
				j %= M;
			}
		}
	}
	return -1;
}

void print(int*arr) {
	for (int i = 0; i < M; i++) {
		printf(" %d", arr[i]);
	}
	printf("\n");
}
int findBucket(int x) {
	return x % M;
}

int findBucket2(int x) {
	return q - (x%q);
}