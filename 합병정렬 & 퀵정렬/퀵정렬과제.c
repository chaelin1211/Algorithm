#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>

int n = 10000;								//�迭 ũ��

int Limit;									//���� Limit�� ����
int Limits[4] = { 1, 100 , 500, 1000 };
//Limit 0 = 1
//Limit 1 = 100
//Limit 2 = 500
//Limit 3 = 1000

char* mode;								//���� mode
char* modes[4] = { "deterministic1", "deterministic3", "randomized1", "randomized3" };
//mode	0	=	deterministic1
//mode	1	=	deterministic3
//mode	2	=	randomized1
//mode	3	=	randomized3

int* createArray();														//�迭 ���� �Լ�
void quickSort(int* A, int n);											//������ ���� �Լ�
void rQuickSort(int* A, int l, int r);									//��ͷ� ������
int findPivot(int* A, int l, int r);										//pivot�� ã�� �˰���
void inPlacePartition(int* A, int l, int r, int k, int*arr);		//���ڸ� �з�
void insertionSort(int *A, int n);										//���� ����
int findIndexOfMedianOfThree(int *A, int a, int b, int c);	//A[a], A[b], A[c] �� �߰����� �ε��� ����
void copyArray(int*A, int* A2);										//A->A2�� �迭 ����

int main() {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;		//�ñ� ������ ���� ����
	double t;
	int * A;											//�ʱ� �迭
	int * A2;											//���� �迭 

	srand(time(NULL));							//�õ� ���� - ���� �ʼ��� ���� ���� �� ����

	A = createArray();
	A2 = (int *)malloc(sizeof(int)*n);

	printf("Limit\t������1   \t������3   \t������1   \t������3\n");
	for (int i = 0; i < 4; i++) {
		//Limit 0 = 1
		//Limit 1 = 100
		//Limit 2 = 500
		//Limit 3 = 1000
		Limit = Limits[i];
		printf("%d\t", Limit);
		for (int j = 0; j < 4; j++) {
			//mode	0	=	deterministic1
			//mode	1	=	deterministic3
			//mode	2	=	randomized1
			//mode	3	=	randomized3
			mode = modes[j];

			QueryPerformanceFrequency(&ticksPerSec);
			QueryPerformanceCounter(&start);

			copyArray(A, A2);
			/////////�ð��� ������ �۾�////////
			quickSort(A2, n);
			/////////////////////////////////////

			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;	//���� ������ ����ð� ���
			t = (double)diff.QuadPart / (double)ticksPerSec.QuadPart;
			t *= 1000;														//ms�� ��ȯ
			printf("%fms\t", t);
		}
		printf("\n");
	}
}

int* createArray() {
	int *A;
	int max = n, min = 1;

	A = (int*)malloc(sizeof(int)*(n));			//n������ �迭 ����

	for (int i = 0; i < n; i++) {
		A[i] = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
		//arr[i] = rand() % (max - min + 1) + min;
		//min~ max������ ���� ����
		//���� rand()���� ū ���� �ʿ��� ��츦 ���� shift ���� ������ ���ش�.
	}

	return A;
}

void copyArray(int*A, int* A2) {
	for (int i = 0; i < n; i++) {
		A2[i] = A[i];
	}
}

void quickSort(int* A, int n) {
	//----------------------------------
	//Limit���� �θ��� ũ�Ⱑ Ŭ ��
	rQuickSort(A, 0, n - 1);
	//	>> Limit���� �θ���Ʈ ũ�Ⱑ �۾����� ������ ����
	//	>> �� ���Ĵ� ���� ����
	//----------------------------------

	if (Limit > 1) {
		insertionSort(A, n);
		//Limit���� ũŰ�� �θ���Ʈ�� ũ�Ⱑ �۾����ٴ� ���� 
		//������ ������� ����Ǿ��� ���� ���� ���� ���ĵ� 
		//�迭�� ���ؼ� �� ������ ���� ���� ���� ����
	}
	return;
}
void rQuickSort(int* A, int l, int r) {
	int k, arr[2];
	if (r - l >= Limit) {								//�θ���Ʈ�� ũ�Ⱑ Limit���� Ŭ�� ����
		k = findPivot(A, l, r);

		inPlacePartition(A, l, r, k, arr);			//arr[0]: pivot�� ���� ���� ����� ���� ���� �ε���
															//arr[1]: pivot�� ���� ���� ����� ���� ��

		// A[l]			~	A[arr[0]-1]		: LT
		//A[arr[0]]		~	A[arr[1]]			: EQ
		//A[arr[1]+1]	~	A[r]					: GT

		//-----------��� ����----------------
		rQuickSort(A, l, arr[0] - 1);				//LT
		rQuickSort(A, arr[1] + 1, r);				//GT
	}
}

int findPivot(int* A, int l, int r) {
	int max = r, min = l;
	int a, b, c;
	if (mode == "deterministic1") {
		//������ �ε��� 1�� ��
		return r;
	}
	else if (mode == "randomized1") {
		//��ü �ε��� �߿��� ������ �ε��� 1�� ��
		return ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
	}
	if (r - l == 1) {
		return l;
	}

	if (mode == "deterministic3") {
		//������ �ε��� 3�� �� (ó��, �߾�, ��) - �� �� �߰��� 1�� ��
		//Ű�� ��
		a = l;
		b = (l + r) / 2;
		c = r;
	}
	else if (mode == "randomized3") {
		//��ü �ε��� �߿��� ������ �ε��� 3�� �� - �� �� �߾Ӱ� �̿�
		//Ű�� ��
		a = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
		b = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
		c = ((((long)rand() << 15) | rand()) % (max - min + 1)) + min;
	}
	return findIndexOfMedianOfThree(A, a, b, c);
}


void inPlacePartition(int* A, int l, int r, int k, int*arr) {
	//LT, EQ, GT �з�
	//EQ�� ���� �ε���, ���� �ε����� arr �迭�� ����

	int tmp, p;
	int i, j;
	int a;							//EQ ���� �ε���
	int c = 0;					//EQ�� ũ��

	p = A[k];					//�Ǻ�

	a = (r + l) / 2;

	//swap(a, k)---------------------
	//a - �迭�� �߾� �ε���
	//k - ���� pivot�� �ε���
	//		>>�迭�� �߰��� pivot �̵�
	tmp = A[a];
	A[a] = A[k];
	A[k] = tmp;
	//------------------------------

	i = l;
	j = r;
	// l---------a~~a+c------r
	// i                                      j

	//EQ�� �������� ���еǾ� �ְ� LT�� GT���� pivot�� ���� ���� �����ϸ� 
	//LT �Ǵ� GT�� ũ�⸦ ���̰� EQ�� �߰�

	//LT�� pivot���� ū ���� �����ϰų� GT�� pivot���� ���� ���� �����ϸ�
	//���� ��ü

	while (i < j) {
		while (A[i] <= p && i < j &&i < a) {
			if (A[i] == p) {
				//A[i]�� pivot�� ���� �� EQ�� �̵�
				c++;								//EQ�� ũ�� ����

				// LT�� ũ�⸦ ���̱� ���� a�� ������ ����
				tmp = A[a];
				A[a] = A[a - 1];
				A[a - 1] = tmp;

				tmp = A[a];
				A[a] = A[i];
				A[i] = tmp;
				a--;
			}
			else {
				i++;
			}
		}

		while (p <= A[j] && i < j && a + c < j) {
			if (A[j] == p) {
				//A[j]�� pivot�� ���� �� EQ�� �̵�
				c++;								//EQ�� ũ�� ����

				//EQ�� �ڿ� A[j] ����
				tmp = A[j];
				A[j] = A[a + c];
				A[a + c] = tmp;
			}
			else {
				j--;
			}
		}

		//i�� j�� EQ�� ������ ���� - a~a+c�ε��� ������ �ٸ� ���� �������� ����
		if (i == a && a + c == j)
			break;

		if (i < j) {
			// i�� j�� ���� EQ�� ������ ���
			// EQ�� ��ġ�� �����ؾ��Ѵ�.

			// --------j�� a+c�� ���� A[i]�� pivot���� ū ��� (c>0)------------------
			// 1) A[i]�� ���� EQ�� ������ A[j] �� swap 
			// 2) EQ�� ũ�⸦ ������ c�� ũ�� ���� -> c--
			// 3) pivot�� ������ A[i]�� �ݺ����� ������ ����ϸ� �ٽ� EQ�� ���ϰ� �ȴ�.

			// --------j�� a+c�� ���� A[i]�� pivot���� ū ��� (c=0)------------------
			// 1) A[i]�� ���� EQ�� ������ A[j] �� swap 
			// 2) a�� �ε����� i�� �ٲپ� �ش�. -> EQ ��ü�� �̵���
			// 3) �ݺ����� ������ ����ϸ� EQ�� �ٸ� �ڸ��� �̵��ȴ�.

			//i�� a�̰� A[j]�� Pivot���� ���� ��쵵 ���� ������ �˰������� ����

			if (c == 0) {
				if (i == a) {
					a = j;
				}
				else if (j == a) {
					a = i;
				}
			}
			else {
				if (i == a) {
					a++;
					c--;
				}
				else if (j == a + c) {
					c--;
				}
			}
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
	}
	arr[0] = a;
	arr[1] = a + c;
}


void insertionSort(int *A, int n) {
	//������������ �����ϴ� �������� �˰���
	int tmp = 0, *pj;
	for (int *pi = A + 1; pi < A + n; pi++) {
		pj = pi - 1;
		tmp = *pi;
		while (tmp < *pj && pj >= A) {
			*(pj + 1) = *pj;
			pj--;
		}
		*(pj + 1) = tmp;
	}
}

int findIndexOfMedianOfThree(int *A, int a, int b, int c) {
	int med = a;
	if (A[a] > A[b] && A[a] > A[c]) {
		if (A[b] > A[c]) {			//[a][b][c]
			med = b;
		}
		else {							//[a][c][b]
			med = c;
		}
	}

	if (A[b] > A[a] && A[b] > A[c]) {
		if (A[a] > A[c]) {			//[b][a][c]
			med = a;
		}
		else {							//[b][c][a]
			med = c;
		}
	}

	if (A[c] > A[a] && A[c] > A[b]) {
		if (A[a] > A[b]) {			//[c][a][b]
			med = a;
		}
		else {							//[c][b][a]
			med = b;
		}
	}
	return med;
}