#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void main() {
	char a[100]={'\0'},ch='y';
	int i, j;
	printf("================================\n");
	printf("���ڿ� �Ųٷ� ����ϴ� ���α׷�\n");
	printf("================================\n");
	while (ch != 'n') {
		printf("���ڿ��� �Է��ϼ���:");
		gets(a);
		for (i = 0; a[i] != '\0'; i++);
		for (j = i - 1; j >= 0; j--)
		printf("%c", a[j]);
		printf("\n��Ӱ����?(y/n).....");
		scanf_s("%c", &ch);
		gets(a);
	}
	printf("\n\n\n\n\n\n\n\n\n\n");
	return 0;

}