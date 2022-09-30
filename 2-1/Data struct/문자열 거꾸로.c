#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void main() {
	char a[100]={'\0'},ch='y';
	int i, j;
	printf("================================\n");
	printf("문자열 거꾸로 출력하는 프로그램\n");
	printf("================================\n");
	while (ch != 'n') {
		printf("문자열을 입력하세요:");
		gets(a);
		for (i = 0; a[i] != '\0'; i++);
		for (j = i - 1; j >= 0; j--)
		printf("%c", a[j]);
		printf("\n계속갈까요?(y/n).....");
		scanf_s("%c", &ch);
		gets(a);
	}
	printf("\n\n\n\n\n\n\n\n\n\n");
	return 0;

}