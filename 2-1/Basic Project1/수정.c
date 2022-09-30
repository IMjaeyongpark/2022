#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define UP 72
#define DOWN 80

typedef struct team {		//�м��ϴ� ���� �����ϴ� ���� ����
	char team_name[3];		//�� �̸�
	int win;				//��
	int draw;				//��
	int lose;				//��
	int point;				//����
}TEAM;

typedef struct bigteam {	//�м��ϴ� ��� ���� �����ϴ� ���� ����
	char team_name[3];		//���̸�
	int homewin;			//Ȩ ��
	int win;				//��
	int homedraw;			//Ȩ ��
	int draw;				//��
	int homelose;			//Ȩ ��
	int lose;				//��
	int goal;				//����
	int losegoal;			//����
}BIGTEAM;

typedef struct seasonrank {	//�м��� ������ ������ ����
	char team_name[3];
	int win;
	int draw;
	int lose;
	int point;
	struct seasonrank* next;
}SEASONRANK;

typedef struct game {		//���� ���� ���ӿ����� ���� ��� ����
	int home;
	int away;
	float h_bet;			//Ȩ ���
	float a_bet;			//���� ���	
	float h_win;			//Ȩ �·�
	float a_win;			//���� �·�
	struct game* next;
}GAME;

typedef struct userbet {	//������ ������ ���� ���
	int bett;				//������ ������ ��
	float betwin;			//������ ������ ����� �·�
	int gam;				//������ ���� Ȩ���� ��������
	struct userbet* next;
}USER;


TEAM analysis[20];			//�м��ϴ� ���� �����ϴ� ���� ������ �����ϴ� �迭
BIGTEAM bigteam[15];		//�м��ϴ� ��� ������ �����ϴ� ���� �����迭
SEASONRANK* season[3] = { NULL };	//3���� ���� ������ �����ϴ� ���Ḯ��Ʈ

void teamread(char teamdata[]);	//�м��ϴ� ���� �����ϴ� ���� �����ϴ� �Լ�
void stringSplit(char data[]);	//������ �а� ������ �����ϴ� �Լ�
void seasonrank(int se);		//�м��� ���� ������ ������ ����Ͽ� ������������ ���Ḯ��Ʈ�� �����ϴ� �Լ�
void print_rank();				//������ ������ ������ Ǯ���ϴ� �Լ�
int select_menu();				//����ڰ� ����� �޴��� ����ϴ� �Լ�
void big_team_name();			//�м��ϴ� ��� ���� �����ϴ� ������ �̸��� �����ϰ� �������� �ʱ�ȭ ��Ű�� �Լ�
int check_bigteam(char* te_name);	//������ �����Ҷ� ������ �����ϴ� ������ Ȯ���ϴ� �Լ�
void bigteam_analysis();		//��� ���� �����ϴ� ������ ������ ����ϴ� �Լ�
void proto();					//���� ���� ���� �Լ�
GAME* makegame();				//���� ���� ���ӿ��� ����� �����⸦ ����� �Լ�
int* playgame(USER* node);		//���� ����� ���и� ���ϴ� �Լ�
void makerank();				//������ �޸��忡 �����ϴ� �Լ�
void printproto();
int keyControl();

int main() {
	srand(time(NULL));
	FILE* fp = NULL;
	char str[100] = { "\0" };		//���� ������ �����ϴ� ���ڹ迭
	int i = 0;
	int select;

	big_team_name();
	for (int i = 0; i < 3; i++) {	//3���� ������ �ϳ��� ����	
		switch (i) {
		case 0:fp = fopen("19-20.txt", "r");
			break;
		case 1:fp = fopen("20-21.txt", "r");
			break;
		case 2:fp = fopen("21-22.txt", "r");
			break;
		}
		fgets(str, 99, fp);		//������ ������ ����
		teamread(str);
		while (!feof(fp)) {		//������ ������ ���پ� ����
			fgets(str, 99, fp);
			stringSplit(str);
		}
		seasonrank(i);
		fclose(fp);
	}
	makerank();

	while (1) {
		select = select_menu();
		system("cls");
		switch (select) {
		case 1:print_rank();
			break;
		case 2:
			bigteam_analysis();
			break;
		case 3:printproto();
			proto();
			break;
		case 4:printf("\n\n\n���α׷� ����\n\n\n");
			exit(-1);
		default:printf("\n\n\n�ٽ� �Է� �ϼ���!!\n\n\n");
			break;
		}

		printf("\n\n\n");
		system("pause");
		system("cls");
	}
}

int keyControl() {
	char c;
	while (1) {
		if (_kbhit()) {
			c = _getch();
			if (c == -32) {
				c = _getch();
				switch (c) {
				case UP:
					return UP;
				case DOWN:
					return DOWN;
				}
			}
			else return 0;
		}
	}
}


void big_team_name() {			//��� ���� �����ϴ� ���� �̸��� ����ִ� �迭
	char* bigname[15] = { "LIV","MCI","MUN","CHE" ,"LEI","TOT" ,"WOL","ARS" ,"SOU","EVE","NEW","CRY","BHA","WHU","AVL" };

	for (int i = 0; i < 15; i++) {		//�迭 �ʱ�ȭ
		strcpy(bigteam[i].team_name, bigname[i]);
		bigteam[i].draw = 0;
		bigteam[i].goal = 0;
		bigteam[i].homedraw = 0;
		bigteam[i].homelose = 0;
		bigteam[i].homewin = 0;
		bigteam[i].lose = 0;
		bigteam[i].losegoal = 0;
		bigteam[i].win = 0;
	}
	return;
}

void teamread(char teamdata[]) {
	char* result;
	result = strtok(teamdata, "\t");
	for (int i = 0; i < 20; i++) {
		result = strtok(NULL, "\t\n");
		strcpy(analysis[i].team_name, result);
		analysis[i].win = 0;
		analysis[i].draw = 0;
		analysis[i].lose = 0;
		analysis[i].point = 0;
	}
	return;
}

void  stringSplit(char data[]) {
	char* homename;
	char* score;
	int i, j = 0;
	int goal1, goal2;
	int home, away;
	homename = strtok(data, "\t");
	for (i = 0; i < 20 && strcmp(analysis[i].team_name, homename) != 0; i++);
	score = strtok(NULL, "\t");
	home = check_bigteam(analysis[i].team_name);	//��� ���� �����ϴ� ������ Ȯ��
	j = 0;
	while (score != NULL) {
		goal1 = 0;
		goal2 = 0;
		if (j != i) {
			sscanf(score, "%d-%d", &goal1, &goal2);	//���ھ ����
			away = check_bigteam(analysis[j].team_name);
			if (goal1 > goal2) {	//Ȩ���� ������ �� ������
				analysis[i].win++;
				analysis[j].lose++;
				analysis[i].point += 3;
				if (home != -1) {
					bigteam[home].goal += goal1;
					bigteam[home].homewin++;
					bigteam[home].win++;
					bigteam[home].losegoal += goal2;
				}
				if (away != -1) {
					bigteam[away].goal += goal2;
					bigteam[away].lose++;
					bigteam[away].losegoal += goal1;
				}
			}
			else if (goal1 < goal2) {	//�������� ������ �� ������
				analysis[i].lose++;
				analysis[j].win++;
				analysis[j].point += 3;
				if (home != -1) {
					bigteam[home].goal += goal1;
					bigteam[home].homelose++;
					bigteam[home].lose++;
					bigteam[home].losegoal += goal2;
				}
				if (away != -1) {
					bigteam[away].goal += goal2;
					bigteam[away].win++;
					bigteam[away].losegoal += goal1;
				}
			}
			else {			//������ ������
				analysis[i].draw++;
				analysis[j].draw++;
				analysis[i].point++;
				analysis[j].point++;
				if (home != -1) {
					bigteam[home].goal += goal1;
					bigteam[home].homedraw++;
					bigteam[home].draw++;
					bigteam[home].losegoal += goal2;
				}
				if (away != -1) {
					bigteam[away].goal += goal2;
					bigteam[away].draw++;
					bigteam[away].losegoal += goal1;
				}
			}
		}
		j++;
		score = strtok(NULL, "\t\0\n");
	}
	return;
}
int check_bigteam(char* te_name) {
	for (int i = 0; i < 15; i++) {
		if (strcmp(te_name, bigteam[i].team_name) == 0)return i;	//��� ���� �����ϴ� ���� �迭�� �ϳ��� ���ϰ� �̸��� ������ �迭�� ���� ��ȯ
	}
	return -1;
}

void seasonrank(int se) {
	for (int i = 0; i < 20; i++) {
		SEASONRANK* newnode, * current = NULL, * pre = NULL;
		current = pre = season[se];
		newnode = (SEASONRANK*)malloc(sizeof(SEASONRANK));		//�м��ϴ� ������ ���� ���� ����
		strcpy(newnode->team_name, analysis[i].team_name);
		newnode->win = analysis[i].win;
		newnode->draw = analysis[i].draw;
		newnode->lose = analysis[i].lose;
		newnode->point = analysis[i].point;
		while ((current != NULL) && (current->point >= newnode->point)) {	//������������ ����
			pre = current;
			current = current->next;
		}

		newnode->next = current;
		if (current == season[se])season[se] = newnode;
		else pre->next = newnode;
	}
	return;
}

int select_menu() {
	int key;
	int select = 1;
	while (1) {
		printf("%d\n", select);
		printf("-----------------------------------\n");
		printf("�����̾� ���� �м� �� ���� ���ð���\n");
		printf("-----------------------------------\n\n");
		printf("1.���� ���� ���\n");
		printf("2.19~22���� ���� ���� ���\n");
		printf("3.���� ���� ����\n");
		printf("4.����\n\n");

		key = keyControl();
		if (key == UP) {
			if (select == 1)select = 4;
			else select--;
		}
		else if (key == DOWN) {
			if (select == 4)select = 1;
			else select++;
		}
		else return select;
		system("cls");
	}
}

void print_rank() {
	int sel;
	int rank;
	SEASONRANK* current = NULL;

	while (1) {
		printf("���� ����\n\n1.19~20����\n2.20~21����\n3.21~22����\n\n���� ����:");
		scanf("%d", &sel);		//���� ����
		if (sel > 0 && sel < 4)break;
		printf("�ٽ��Է�!!\n");
		system("pause");
		system("cls");
	}
	system("cls");
	current = season[sel - 1];
	rank = 1;
	printf("\n\t\t<<%d~%d���� ����>>", sel + 18, sel + 19);
	printf("\n\n\n����\t��\t��\t��\t��\t����\t����/����\n");
	while (current != NULL) {		//������ ������ ���� ���� �� ���� ���
		printf("%d\t%s\t%d\t%d\t%d\t%d", rank, current->team_name, current->win, current->draw, current->lose, current->point);
		if (rank < 5) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
			printf("\tè�Ǿ𽺸��� ���� ����\n");		//������ ���� ���� �� ���� ���� ���
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (rank == 5 || rank == 6) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			printf("\t�����ĸ��� ���� ����\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (rank == 7) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("\t������ ���۷������� ������\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (rank > 17) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\t����\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else printf("\n");
		current = current->next;
		rank++;
	}
	return;
}

void bigteam_analysis() {
	int a;
	float hw, w;
	while (1) {
		printf("\n19~22���� ����\n\n");
		for (int i = 0; i < 15; i++)printf("%d:%s\n", i + 1, bigteam[i].team_name);	//�м��� ������ �̸� ���
		printf("\n�� ����:");
		scanf("%d", &a);		//�� ����
		if (a < 16)break;
		printf("\n\n\n�ٽ� �Է��ϼ���!!\n\n\n\n");
		system("pause");
		system("cls");
	}
	a--;
	system("cls");
	printf("\n19~22���� ����\n");		//������ ���� 19~22���� ������ ���
	printf("\n���̸�: %s\n\nȨ ��\tȨ ��\tȨ ��\t��\t��\t��\n", bigteam[a].team_name);
	printf("%d\t%d\t%d\t%d\t%d\t%d\n", bigteam[a].homewin, bigteam[a].homedraw, bigteam[a].homelose, bigteam[a].win, bigteam[a].draw, bigteam[a].lose);
	printf("\n��\t����\tȨ �·�\t�·�\n");
	hw = (float)bigteam[a].homewin / (bigteam[a].homedraw + bigteam[a].homelose + bigteam[a].homewin) * 100;
	w = (float)bigteam[a].win / (bigteam[a].draw + bigteam[a].lose + bigteam[a].win) * 100;
	printf("%d\t%d\t%.2f%%\t%.2f%%\n", bigteam[a].goal, bigteam[a].losegoal, hw, w);
	return;
}

void proto() {
	int money = 0;		//������� ����ȭ��
	int plusmoney = 0;	//����ڰ� ������ �� ����ȭ��
	int plus;			//����ڰ� ������ ����ȭ��
	int betm;			//����ڰ� ������ ����ȭ��
	int selteam;		//��밡�� ������ �������� ��
	int selgame;		//����ڰ� ������ ������
	float bet;			//����ڰ� ������ ��������� ����
	long long profit = 0;	//������� ����
	int result;			//����ڰ� ������ ����� ���
	int checkwin;		//��밡�� ���߿��� 
	int* score;

	USER* betgame = NULL, * new = NULL, * cur = NULL;			//����ڰ� ������ ��⸦ �����ϴ� ���Ḯ��Ʈ
	GAME* list = NULL, * current = NULL, * newnode = NULL;		//������ ������ �����ϴ� ���Ḯ��Ʈ

	system("cls");

	while (1) {

		printf("\n1336 �����ߵ�ġ�Ἶ��\n\n\n������ �ݾ��� �Է��ϼ���(���� ����:-1):");
		scanf("%d", &plus);
		if (plus == -1) {
			system("cls");
			printf("\n\n\t����:%d\n\n\n", profit);
			return;
		}
		money += plus;
		plusmoney += plus;
		system("cls");
		list = current = NULL;
		int gamecount = rand() % 4 + 5;		//�������� ���� �������� ����
		for (int i = 0; i < gamecount; i++) {	//������ �����Ͽ� ���Ḯ��Ʈ�� ����
			newnode = makegame();
			if (list == NULL) list = current = newnode;
			else {
				current->next = newnode;
				current = newnode;
			}
		}
		int game[8] = { 0 };	//����ڰ� �����⸦ �����ߴ��� ���θ� Ȯ���ϴ� �迭
		while (1) {
			betm = 0;
			bet = 1;
			printf("\n1336 �����ߵ�ġ�Ἶ��\n\n���� �ݾ�:%d\t\t�����ݾ�:%d\n���:%.2f\t���߽� �ݾ�:%d\n\n", money, plusmoney, bet, (int)(betm * bet));
			printf(" home\t\t\taway\n\n");
			current = list;
			for (int k = 1; current != NULL; k++) {		//�������� ���� ���
				printf("%d.%s\t%.2f:%.2f\t%s\n", k, bigteam[current->home].team_name, current->h_bet, current->a_bet, bigteam[current->away]);
				current = current->next;
			}
			printf("\n������ �ݾ� ����:");
			scanf("%d", &betm);
			if (money >= betm && betm > -1)break;
			printf("\n\n\n�ٽ� �Է��ϼ���!!\n\n\n");
			system("pause");
			system("cls");
		}
		money -= betm;
		system("cls");
		selgame = 0;
		for (int k = 0; k < gamecount && selgame != -1; k++) {
			current = list;
			while (1) {
				printf("\n1336 �����ߵ�ġ�Ἶ��\n\n���� �ݾ�:%d\t\t�����ݾ�:%d\n���:%.2f\t���߽� �ݾ�:%d\n\n", money, plusmoney, bet, (int)(betm * bet));
				printf(" home\t\t\taway\n\n");
				current = list;
				for (int k = 1; current != NULL; k++) {
					printf("%d.%s\t%.2f:%.2f\t%s\n", k, bigteam[current->home].team_name, current->h_bet, current->a_bet, bigteam[current->away]);
					current = current->next;
				}
				printf("\n��⸦ �����ϼ���(���� ����:-1):");
				scanf("%d", &selgame);
				if (selgame == -1) {
					break;
				}
				if (selgame > gamecount || selgame < -1) {
					printf("\n\n�ٽ� �Է��ϼ���!!\n\n\n");
					system("pause");
					system("cls");
				}
				else if (game[selgame] == 1) {
					printf("\n\n�̹� ������ ����Դϴ�!\n\n\n");
					system("pause");
					system("cls");
				}
				else {
					game[selgame]++;
					break;
				}
			}
			while (1) {
				if (selgame == -1) {
					break;
				}
				printf("\n1.Ȩ�� ����\n2.������ ����\n\n");
				printf("������ ���� �����ϼ���:");
				scanf("%d", &selteam);
				printf("\n\n");
				if (selteam == 1 || selteam == 2)break;
				printf("\n\n�ٽ� �Է��ϼ���!!\n\n");
			}

			if (selgame != -1) {		//����ڰ� ������ ��⸦ ��带 �����Ͽ� �������� ����
				new = (USER*)malloc(sizeof(USER));
				current = list;
				for (int j = 1; j < selgame; j++) current = current->next;
				new->bett = selteam;
				new->gam = selgame;
				if (selteam == 1) {
					new->betwin = current->h_win;
					bet *= current->h_bet;
				}
				else if (selteam == 2) {
					new->betwin = current->a_win;
					bet *= current->a_bet;
				}
				new->next = NULL;
				if (betgame == NULL)betgame = cur = new;
				else {
					cur->next = new;
					cur = new;
				}
			}
			else break;
			system("pause");
			system("cls");
		}
		checkwin = 0;
		cur = betgame;
		printf("\n");
		while (cur != NULL) {		//����ڰ� ������ ������ ���� ���� ���
			current = list;
			score = playgame(cur);
			if (score[0] > score[1])result = 1;
			else if (score[0] < score[1])result = 2;
			if (result == 1)printf("��\t");
			else if (result == 2)printf("��\t");
			if (result != cur->bett) checkwin++;
			for (int n = 1; n < cur->gam; n++)current = current->next;
			printf("%s\t%d : %d\t%s\t\t", bigteam[current->home].team_name,score[0],score[1], bigteam[current->away].team_name);
			if (result == 2)printf("��\t");
			else printf("��\t");
			if (result != cur->bett) {
				checkwin++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

				printf("������\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("����\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			cur = cur->next;
		}
		if (checkwin == 0) {		//������� ���ÿ� ���߿���
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("\n�¸�!!");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf("\n%d�� ȹ��\n\n", (int)((float)betm * bet));
			money += (int)((float)betm * bet);
			profit += (int)((float)betm * bet) - betm;

		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n�й�....\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			profit -= betm;
		}


		betgame = cur = NULL;
		list = current = NULL;
		system("pause");
		system("cls");
	}
	return;
}

GAME* makegame() {
	int hometeam;
	int awayteam;
	GAME* newnode;
	newnode = (GAME*)malloc(sizeof(GAME));
	hometeam = rand() % 15;		//Ȩ�� �������� ����
	newnode->home = hometeam;
	while (1) {
		awayteam = rand() % 15;		//������ �������� ����
		if (hometeam != awayteam)break;
	}
	newnode->away = awayteam;	//Ȩ���� �������� �·��� ���� ���� �ο�
	newnode->h_win = (float)(bigteam[hometeam].homewin * 100) / (bigteam[hometeam].homewin + (bigteam[awayteam].win - bigteam[awayteam].homewin));
	newnode->a_win = (float)(bigteam[awayteam].homewin * 100) / (bigteam[hometeam].homewin + (bigteam[awayteam].win - bigteam[awayteam].homewin));
	newnode->h_bet = (newnode->a_win + newnode->h_win) / newnode->h_win * 0.95;
	newnode->a_bet = (newnode->a_win + newnode->h_win) / newnode->a_win * 0.95;


	newnode->next = NULL;
	return newnode;
}

int* playgame(USER* node) {
	int score[2] = { 0 };
	int randum[100] = { 0 };
	for (int i = 0; i < (int)node->betwin; i++)randum[i]++;		//����ڰ� ������ ���� �·���ŭ �迭�� 1����
	while (1) {
		score[0] = 0;
		score[1] = 0;
		for (int i = 0; i < rand() % 5 + 1; i++) {
			if (randum[rand() % 100] == 1)score[0]++;
			else score[1]++;
		}
		if (score[0] != score[1])break;
	}
	return score;

}

void makerank() {
	FILE* fp = NULL;
	SEASONRANK* current;
	int rank;
	for (int i = 0; i < 3; i++) {
		switch (i) {		//���� ���� ���Ͽ� ����
		case 0:fp = fopen("19~20���� ����.txt", "w");
			break;
		case 1:fp = fopen("20~21���� ����.txt", "w");
			break;
		case 2:fp = fopen("21~22���� ����.txt", "w");
			break;
		}
		current = season[i];
		rank = 1;
		fprintf(fp, "\n\t\t<<%d~%d���� ����>>", i + 19, i + 20);
		fprintf(fp, "\n\n\n����\t��\t��\t��\t��\t����\t����/����\n");
		while (current != NULL) {
			fprintf(fp, "%d\t%s\t%d\t%d\t%d\t%d", rank, current->team_name, current->win, current->draw, current->lose, current->point);
			if (rank < 5)fprintf(fp, "\tè�Ǿ𽺸��� ���� ����\n");
			else if (rank == 5 || rank == 6)fprintf(fp, "\t�����ĸ��� ���� ����\n");
			else if (rank == 7)fprintf(fp, "\t������ ���۷������� ������\n");
			else if (rank > 17)fprintf(fp, "\t����\n");
			else fprintf(fp, "\n");
			current = current->next;
			rank++;
		}
		fclose(fp);
	}
}

void printproto() {
	printf("\t\t\t\t\t  ----------------------------------\n");
	printf("\t\t\t\t\t          <<���� ���� ����>>\n");
	printf("\t\t\t\t\t  ----------------------------------\n\n");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t�ҹ�����Ʈ���� �̿���\n");
	printf("\t\t\t\t       5�� ������ ¡�� �Ǵ� 5õ���� ������ ����\n\n");
	printf("\t\t\t\t\t     �Ҿ����� �����ϰ� ��⼼��!\n");
	printf("\t\t\t\t\t\t1336 �����ߵ�ġ�Ἶ��\n");
	printf("\t\t\t\t\t   1899-1119�ҹ�����������Ű���\n\n\n\n\n\n\n\n\n\n\n");
	system("pause");
	system("cls");
}