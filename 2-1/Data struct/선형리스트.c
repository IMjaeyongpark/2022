#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<windows.h>
#define MAX 100
int Menu();
void Print_Header();
int Insert(int _data[MAX],int _i);
int Delete(int _data[MAX],int _i);
void Search(int _data[MAX],int _i);
void Print(int _data[MAX],int _i);
void End();
void main() {
	int num,i=0;
	int data[MAX];
	while (1) {
	
		num = Menu();
		switch (num) {
		case 1:
			i=Insert(data,i);
			break;
		case 2:
			i=Delete(data,i);
			break;
		case 3:
			Search(data,i);
			break;
		case 4:
			Print(data,i);
			break;
		case 5:End();
		}
		system("pause");
		system("cls");
	}
}

int Menu() {
	int _num;
	printf("=================================\n\n");
	printf("���� ����Ʈ ���α׷�\n\n");
	printf("=================================\n\n\n\n\n");
	printf("1.Insert\n");
	printf("2.Delete\n");
	printf("3.Search\n");
	printf("4.Print\n");
	printf("5.End\n");
	printf("�޴��� �����ϼ���.......");
	scanf_s("%d", &_num);
	return _num;
}
int Insert(int _data[MAX],int _i) {
	int b=0,c,a=0;
	printf("\n���ڸ� �Է��ϼ���:");
	scanf_s(" %d", &c);
	while (b <= _i) {
		if (_data[b] == c) {
			printf("\n�̹� ����Ǿ��ִ� �����Դϴ�!!!\n");
			return _i;
		}
		b++;
	}
	if (_i > MAX) {
		printf("\n��������� ����á���ϴ�!!!\n\n");
		return _i;
	}
	while (a < _i && _data[a] < c) a++;
	
	for (b = _i; b >= a;b--) {
		_data[b + 1] = _data[b];
		
	}
	_data[a] = c;
	_i++;
	return _i;
}
int Delete(int _data[MAX],int _i) {
	int c;
	int a=0;
	printf("\n���ڸ� �Է��ϼ���:");
	scanf_s(" %d",&c );
	while (_data[a] != c&&a<=_i) {
		a++;
	}
		if (_i < a)printf("���� �������Դϴ�\n");
		else {
			while (a <= _i) {
				_data[a] = _data[a + 1];
				a++;
			}
			_i--;
		}
	return _i;
}
void Search(int _data[MAX],int _i){
	int c;
	int a=0;
	printf("\n���ڸ� �Է��ϼ���:");
	scanf_s(" %d", &c);
	while (_data[a] !=c&&a<=_i ) {
		a++;
	}
	if (a < _i) printf("%d�� %d��° �������Դϴ�\n",_data[a], a+1);
	else printf("���� �������Դϴ�\n");
	return;
}
void Print(int _data[MAX], int _i) {
	int a = 0;
	while (a < _i) {
		printf("%d\t", _data[a]);
		a++;
	}
	printf("\n");
	return;
}
void End() {
	printf("\n\n\n\n\n\n\n\n\n\n���α׷� ����\n\n\n\n\n\n\n\n\n\n");
	exit(-1);
}





