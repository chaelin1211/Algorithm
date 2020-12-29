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

	//--------------데이터 입력--------------
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
		//------분할통치 버전 수행 시간 airtelDC---------
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		///////////////////////////////////////////////
		printf("%-10dDC        ", airtelDC(n, s, d));
		///////////////////////////////////////////////
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);

		printf("%2d %2d %2d   ", n, s, d);
		//-----동적프로그래밍 버전 수행 시간 airtelDP------
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
	//------분할통치 버전 수행 시간 airtelDC---------
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	///////////////////////////////////////////////
	printf("%-10dDC        ", airtelDC(n, s, d));
	///////////////////////////////////////////////
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.9fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) / 1000.0f);

	printf("%2d %2d %2d   ", n, s, d);
	//-----동적프로그래밍 버전 수행 시간 airtelDP------
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
	//재귀 호출
	//최종 mincost에 최종 도착지의 Hotel Cost를 추가한다.
	return rairtelDC(n, s, d) + Hotel[d];
}
int airtelDP(int n, int s, int d) {
	//최종 mincost에 최종 도착지의 Hotel Cost를 추가한다.
	return airtelDP2(n, s, d) + Hotel[d];
}
int airtelDP2(int n, int s, int d) {
	int *m, cost = 0;
	m = (int*)malloc(sizeof(int)*n);

	//m[i]에는 s부터 i 까지의 최소 비용이 저장된다.
	//즉 s부터 d까지의 최소 비용은 m[d]
	m[s] = 0;

	for (int i = s + 1; i <= d; i++) {
		m[i] = 100000;
		for (int k = s; k <= i - 1; k++) {
			cost = m[k] + Hotel[k] + Arr[i - k];
			//경유지 k까지의 비용인 m[k]와 경유시 발생하는 Hotel cost Hotel[k]
			//그리고 경유지부터 목적지까지의 비용인 Arr[i-k]를 다 더함
			//>>해당 경로의 최종 비용

			//경유 없이 도착지로 갈 경우 호텔 비용이 필요 없다.
			//s가 0이 아닌 경우엔 Hotel[k]의 값이 0이 아니니 빼주어야 한다.
			if (k == s) {
				cost -= Hotel[k];
			}
			if (m[i] > cost) {
				m[i] = cost;
			}
		}
	}
	return m[d];			//s부터 d까지의 최소 비용
}
int rairtelDC(int n, int s, int d) {
	int mincost = 100000, cost;
	if (d == s)return 0;
	for (int k = s; k <= d - 1; k++) {
		cost = rairtelDC(n, s, k) + Hotel[k] + Arr[d - k];
		//재귀를 통해 s부터 k까지의 최소 비용을 구하고 경유시 발생하는 Hotel cost와
		// 경유 후 목적지 d까지의 비용을 더해준다.

		//경유 없이 도착지로 갈 경우 호텔 비용이 필요 없다
		//s가 0이 아닌 경우엔 Hotel[k]의 값이 0이 아니니 빼주어야 한다.
		if (k == s) {
			cost -= Hotel[k];
		}
		if (cost < mincost) {
			mincost = cost;
		}
	}
	return mincost;
}