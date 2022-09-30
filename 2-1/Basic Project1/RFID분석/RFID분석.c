#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

typedef struct taginfo {	//RFID_Data에서 읽어온 태그정보를 저장하는 연결리스트 구조체
	char id[27];
	float rssi;
	double identifiedTime;
	struct taginfo* next;
}TAGINFO;

typedef struct analysisresult {	//태그들을 분석한 정보들을 저장하는 구조체
	char id[27];
	double avgrssi;
	double avgInterval;
	double maxRSSI;
	double minRSSI;
	int count;
}ARESULT;

ARESULT target;			//타겟태그 정보분석값
ARESULT refers[60];		//모든태그들의 정보분석값

char targetID[27] = "0x35E0170044CF0D590000F5A5";	//타겟태그

char referenceIDs[60][27] = {	//태그들의 아이디
	"0x35E0170044CF0D590000F544","0x35E0170044CF0D590000F543","0x35E0170044CF0D590000F542","0x35E0170044CF0D590000F551","0x35E0170044CF0D590000F550","0x35E0170044CF0D590000F54F",
	"0x35E0170044CF0D590000F61D","0x35E0170044CF0D590000F61C","0x35E0170044CF0D590000F61B","0x35E0170044CF0D590000F61A","0x35E0170044CF0D590000F629","0x35E0170044CF0D590000F628",
	"0x35E0170044CF0D590000F54E","0x35E0170044CF0D590000F55D","0x35E0170044CF0D590000F55C","0x35E0170044CF0D590000F55B","0x35E0170044CF0D590000F55A","0x35E0170044CF0D590000F569",
	"0x35E0170044CF0D590000F627","0x35E0170044CF0D590000F626","0x35E0170044CF0D590000F635","0x35E0170044CF0D590000F634","0x35E0170044CF0D590000F633","0x35E0170044CF0D590000F632",
	"0x35E0170044CF0D590000F568","0x35E0170044CF0D590000F567","0x35E0170044CF0D590000F566","0x35E0170044CF0D590000F575","0x35E0170044CF0D590000F574","0x35E0170044CF0D590000F573",
	"0x35E0170044CF0D590000F641","0x35E0170044CF0D590000F640","0x35E0170044CF0D590000F63F","0x35E0170044CF0D590000F63E","0x35E0170044CF0D590000F64D","0x35E0170044CF0D590000F64C",
	"0x35E0170044CF0D590000F572","0x35E0170044CF0D590000F581","0x35E0170044CF0D590000F580","0x35E0170044CF0D590000F57F","0x35E0170044CF0D590000F57E","0x35E0170044CF0D590000F58D",
	"0x35E0170044CF0D590000F64B","0x35E0170044CF0D590000F64A","0x35E0170044CF0D590000F659","0x35E0170044CF0D590000F658","0x35E0170044CF0D590000F657","0x35E0170044CF0D590000F656",
	"0x35E0170044CF0D590000F58C","0x35E0170044CF0D590000F58B","0x35E0170044CF0D590000F58A","0x35E0170044CF0D590000F599","0x35E0170044CF0D590000F598","0x35E0170044CF0D590000F597",
	"0x35E0170044CF0D590000F603","0x35E0170044CF0D590000F5F8","0x35E0170044CF0D590000F5F7","0x35E0170044CF0D590000F5F6","0x35E0170044CF0D590000F605","0x35E0170044CF0D590000F604"
};

int referecePoints[60][2] = {		//태그들의 위치좌표
	{ 7, 1 },{ 22, 1 },{ 37, 1 },{ 52, 1 },{ 67, 1 },{ 81, 1 },
	{ 101, 1 },{ 116, 1 },{ 131, 1 },{ 146, 1 },{ 161, 1 },{ 176, 1 },
	{ 7, 41 },{ 22, 41 },{ 37, 41 },{ 52, 41 },{ 67, 41 },{ 81, 41 },
	{ 101, 41 },{ 116, 41 },{ 131, 41 },{ 146, 41 },{ 161, 41 },{ 176, 41 },
	{ 7, 80 },{ 22, 80 },{ 37, 80 },{ 52, 80 },{ 67, 80 },{ 81, 80 },
	{ 101, 80 },{ 116, 80 },{ 131, 80 },{ 146, 80 },{ 161, 80 },{ 176, 80 },
	{ 7, 115 },{ 22, 115 },{ 37, 115 },{ 52, 115 },{ 67, 115 },{ 81, 115 },
	{ 101, 115 },{ 116, 115 },{ 131, 115 },{ 146, 115 },{ 161, 115 },{ 176, 115 },
	{ 7, 144 },{ 22, 144 },{ 37, 144 },{ 52, 144 },{ 67, 144 },{ 81, 144 },
	{ 101, 144 },{ 116, 144 },{ 131, 144 },{ 146, 144 },{ 161, 144 },{ 176, 144 }
};

TAGINFO* stringSplit(TAGINFO* head, char data[]);	//읽은 파일을 연결리스트에 저장하는 함수
void TagAnalysis(TAGINFO* head);		//RFID_Data에 있는 태그들 분석하는 함수
void TargetAnalysis(TAGINFO* head);		//타겟태그 분석하는 함수
int chooce();			//메뉴 선택함수
void printTag();		//태그들의 분석값을 모두 출력하는 함수
void printtarget();		//타겟태그의 분석값을 출력
void targetsearch();	//타겟태그의 위치를 예상하는 함수

void main() {
	char str[300];
	FILE* fp;
	TAGINFO* list = NULL;
	int num;

	fp = fopen("RFID_Data.txt", "r");	//RFID_Data.txt파일 읽기

	while (!feof(fp)) {
		fgets(str, 299, fp);
		list = stringSplit(list, str);
	}

	TargetAnalysis(list);
	TagAnalysis(list);

	while (1) {
		num = choose();
		switch (num) {
		case 1:		//참조태그들의 정보 분석 값 출력 
			printTag();
			break;
		case 2:		//타겟 태그의 정보 분석 값 출력 
			printtarget();
			break;
		case 3:		//타겟의 위치 예측 값 출력 
			targetsearch();
			break;
		case 4:		//종료
			printf("\n\n\n\n프로그램 종료......\n\n\n\n");
			exit(-1);
		default:
			printf("다시 입력 하세요!!\n\n\n\n");
			break;
		}
		system("pause");
		system("cls");
	}
}

TAGINFO* stringSplit(TAGINFO* head, char data[]) {
	char* result ;
	TAGINFO* node;
	double time = 0;

	node = (TAGINFO*)malloc(sizeof(TAGINFO));

	result = strtok(data, " =,T");
	while (result != NULL) {
		if ((strcmp(result, "tag_id")) == 0) {	//태그 아이디 추출
			result = strtok(NULL, " =,T");
			strcpy(node->id, result);
		}
		else if ((strcmp(result, "rssi")) == 0) {	//RSSI값 추출
			result = strtok(NULL, " =,T");
			node->rssi = atof(result);
		}
		else if ((strcmp(result, "time")) == 0) {	//시간 추출
			result = strtok(NULL, " =,T");
			result = strtok(NULL, " =,T\n");
			time += atof(strtok(result, ":.\n")) * 3600;	//시간을 초단위로 변환
			time += atof(strtok(NULL, ":.\n")) * 60;
			time += atof(strtok(NULL, ":.\n"));
			time += atof(strtok(NULL, ":.\n")) / 1000;
			node->identifiedTime = time;
			break;
		}
		else result = strtok(NULL, " =,T");
	}
	node->next = head;
	head = node;
	return head;
}

int choose() {
	int _num;
	printf("=======================================================\n");
	printf("RFID Tag Information Analysis based Localization System\n");
	printf("=======================================================\n");
	printf("1.Reference Tag Analysis\n");
	printf("2.Target Tag Analysis\n");
	printf("3.Estimation of Target Position\n");
	printf("4.Quit\n\n");
	printf("choose menu:");
	scanf("%d", &_num);
	return _num;
}

void TargetAnalysis(TAGINFO* head) {
	double time = 0;

	strcpy(target.id, targetID);	//타겟태그 아이디 저장
	target.avgrssi = 0;				//타겟태그의 정보변수들을 초기화
	target.count = 0;
	target.maxRSSI = 0;
	target.minRSSI = 99999;
	target.avgInterval = 0;
	while (head != NULL) {
		if (strcmp(head->id, target.id) == 0) {		//타겟태그가 맞는지 확인
			if (time == 0)time = head->identifiedTime;	//간격을 구하기위한 시간값이 하나면 시간저장
			else {
				target.avgInterval += (time - head->identifiedTime);	//시간과 시간사이의 간격들을 저장
				time = head->identifiedTime;
			}
			if (target.maxRSSI < head->rssi) target.maxRSSI = head->rssi;	//더큰 RSSI값을 저장
			if (target.minRSSI > head->rssi)target.minRSSI = head->rssi;	//더작은 RSSI값을 저장
			target.count++;
			target.avgrssi += head->rssi;		//RSSI갑들의 합
		}
		head = head->next;
	}
	target.avgrssi = target.avgrssi / target.count;		//RSSI값들의 합을 갯수로 나누어 평균RSSI값을 구함
	target.avgInterval /= (target.count - 1);			//간격들을 갯수-1 로 나누어 시간간격들의 평균을 구함
	return;
}

void TagAnalysis(TAGINFO* head) {
	int i;
	double time=0;
	TAGINFO* current=NULL;

	for (i = 0; i < 60; i++) {		//60개의 referenceTag들을 TargetTag분석과 같은 방법으로 분석
		strcpy(refers[i].id, referenceIDs[i]);
		current = head;
		time = 0;
		refers[i].avgrssi = 0;
		refers[i].count = 0;
		refers[i].maxRSSI = 0;
		refers[i].minRSSI = 99999;
		refers[i].avgInterval = 0;
		while (current != NULL) {
			if (strcmp(current->id, refers[i].id) == 0) {
				if (time == 0)time = current->identifiedTime;
				else {
					refers[i].avgInterval += time - current->identifiedTime;
					time = current->identifiedTime;
				}
				if (refers[i].maxRSSI < current->rssi) refers[i].maxRSSI = current->rssi;
				if (refers[i].minRSSI > current->rssi)refers[i].minRSSI = current->rssi;
				refers[i].count++;
				refers[i].avgrssi += current->rssi;

			}
			current = current->next;
		}
		if (refers[i].avgrssi == 0)refers[i].minRSSI = 0;
		else refers[i].avgrssi /= refers[i].count;
		if (time != 0)refers[i].avgInterval /= (refers[i].count - 1);
		}
		return;
	}

void printTag(){
	int j;
	for (j = 0; j < 60; j++) {	//60개의 referenceTag들의 분석값을 모두 출력
		printf("ID:%s\tavgrssi:%.2f\n", refers[j].id, refers[j].avgrssi);
		printf("maxRSSI:%.0f\tminRSSI:%.0f\tavgInterval:%.3f\tcount:%d\n\n", refers[j].maxRSSI, refers[j].minRSSI, refers[j].avgInterval,refers[j].count);
	}
	printf("\n\n\n");
	return;
}

void printtarget(){
	printf("\ntargetID:%s\ttargetavgRSSI:%.2f\n", target.id, target.avgrssi);	//TargetTag의 정보 분석값출력
	printf("target maxRSSI:%.0f\ttarget minRSSI:%.0f\ttarget avgInterval:%.3f\tcount:%d\n", target.maxRSSI, target.minRSSI, target.avgInterval,target.count);
	printf("\n\n\n");
	return;
}

void targetsearch() {
	int N,i,j,rs,best,k;	
	int x = 0, y = 0;		//좌표를 저장할 변수
	int check[60]={0};		//선정되었는지 확인하는 변수
	while (1) {
		printf("\n예측할 Reference Tag갯수:");
		scanf("%d", &N);
		if (N < 55)break;
		printf("다시 입력하세요!!\n");
	}

	for (i = 0; i < N; i++) {		//가장 가까운 RSSi값 입력된 N개 선정
		best = 999999;	//가장 RSSI값이 가까운 값을 저장할 변수 초기화
		k = -1;			//배열의 위치를 저장하는 변수 초기화
		for (j = 0; j < 60; j++) {		//모든 분석값 비교
			if (refers[j].avgrssi != 0 && check[j] == 0) {	//분석값이 있고 이미 선정되었는지 확인
				rs = target.avgrssi - refers[j].avgrssi;	//평균RSSI의 거리 확인
				if (rs < 0)rs *= -1;		
				if (best > rs) {	//현재까지 가장 가까운 값보다 가까운지 확인
					best = rs;		
					k = j;			//가장 가까운 값의 배열위치 저장
				}
			}
		}
		check[k] = 1;	//선정이 끝나면 저장된 가장가까운 값의 배열위치에 1을 삽입하여 확인
	}

	for (i = 0; i < 60; i++) {
		if (check[i] == 1) {	
			x += referecePoints[i][0];	//x값을 모두 더함
			y += referecePoints[i][1];	//y값을 모두 더함
		}
	}
	x /= N;		//선정한 갯수N개로 나누어 평균을 구함
	y /= N;
	printf("\n\nTargetTag의 위치예측 좌표: { %d , %d }\n\n\n",x,y);
	return;
}
