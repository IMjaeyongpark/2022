#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>

typedef struct numbg {			//랜덤으로 생성된 숫자를 저장할 연결리스트
	int i;						//숫자 위치 
	int num;					 
	struct numbg* next;
}NUMBG;

NUMBG* innum();					//랜덤숫자 생성 함수 
NUMBG* ipruk(int _count);		//플레이어가 입력한 숫자 저장 함수 
void print();					//프로그램 이름 출력 함수
int menu();						//메뉴를 출력하고 선택하는 함수
int check(int ran, NUMBG* aa);	//랜덤으로 생성된 숫자가 중복되는지 확인하는 함수
int game(NUMBG* comp);			//숫자야구 시작	
int che (char *_a);				//사용자가 입력한 수가 조건에 맞는지 확인하는 함수 

void main() {
	NUMBG* ranum = NULL;
	int sel, count;
	while (1) {
		print();
		sel = menu();	//메뉴 선택 
		switch (sel) {
		case 1:ranum = innum();
			count = game(ranum);
			printf("\n\n\n\n%d회만에 승리!!!!\n\n\n\n", count);		//시도한 횟수 출력 
			break;
		case 2:printf("\n\n\n\n프로그램 종료\n\n\n\n");
			exit(-1);
		}
		printf("\n\n\n");
		system("pause");
		system("cls");		//콘솔창 지우기 
	}
}

void print() {
	printf("*************************************\n");
	printf("           숫자야구 게임             \n");
	printf("*************************************\n");
	return;
}

int menu() {
	int _sel;
	printf("1.시작\n");
	printf("2.종료\n");
	printf("메뉴를 선택하세요:");
	scanf_s("%d", &_sel);
	return _sel;
}

NUMBG* innum() {
	NUMBG* head = NULL, * newrand = NULL, * current = NULL;
	int ranum, i = 0;
	srand(time(NULL));		//시간이 지남에 따라 숫자가 바뀜
	for (i = 0; i < 5; i++) {
		ranum = rand() % 9 + 1;	//랜덤으로 1 ~ 9까지의 숫자 생성  
		ranum = check(ranum, head);	//생성된 숫자가 중복인지 확인 
		newrand = (NUMBG*)malloc(sizeof(NUMBG));
		newrand->num = ranum;
		newrand->i = i + 1;
		newrand->next = NULL;
		if (head == NULL) {		//첫번 노드 
			head = newrand;
			current = newrand;
		}
		else {					//그다음 노드에 삽입 
			current->next = newrand;
			current = current->next;
		}
	}
	return head;		//랜덤으로 생성된 숫자가 삽입된 연결리스트 반환 
}

int check(int ran, NUMBG* aa) {
	NUMBG* bb;
	bb = aa;

	while (aa != NULL) {
		if (aa->num == ran) {		//랜덥으로 생성된 숫자가 중복인지 확인 
			ran = rand() % 9 + 1;	//중복이면 새로운 랜덤 숫자 생성 
			aa = bb;				//처음부터 비교 
		}
		else aa = aa->next;
	}
	return ran;						//랜덤숫자 반환 
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
		user = ipruk(count);	//숫자를 입력받아 연결리스트에 삽입 
		while (user != NULL) {
			comp = comp2;
			while (comp != NULL) {
				if (comp->num == user->num) {		//입력받은 숫자와 랜덤으로 생성된 숫자를 비교 
					if (comp->i == user->i)S++;	//숫자에 순서가 같으면 S++ 
					else B++;					//숫자에 순서가 다르면 B++ 
				}
				comp = comp->next;
			}
			del = user;
			user = user->next;
			free(del);
		}
		printf("S:%d\tB:%d\n", S, B);		//입력받은 숫자와  랜덤숫자를 비교하여 받은 결과값 
	}
	return count;		//성공하기까지 시도한횟수 반환
}

NUMBG* ipruk(int _count) {
	int num, _i;
	char a[5];
	NUMBG* head = NULL, * newnode = NULL, * current = NULL;
	while (1) {
		printf("%d.숫자입력(5개,0제외):", _count);
		scanf("%s",a);
		if (che(a) == 1)printf("다시 입력하세요!!\n");
		else break;
	}

	for (_i = 0; _i < 5; _i++) {		//입력받은 숫자 연결리스트에 삽입 
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
	if((atoi(_a) - 100000) > 0 || (atoi(_a) - 9999) < 0)return 1;//5자리인지 확인 
	else {
		for(_i=0;_i<5;_i++){
			if(_a[_i]=='0')return 1;		//0이 포합되어 있는지 확인 
		}
		return 0;
	}
}
