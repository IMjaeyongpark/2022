#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define UP 72
#define DOWN 80

typedef struct team {		//분석하는 시즌에 존재하는 팀의 정보
	char team_name[3];		//팀 이름
	int win;				//승
	int draw;				//무
	int lose;				//패
	int point;				//승점
}TEAM;

typedef struct bigteam {	//분석하는 모든 시즌에 존재하는 팀의 정보
	char team_name[3];		//팀이름
	int homewin;			//홈 승
	int win;				//승
	int homedraw;			//홈 무
	int draw;				//무
	int homelose;			//홈 패
	int lose;				//패
	int goal;				//득점
	int losegoal;			//실점
}BIGTEAM;

typedef struct seasonrank {	//분석한 시즌의 팀들의 순위
	char team_name[3];
	int win;
	int draw;
	int lose;
	int point;
	struct seasonrank* next;
}SEASONRANK;

typedef struct game {		//가상 베팅 게임에서의 가상 경기 정보
	int home;
	int away;
	float h_bet;			//홈 배당
	float a_bet;			//원정 배당	
	float h_win;			//홈 승률
	float a_win;			//원정 승률
	struct game* next;
}GAME;

typedef struct userbet {	//유저가 선택한 가상 경기
	int bett;				//유저가 선택한 팀
	float betwin;			//유저가 선택한 경기의 승률
	int gam;				//선택한 팀이 홈인지 원정인지
	struct userbet* next;
}USER;


TEAM analysis[20];			//분석하는 시즌에 존재하는 팀의 정보를 저장하는 배열
BIGTEAM bigteam[15];		//분석하는 모든 시즌의 존재하는 팀의 정보배열
SEASONRANK* season[3] = { NULL };	//3개의 시즌별 순위를 저장하는 연결리스트

void teamread(char teamdata[]);	//분석하는 시즌에 존재하는 팀을 저장하는 함수
void stringSplit(char data[]);	//파일을 읽고 정보를 저장하는 함수
void seasonrank(int se);		//분석한 시즌에 팀들의 승점을 사용하여 내림차순으로 연결리스트에 저장하는 함수
void print_rank();				//선택한 시즌의 순위를 풀력하는 함수
int select_menu();				//사용자가 사용할 메뉴를 출력하는 함수
void big_team_name();			//분석하는 모든 시즌에 존재하는 팀들의 이름을 삽입하고 정보들을 초기화 시키는 함수
int check_bigteam(char* te_name);	//정보를 저장할때 모든시즌에 존재하는 팀인지 확인하는 함수
void bigteam_analysis();		//모든 시즌에 존재하는 팀들의 정보를 출력하는 함수
void proto();					//가상 베팅 게임 함수
GAME* makegame();				//가상 베팅 게임에서 사용할 가상경기를 만드는 함수
int* playgame(USER* node);		//가상 경기의 승패를 정하는 함수
void makerank();				//순위를 메모장에 저장하는 함수
void printproto();
int keyControl();

int main() {
	srand(time(NULL));
	FILE* fp = NULL;
	char str[100] = { "\0" };		//파일 한줄을 저장하는 문자배열
	int i = 0;
	int select;

	big_team_name();
	for (int i = 0; i < 3; i++) {	//3개의 파일을 하나씩 읽음	
		switch (i) {
		case 0:fp = fopen("19-20.txt", "r");
			break;
		case 1:fp = fopen("20-21.txt", "r");
			break;
		case 2:fp = fopen("21-22.txt", "r");
			break;
		}
		fgets(str, 99, fp);		//파일의 한줄을 읽음
		teamread(str);
		while (!feof(fp)) {		//파일의 끝까지 한줄씩 읽음
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
		case 4:printf("\n\n\n프로그램 종료\n\n\n");
			exit(-1);
		default:printf("\n\n\n다시 입력 하세요!!\n\n\n");
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


void big_team_name() {			//모든 시즌에 존재하는 팀의 이름이 담겨있는 배열
	char* bigname[15] = { "LIV","MCI","MUN","CHE" ,"LEI","TOT" ,"WOL","ARS" ,"SOU","EVE","NEW","CRY","BHA","WHU","AVL" };

	for (int i = 0; i < 15; i++) {		//배열 초기화
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
	home = check_bigteam(analysis[i].team_name);	//모든 시즌에 존재하는 팀인지 확인
	j = 0;
	while (score != NULL) {
		goal1 = 0;
		goal2 = 0;
		if (j != i) {
			sscanf(score, "%d-%d", &goal1, &goal2);	//스코어를 읽음
			away = check_bigteam(analysis[j].team_name);
			if (goal1 > goal2) {	//홈팀이 점수가 더 높을때
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
			else if (goal1 < goal2) {	//원정팀이 점수가 더 높을때
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
			else {			//점수가 같을때
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
		if (strcmp(te_name, bigteam[i].team_name) == 0)return i;	//모든 시즌에 존재하는 팀의 배열을 하나씩 비교하고 이름이 같으면 배열의 순서 반환
	}
	return -1;
}

void seasonrank(int se) {
	for (int i = 0; i < 20; i++) {
		SEASONRANK* newnode, * current = NULL, * pre = NULL;
		current = pre = season[se];
		newnode = (SEASONRANK*)malloc(sizeof(SEASONRANK));		//분석하는 시즌의 팀의 정보 저장
		strcpy(newnode->team_name, analysis[i].team_name);
		newnode->win = analysis[i].win;
		newnode->draw = analysis[i].draw;
		newnode->lose = analysis[i].lose;
		newnode->point = analysis[i].point;
		while ((current != NULL) && (current->point >= newnode->point)) {	//내림차순으로 정렬
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
		printf("프리미어 리그 분석 및 가상 베팅게임\n");
		printf("-----------------------------------\n\n");
		printf("1.시즌별 순위 출력\n");
		printf("2.19~22시즌 팀별 정보 출력\n");
		printf("3.가상 베팅 게임\n");
		printf("4.종료\n\n");

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
		printf("시즌 선택\n\n1.19~20시즌\n2.20~21시즌\n3.21~22시즌\n\n시즌 선택:");
		scanf("%d", &sel);		//시즌 선택
		if (sel > 0 && sel < 4)break;
		printf("다시입력!!\n");
		system("pause");
		system("cls");
	}
	system("cls");
	current = season[sel - 1];
	rank = 1;
	printf("\n\t\t<<%d~%d시즌 순위>>", sel + 18, sel + 19);
	printf("\n\n\n순위\t팀\t승\t무\t패\t승점\t진출/강등\n");
	while (current != NULL) {		//선택한 시즌의 팀별 순위 및 정보 출력
		printf("%d\t%s\t%d\t%d\t%d\t%d", rank, current->team_name, current->win, current->draw, current->lose, current->point);
		if (rank < 5) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
			printf("\t챔피언스리그 조별 리그\n");		//순위에 따라 진출 및 강등 여부 출력
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (rank == 5 || rank == 6) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			printf("\t유로파리그 조별 리그\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (rank == 7) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("\t유로파 컨퍼런스리그 예선전\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (rank > 17) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\t강등\n");
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
		printf("\n19~22시즌 전적\n\n");
		for (int i = 0; i < 15; i++)printf("%d:%s\n", i + 1, bigteam[i].team_name);	//분석한 팀들의 이름 출력
		printf("\n팀 선택:");
		scanf("%d", &a);		//팀 선택
		if (a < 16)break;
		printf("\n\n\n다시 입력하세요!!\n\n\n\n");
		system("pause");
		system("cls");
	}
	a--;
	system("cls");
	printf("\n19~22시즌 전적\n");		//선택한 팀의 19~22시즌 정보를 출력
	printf("\n팀이름: %s\n\n홈 승\t홈 무\t홈 패\t승\t무\t패\n", bigteam[a].team_name);
	printf("%d\t%d\t%d\t%d\t%d\t%d\n", bigteam[a].homewin, bigteam[a].homedraw, bigteam[a].homelose, bigteam[a].win, bigteam[a].draw, bigteam[a].lose);
	printf("\n골\t실점\t홈 승률\t승률\n");
	hw = (float)bigteam[a].homewin / (bigteam[a].homedraw + bigteam[a].homelose + bigteam[a].homewin) * 100;
	w = (float)bigteam[a].win / (bigteam[a].draw + bigteam[a].lose + bigteam[a].win) * 100;
	printf("%d\t%d\t%.2f%%\t%.2f%%\n", bigteam[a].goal, bigteam[a].losegoal, hw, w);
	return;
}

void proto() {
	int money = 0;		//사용자의 가상화폐
	int plusmoney = 0;	//사용자가 충전한 총 가상화폐
	int plus;			//사용자가 충전한 가상화폐
	int betm;			//사용자가 베팅한 가상화폐
	int selteam;		//사용가자 선택한 가상경기의 팀
	int selgame;		//사용자가 선택한 가상경기
	float bet;			//사용자가 선택한 가상경기들의 배당률
	long long profit = 0;	//사용자의 손익
	int result;			//사용자가 선택한 경기의 결과
	int checkwin;		//사용가의 적중여부 
	int* score;

	USER* betgame = NULL, * new = NULL, * cur = NULL;			//사용자가 선택한 경기를 저장하는 연결리스트
	GAME* list = NULL, * current = NULL, * newnode = NULL;		//가상경기 정보를 저장하는 연결리스트

	system("cls");

	while (1) {

		printf("\n1336 도박중독치료센터\n\n\n충전할 금액을 입력하세요(게임 종료:-1):");
		scanf("%d", &plus);
		if (plus == -1) {
			system("cls");
			printf("\n\n\t손익:%d\n\n\n", profit);
			return;
		}
		money += plus;
		plusmoney += plus;
		system("cls");
		list = current = NULL;
		int gamecount = rand() % 4 + 5;		//가상경기의 갯수 랜덤으로 선택
		for (int i = 0; i < gamecount; i++) {	//가상경기 생성하여 연결리스트에 저장
			newnode = makegame();
			if (list == NULL) list = current = newnode;
			else {
				current->next = newnode;
				current = newnode;
			}
		}
		int game[8] = { 0 };	//사용자가 가상경기를 선택했는지 여부를 확인하는 배열
		while (1) {
			betm = 0;
			bet = 1;
			printf("\n1336 도박중독치료센터\n\n현재 금액:%d\t\t충전금액:%d\n배당:%.2f\t적중시 금액:%d\n\n", money, plusmoney, bet, (int)(betm * bet));
			printf(" home\t\t\taway\n\n");
			current = list;
			for (int k = 1; current != NULL; k++) {		//가상경기의 정보 출력
				printf("%d.%s\t%.2f:%.2f\t%s\n", k, bigteam[current->home].team_name, current->h_bet, current->a_bet, bigteam[current->away]);
				current = current->next;
			}
			printf("\n배팅할 금액 선택:");
			scanf("%d", &betm);
			if (money >= betm && betm > -1)break;
			printf("\n\n\n다시 입력하세요!!\n\n\n");
			system("pause");
			system("cls");
		}
		money -= betm;
		system("cls");
		selgame = 0;
		for (int k = 0; k < gamecount && selgame != -1; k++) {
			current = list;
			while (1) {
				printf("\n1336 도박중독치료센터\n\n현재 금액:%d\t\t충전금액:%d\n배당:%.2f\t적중시 금액:%d\n\n", money, plusmoney, bet, (int)(betm * bet));
				printf(" home\t\t\taway\n\n");
				current = list;
				for (int k = 1; current != NULL; k++) {
					printf("%d.%s\t%.2f:%.2f\t%s\n", k, bigteam[current->home].team_name, current->h_bet, current->a_bet, bigteam[current->away]);
					current = current->next;
				}
				printf("\n경기를 선택하세요(배팅 종료:-1):");
				scanf("%d", &selgame);
				if (selgame == -1) {
					break;
				}
				if (selgame > gamecount || selgame < -1) {
					printf("\n\n다시 입력하세요!!\n\n\n");
					system("pause");
					system("cls");
				}
				else if (game[selgame] == 1) {
					printf("\n\n이미 선택한 경기입니다!\n\n\n");
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
				printf("\n1.홈팀 베팅\n2.원정팀 베팅\n\n");
				printf("베팅할 팀을 선택하세요:");
				scanf("%d", &selteam);
				printf("\n\n");
				if (selteam == 1 || selteam == 2)break;
				printf("\n\n다시 입력하세요!!\n\n");
			}

			if (selgame != -1) {		//사용자가 선택한 경기를 노드를 생성하여 정보들을 저장
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
		while (cur != NULL) {		//사용자가 선택한 경기들의 승패 여부 출력
			current = list;
			score = playgame(cur);
			if (score[0] > score[1])result = 1;
			else if (score[0] < score[1])result = 2;
			if (result == 1)printf("승\t");
			else if (result == 2)printf("패\t");
			if (result != cur->bett) checkwin++;
			for (int n = 1; n < cur->gam; n++)current = current->next;
			printf("%s\t%d : %d\t%s\t\t", bigteam[current->home].team_name,score[0],score[1], bigteam[current->away].team_name);
			if (result == 2)printf("승\t");
			else printf("패\t");
			if (result != cur->bett) {
				checkwin++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

				printf("미적중\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("적중\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			cur = cur->next;
		}
		if (checkwin == 0) {		//사용자의 베팅에 적중여부
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("\n승리!!");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf("\n%d원 획득\n\n", (int)((float)betm * bet));
			money += (int)((float)betm * bet);
			profit += (int)((float)betm * bet) - betm;

		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n패배....\n\n");
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
	hometeam = rand() % 15;		//홈팀 랜덤으로 선택
	newnode->home = hometeam;
	while (1) {
		awayteam = rand() % 15;		//원정팀 랜덤으로 선택
		if (hometeam != awayteam)break;
	}
	newnode->away = awayteam;	//홈팀과 원정팀의 승률을 통해 베당 부여
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
	for (int i = 0; i < (int)node->betwin; i++)randum[i]++;		//사용자가 선택한 팀의 승률만큼 배열에 1삽입
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
		switch (i) {		//시즌별 순위 파일에 저장
		case 0:fp = fopen("19~20시즌 순위.txt", "w");
			break;
		case 1:fp = fopen("20~21시즌 순위.txt", "w");
			break;
		case 2:fp = fopen("21~22시즌 순위.txt", "w");
			break;
		}
		current = season[i];
		rank = 1;
		fprintf(fp, "\n\t\t<<%d~%d시즌 순위>>", i + 19, i + 20);
		fprintf(fp, "\n\n\n순위\t팀\t승\t무\t패\t승점\t진출/강등\n");
		while (current != NULL) {
			fprintf(fp, "%d\t%s\t%d\t%d\t%d\t%d", rank, current->team_name, current->win, current->draw, current->lose, current->point);
			if (rank < 5)fprintf(fp, "\t챔피언스리그 조별 리그\n");
			else if (rank == 5 || rank == 6)fprintf(fp, "\t유로파리그 조별 리그\n");
			else if (rank == 7)fprintf(fp, "\t유로파 컨퍼런스리그 예선전\n");
			else if (rank > 17)fprintf(fp, "\t강등\n");
			else fprintf(fp, "\n");
			current = current->next;
			rank++;
		}
		fclose(fp);
	}
}

void printproto() {
	printf("\t\t\t\t\t  ----------------------------------\n");
	printf("\t\t\t\t\t          <<가상 베팅 게임>>\n");
	printf("\t\t\t\t\t  ----------------------------------\n\n");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t불법스포트토토 이용자\n");
	printf("\t\t\t\t       5년 이하의 징역 또는 5천만원 이하의 벌금\n\n");
	printf("\t\t\t\t\t     소액으로 건정하게 즐기세요!\n");
	printf("\t\t\t\t\t\t1336 도박중독치료센터\n");
	printf("\t\t\t\t\t   1899-1119불법스포츠토토신고센터\n\n\n\n\n\n\n\n\n\n\n");
	system("pause");
	system("cls");
}