#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>

typedef struct numbg {			//�������� ������ ���ڸ� ������ ���Ḯ��Ʈ
	int i;						//���� ��ġ 
	int num;					 
	struct numbg* next;
}NUMBG;

NUMBG* innum();					//�������� ���� �Լ� 
NUMBG* ipruk(int _count);		//�÷��̾ �Է��� ���� ���� �Լ� 
void print();					//���α׷� �̸� ��� �Լ�
int menu();						//�޴��� ����ϰ� �����ϴ� �Լ�
int check(int ran, NUMBG* aa);	//�������� ������ ���ڰ� �ߺ��Ǵ��� Ȯ���ϴ� �Լ�
int game(NUMBG* comp);			//���ھ߱� ����	
int che (char *_a);				//����ڰ� �Է��� ���� ���ǿ� �´��� Ȯ���ϴ� �Լ� 

void main() {
	NUMBG* ranum = NULL;
	int sel, count;
	while (1) {
		print();
		sel = menu();	//�޴� ���� 
		switch (sel) {
		case 1:ranum = innum();
			count = game(ranum);
			printf("\n\n\n\n%dȸ���� �¸�!!!!\n\n\n\n", count);		//�õ��� Ƚ�� ��� 
			break;
		case 2:printf("\n\n\n\n���α׷� ����\n\n\n\n");
			exit(-1);
		}
		printf("\n\n\n");
		system("pause");
		system("cls");		//�ܼ�â ����� 
	}
}

void print() {
	printf("*************************************\n");
	printf("           ���ھ߱� ����             \n");
	printf("*************************************\n");
	return;
}

int menu() {
	int _sel;
	printf("1.����\n");
	printf("2.����\n");
	printf("�޴��� �����ϼ���:");
	scanf_s("%d", &_sel);
	return _sel;
}

NUMBG* innum() {
	NUMBG* head = NULL, * newrand = NULL, * current = NULL;
	int ranum, i = 0;
	srand(time(NULL));		//�ð��� ������ ���� ���ڰ� �ٲ�
	for (i = 0; i < 5; i++) {
		ranum = rand() % 9 + 1;	//�������� 1 ~ 9������ ���� ����  
		ranum = check(ranum, head);	//������ ���ڰ� �ߺ����� Ȯ�� 
		newrand = (NUMBG*)malloc(sizeof(NUMBG));
		newrand->num = ranum;
		newrand->i = i + 1;
		newrand->next = NULL;
		if (head == NULL) {		//ù���� ��� 
			head = newrand;
			current = newrand;
		}
		else {					//�״��� ��忡 ���� 
			current->next = newrand;
			current = current->next;
		}
	}
	return head;		//�������� ������ ���ڰ� ���Ե� ���Ḯ��Ʈ ��ȯ 
}

int check(int ran, NUMBG* aa) {
	NUMBG* bb;
	bb = aa;

	while (aa != NULL) {
		if (aa->num == ran) {		//�������� ������ ���ڰ� �ߺ����� Ȯ�� 
			ran = rand() % 9 + 1;	//�ߺ��̸� ���ο� ���� ���� ���� 
			aa = bb;				//ó������ �� 
		}
		else aa = aa->next;
	}
	return ran;						//�������� ��ȯ 
}

int game(NUMBG* comp) {
	NUMBG* user = NULL, * del = NULL;
	int S = 0, B = 0;
	int count = 0;
	NUMBG* comp2;
	comp2 = comp;
	while (S != 5) {
		int i = 1;
		S = 0, B = 0;
		count++;
		user = ipruk(count);	//���ڸ� �Է¹޾� ���Ḯ��Ʈ�� ���� 
		while (user != NULL) {
			comp = comp2;
			while (comp != NULL) {
				if (comp->num == user->num) {		//�Է¹��� ���ڿ� �������� ������ ���ڸ� �� 
					if (comp->i == user->i)S++;	//���ڿ� ������ ������ S++ 
					else B++;					//���ڿ� ������ �ٸ��� B++ 
				}
				comp = comp->next;
			}
			del = user;
			user = user->next;
			free(del);
		}
		printf("S:%d\tB:%d\n", S, B);		//�Է¹��� ���ڿ�  �������ڸ� ���Ͽ� ���� ����� 
	}
	return count;		//�����ϱ���� �õ���Ƚ�� ��ȯ
}

NUMBG* ipruk(int _count) {
	int num, _i;
	char a[5];
	NUMBG* head = NULL, * newnode = NULL, * current = NULL;
	while (1) {
		printf("%d.�����Է�(5��,0����):", _count);
		scanf("%s",a);
		if (che(a) == 1)printf("�ٽ� �Է��ϼ���!!\n");
		else break;
	}

	for (_i = 0; _i < 5; _i++) {		//�Է¹��� ���� ���Ḯ��Ʈ�� ���� 
		newnode = (NUMBG*)malloc(sizeof(NUMBG));
		newnode->i = _i + 1;
		newnode->num = a[_i]-'0';
		if (head == NULL) {
			head = newnode;
			current = newnode;
		}
		else {
			current->next = newnode;
			current = newnode;
		}
	}
	newnode->next = NULL;
	return head;
}

int che(char *_a){
	int _i;
	if((atoi(_a) - 100000) > 0 || (atoi(_a) - 9999) < 0)return 1;//5�ڸ����� Ȯ�� 
	else {
		for(_i=0;_i<5;_i++){
			if(_a[_i]=='0')return 1;		//0�� ���յǾ� �ִ��� Ȯ�� 
		}
		return 0;
	}
}


































