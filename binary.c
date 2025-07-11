#include <stdio.h>

int main() {
    unsigned int num;
    
    printf("양의 정수를 입력하세요: ");
    scanf("%u", &num);
    
    printf("입력한 값 %u의 이진수 표현: ", num);
    
    // 32비트 unsigned int의 모든 비트를 확인
    for (int i = 31; i >= 0; i--) {
        // i번째 비트가 1인지 확인
        if (num & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
        
        // 4비트마다 공백 추가하여 가독성 향상
        if (i % 4 == 0 && i != 0) {
            printf(" ");
        }
    }
    
    printf("\n");
    
    return 0;
}