#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <Windows.h>

int MAX = 25;
int *Arr, *Hotel;

int main() {
	int n, s, d;
	int test[3][2] = { {0,4},{2,5},{2,4} };
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	Arr = (int *)malloc(sizeof(int)*MAX);
	Hotel = (int *)malloc(sizeof(int)*MAX);

	//--------------������ �Է�--------------
	Arr[0] = 0;
	Arr[1] = 1;
	Hotel[0] = 0;
	Hotel[1] = 5;

	for (int i = 2; i < MAX - 1; i++) {
		Arr[i] = Arr[i - 1] + Arr[i - 1] % 5 + 3;
	}
	for (int i = 2; i < MAX - 1; i++) {
		Hotel[i] = (Hotel[i - 1] + i) % 9 + 1;
	}

	//--------------n=6---------------
	n = 6;

	printf(" n  s  d   mincost   version   cputime\n");
	for (int i = 0; i < 3; i++) {
		s = test[i][0];
		d = test[i][1];

		printf("%2d %2d %2d   ", n, s, d);
		//------������ġ ���� ���� �ð� airtelDC---------
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		///////////////////////////////////////////////
		printf("%-10dDC        ", airtelDC(n, s, d));
		///////////////////////////////////////////////
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);

		printf("%2d %2d %2d   ", n, s, d);
		//-----�������α׷��� ���� ���� �ð� airtelDP------
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		///////////////////////////////////////////////
		printf("%-10dDP        ", airtelDP(n, s, d));
		///////////////////////////////////////////////
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);
	}

	//--------------n=MAX---------------
	n = MAX;
	s = 1;
	d = n - 2;

	printf("%2d %2d %2d   ", n, s, d);
	//------������ġ ���� ���� �ð� airtelDC---------
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	///////////////////////////////////////////////
	printf("%-10dDC        ", airtelDC(n, s, d));
	///////////////////////////////////////////////
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);

	printf("%2d %2d %2d   ", n, s, d);
	//-----�������α׷��� ���� ���� �ð� airtelDP------
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	///////////////////////////////////////////////
	printf("%-10dDP        ", airtelDP(n, s, d));
	///////////////////////////////////////////////
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);
}

int airtelDC(int n, int s, int d) {
	//��� ȣ��
	//���� mincost�� ���� �������� Hotel Cost�� �߰��Ѵ�.
	return rairtelDC(n, s, d) + Hotel[d];
}
int airtelDP(int n, int s, int d) {
	//���� mincost�� ���� �������� Hotel Cost�� �߰��Ѵ�.
	return airtelDP2(n, s, d) + Hotel[d];
}
int airtelDP2(int n, int s, int d) {
	int *m, cost = 0;
	m = (int*)malloc(sizeof(int)*n);

	//m[i]���� s���� i ������ �ּ� ����� ����ȴ�.
	//�� s���� d������ �ּ� ����� m[d]
	m[s] = 0;

	for (int i = s + 1; i <= d; i++) {
		m[i] = 100000;
		for (int k = s; k <= i - 1; k++) {
			cost = m[k] + Hotel[k] + Arr[i - k];
			//������ k������ ����� m[k]�� ������ �߻��ϴ� Hotel cost Hotel[k]
			//�׸��� ���������� ������������ ����� Arr[i-k]�� �� ����
			//>>�ش� ����� ���� ���

			//���� ���� �������� �� ��� ȣ�� ����� �ʿ� ����.
			//s�� 0�� �ƴ� ��쿣 Hotel[k]�� ���� 0�� �ƴϴ� ���־�� �Ѵ�.
			if (k == s) {
				cost -= Hotel[k];
			}
			if (m[i] > cost) {
				m[i] = cost;
			}
		}
	}
	return m[d];			//s���� d������ �ּ� ���
}
int rairtelDC(int n, int s, int d) {
	int mincost = 100000, cost;
	if (d == s)return 0;
	for (int k = s; k <= d - 1; k++) {
		cost = rairtelDC(n, s, k) + Hotel[k] + Arr[d - k];
		//��͸� ���� s���� k������ �ּ� ����� ���ϰ� ������ �߻��ϴ� Hotel cost��
		// ���� �� ������ d������ ����� �����ش�.

		//���� ���� �������� �� ��� ȣ�� ����� �ʿ� ����
		//s�� 0�� �ƴ� ��쿣 Hotel[k]�� ���� 0�� �ƴϴ� ���־�� �Ѵ�.
		if (k == s) {
			cost -= Hotel[k];
		}
		if (cost < mincost) {
			mincost = cost;
		}
	}
	return mincost;
}