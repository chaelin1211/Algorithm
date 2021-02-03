#include<stdio.h>
#include<stdlib.h>
int main(void) {
	char input[2][10001];
	int i, j, k, tmp=0;

	int answer[20001];
	int a, b;
	scanf("%s %s", input[0], input[1]);

	i = strlen(input[0])-1;
	j = strlen(input[1])-1;
	k = 0;
	while (i >= 0 && j >= 0) {
		a = input[0][i--] + 1 - '1';
		b = input[1][j--] + 1 - '1';
		tmp += a + b;

		answer[k++] = tmp % 10;
		tmp /= 10;
	}	
	while (i >= 0) {
		a = input[0][i--] + 1 - '1';
		tmp += a;
		answer[k++] = tmp % 10;
		tmp /= 10;
	}
	while (j >= 0) {
		b = input[1][j--] + 1 - '1';
		tmp += b;
		answer[k++] = tmp % 10;
		tmp /= 10;
	}
	while (tmp != 0) {
		answer[k++] = tmp % 10;
		tmp /= 10;
	}
	k--;
	for (; k >= 0; k--) {
		printf("%d", answer[k]);
	}
}