#include<stdio.h>
#define MAX 100
int n = 1;
int list[MAX] = { 0 };
void main()
{
	int a, b, c;
	printf("=================================\n");
	printf("입력받은 정수 오름차순으로 정렬\n");
	printf("=================================\n");
	while (1)
	{
		printf("\n정수를 입력하세요 출력(0) 종료(-1)");
		scanf_s("%d", &a);
		if (list[0] == 0)list[0] = a;
		else {
			if (a == 0) {
				for (int k = 0; k < n; k++) printf("%d ", list[k]);
			}
			else if (a == -1)break;
			else {
				b = 0;
				while (list[b] < a && b < n) b++;
				for (c = n; c >= b; c--) {
					list[c] = list[c - 1];
				}
				list[b] = a;
				n++;
			}
		}
	}
	printf("\n\n\n\n\n\n\n\n");
		return 0;
}
