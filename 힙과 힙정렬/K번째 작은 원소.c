#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
int* buildList(int n, int min, int max);		//������ ������ nũ���� ����Ʈ L ���� (���� limit: min~max)
int findKthSmallest(int* L, int n, int k);	//nũ���� ����Ʈ L���� k��°�� ū �� ��ȯ
void writeList(int* L, int n);							//����Ʈ ���� �� �ٷ� ���
void buildHeap(int*L, int n);					//����Ʈ L�� ���� �� ����
void downHeap(int*L,int i, int n);			//���� i�� �Ʒ��� ������ �°� ����
int removeMin(int *L, int n);					//���� ���� ���� �� (root) ��ȯ
int main() {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;		//�ñ� ������ ���� ����
	double t;
	int *L, *copyL, n, e;
	int *output;										//findKthSmallList ����� ���� ���
	int karray[4] = { 1, 100, 99900, 99999 };
	/*-------------------------------------------------------
	mini test runs	
	>> n =10		
	>> k = 1,2,3
	>> min = 1
	>> max = 100
	-------------------------------------------------------*/
	n = 10;
	output = (int*)malloc(sizeof(int) * 3);
	L = buildList(n, 1, 100);

	writeList(L,n);

	//����Ʈ L�� �ʱ� ���� ���¸� �����ϴ� �迭 ���� �� ����
	copyL = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		copyL[i] = L[i];
	}

	for (int k = 1; k <= 3; k++) {
		output[k] = findKthSmallest(L, n, k);
		 //������ ��ȯ�� L�� �ʱ� ������ ���� ����Ʈ�� ��ȯ
		for (int i = 1; i <= n; i++) {
			L[i] = copyL[i];
		}
	}

	writeList(output,3);
	/*-------------------------------------------------------
	main test runs
	>> n = 100000		
	>> k = 1, 100, 99900, 99999
	>> min = 1
	>> max = 1000000
	-------------------------------------------------------*/
	n = 100000;
	output = (int*)malloc(sizeof(int) * 4);
	L = buildList(n, 1, 1000000);

	//����Ʈ L�� �ʱ� ���� ���¸� �����ϴ� �迭 ���� �� ����
	copyL = (int*)malloc(sizeof(int) * (n+1));
	for (int i = 1; i <= n; i++) {
		copyL[i] = L[i];
	}

	// karray[4] = { 1, 100, 99900, 99999 };
	for (int k = 0; k <= 3; k++) {
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);

		/////////�ð��� ������ �۾�////////
		e = findKthSmallest(L, n, karray[k]);
		/////////////////////////////////////

		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;	//���� ������ ����ð� ���
		t = (double)diff.QuadPart / (double)ticksPerSec.QuadPart;
		t *= 1000;														//ms�� ��ȯ
		printf("%d\t%fms\n", e, t);

		//������ ��ȯ�� L�� �ʱ� ������ ���� ����Ʈ�� ��ȯ
		for (int i = 1; i <= n; i++) {			
			L[i] = copyL[i];				
		}
	}

}
int* buildList(int n, int min, int max) {
	int *arr;
	int randT;
	arr = (int*)malloc(sizeof(int)*(n+1));		//n+1������ �迭 ����
	srand(time(NULL));								//�õ� ���� - ���� �ʼ��� ���� ���� �� ����
	
	for (int i = 1; i <= n; i++) {
		arr[i] = ((((long)rand() << 15) | rand()) % (max - min + 1) ) + min;
		//arr[i] = rand()* % (max - min + 1) + min;
		//min~ max������ ���� ����
		//���� rand()���� ū ���� �ʿ��� ��츦 ���� shift ���� ������ ���ش�.
	}

	return arr;
}

void downHeap(int *L, int i, int n) {		//���
	int ind, tmp;					//ind: ���� i ���� ���� �ڽ� ����� �ε����� ����

	if (i * 2 > n) {					//�ش� ����� �ڽ� ��尡 ������ ����
		return;
	}

	if (i * 2 + 1 > n) {			//�ش� ����� �ڽ� ��尡 left�� ����
		ind = i * 2;					
	}
	else {
		ind = L[i * 2] < L[i * 2 + 1] ? i * 2 : i * 2 + 1;	//���� ���� �ڽ� ����� index ����
	}
	if (L[i] > L[ind]) {			//���� i���� �ڽ� ��� �� ���� �Ͱ� swap
		tmp = L[i];
		L[i] = L[ind];
		L[ind] = tmp;
	}
	downHeap(L, ind, n);
}

void buildHeap(int*L,int n) {	
	for (int i = n / 2; i >= 1; i--) {	//���� ����̸� downHeap�� ���� ����
		downHeap(L, i, n);	
	}
}

int removeMin(int *L, int n) {
	int min = L[1];
	L[1] = L[n];
	n--;
	downHeap(L, 1, n);
	return min;
}

int findKthSmallest(int* L, int n, int k) {
	int min;

	//1. ����Ʈ L�� ����Ʈ���� ���� HeapSort()		-O(n)
	buildHeap(L, n);

	//2. removeMin()�� k�� ����								-O(klogn)
	for (int i = 0; i < k; i++) {
		min = removeMin(L, n);			//removeMin�� big-O�� O(logn)
	}

	return min;
}

void writeList(int *L,int n) {
	for (int i=1; i <= n;i++) {
		printf("%d ", L[i]);
	}
	printf("\n");
}