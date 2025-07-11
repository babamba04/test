#include <stdio.h>

int main(void)
{
	int pivo[10];  // 피보나치 수를 저장할 배열
	int i;
	
	// 피보나치 수열 계산 (1부터 시작)
	pivo[0] = 1;  // 첫 번째 수
	pivo[1] = 1;  // 두 번째 수
	
	// 나머지 피보나치 수 계산
	for (i = 2; i < 10; i++) {
		pivo[i] = pivo[i-1] + pivo[i-2];
	}
	
	// 피보나치 수열 출력
	printf("피보나치 수열 (1부터 시작):\n");
	for (i = 0; i < 10; i++) {
		printf("pivo[%d] = %d\n", i, pivo[i]);
	}
	
	return 0;
}
