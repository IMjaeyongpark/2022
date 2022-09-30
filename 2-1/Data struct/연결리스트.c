#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef struct node {
	int data;
	struct node* next;
}NODE;

NODE* list;

int menu();
void insert();
void delete();
void search();
void print();


int main() {
	int sel;
	while (1) {
		sel = menu();
		switch (sel) {
		case 1:insert();
			break;
		case 2:delete();
			break;
		case 3:search();
			break;
		case 4:print();
			break;
		case 5:printf("\n\n\n����\n\n\n\n\n\n");
			exit(-1);
		default: printf("�ٽ��Է��ϼ���!!\n");
			break;
		}
		system("pause");
		system("cls");
	}
}

int menu() {
	int _sel;
	printf("---------------------------------\n");
	printf("���Ḯ��Ʈ ���� 2019243097 �����\n");
	printf("---------------------------------\n");
	printf("1.����\n");
	printf("2.����\n");
	printf("3.�˻�\n");
	printf("4.���\n");
	printf("5.����\n");
	printf("\n���ڸ� �Է��ϼ���:");
	scanf("%d", &_sel);
	return _sel;
}

void insert() {
	int num;
	NODE* newnode,*current,*pre=NULL;
	printf("\n������ �����͸� �Է��ϼ���:");
	scanf("%d", &num);
	current = list;
	while (current != NULL) {
		if (current->data == num) {
			printf("\n�ߺ��� �������Դϴ�!!\n");
			return;
		}
		pre = current;
		current = current->next;
	}
	newnode = (NODE*)malloc(sizeof(NODE));
	newnode->data = num;
	newnode->next = NULL;
	if (list == NULL) {
		list = newnode;
		return;
	}
	pre->next = newnode;
	return ;
}

void delete() {
	int _data;
	NODE* current = list, * follow = NULL;
	printf("\n�����ϰ� ���� �����͸� �Է��ϼ���:");
	scanf("%d", &_data);
	while (current != NULL && current->data != _data) {
		follow = current;
		current = current->next;
	}
	if (follow == NULL) {
		list = list->next;
		free(current);
	}
	else if (current == NULL) {
		printf("\n���� �������Դϴ�!!\n");
	}
	else {
		follow->next = current->next;
		free(current);
	}
	printf("\n");
	return;
}

void search() {
	int _data;
	NODE* current = list;
	printf("\nã�� ���� �����͸� �Է��ϼ���:");
	scanf("%d", &_data);
	while (current != NULL) {
		if (current->data == _data) {
			printf("\n�����ϴ� �������Դϴ�.\n");
			return;
		}
		current = current->next;
	}
	printf("\n���� �������Դϴ�.\n");
	return;
}

void print() {
	NODE* current = list;
	while (current != NULL) {
		printf("%d\t", current->data);
		current = current->next;
	}
	printf("\n");
	return;
}