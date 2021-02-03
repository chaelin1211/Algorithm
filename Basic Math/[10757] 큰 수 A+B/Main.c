#include<stdio.h>
#include<stdlib.h>
int main(void) {
	char input[2][10001];
	scanf("%s %s", input[0], input[1]);
    function(input[0], input[1]);
}
void function(char*input1, char*input2){
	int i, j, k, tmp=0;

	int answer[20001];
	int a, b;

	i = strlen(input1)-1;
	j = strlen(input2)-1;
	k = 0;

    // 뒤쪽(작은 쪽)부터 더한다.
	while (i >= 0 && j >= 0) {
		a = input1[i--] + 1 - '1';    
		b = input2[j--] + 1 - '1';
		tmp += a + b;

        // 더해서 10이 넘을 경우를 대비
		answer[k++] = tmp % 10;

        // 10이 넘으면 다음 자릿수에 1을 더해야 함
		tmp /= 10;
	}	

	while (i >= 0) {
		a = input1[i--] + 1 - '1';    
		tmp += a;
		answer[k++] = tmp % 10;
		tmp /= 10;
	}
	while (j >= 0) {
		b = input2[j--] + 1 - '1';
		tmp += b;
		answer[k++] = tmp % 10;
		tmp /= 10;
	}
    
	while (tmp != 0) {
		answer[k++] = tmp % 10;
		tmp /= 10;
	}
	
    // k에서 1을 빼야 마지막 값이 저장된 위치
    k--;
	for (; k >= 0; k--) {
		printf("%d", answer[k]);
	}
}