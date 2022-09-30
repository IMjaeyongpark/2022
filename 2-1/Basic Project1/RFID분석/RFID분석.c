#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

typedef struct taginfo {	//RFID_Data���� �о�� �±������� �����ϴ� ���Ḯ��Ʈ ����ü
	char id[27];
	float rssi;
	double identifiedTime;
	struct taginfo* next;
}TAGINFO;

typedef struct analysisresult {	//�±׵��� �м��� �������� �����ϴ� ����ü
	char id[27];
	double avgrssi;
	double avgInterval;
	double maxRSSI;
	double minRSSI;
	int count;
}ARESULT;

ARESULT target;			//Ÿ���±� �����м���
ARESULT refers[60];		//����±׵��� �����м���

char targetID[27] = "0x35E0170044CF0D590000F5A5";	//Ÿ���±�

char referenceIDs[60][27] = {	//�±׵��� ���̵�
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

int referecePoints[60][2] = {		//�±׵��� ��ġ��ǥ
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

TAGINFO* stringSplit(TAGINFO* head, char data[]);	//���� ������ ���Ḯ��Ʈ�� �����ϴ� �Լ�
void TagAnalysis(TAGINFO* head);		//RFID_Data�� �ִ� �±׵� �м��ϴ� �Լ�
void TargetAnalysis(TAGINFO* head);		//Ÿ���±� �м��ϴ� �Լ�
int chooce();			//�޴� �����Լ�
void printTag();		//�±׵��� �м����� ��� ����ϴ� �Լ�
void printtarget();		//Ÿ���±��� �м����� ���
void targetsearch();	//Ÿ���±��� ��ġ�� �����ϴ� �Լ�

void main() {
	char str[300];
	FILE* fp;
	TAGINFO* list = NULL;
	int num;

	fp = fopen("RFID_Data.txt", "r");	//RFID_Data.txt���� �б�

	while (!feof(fp)) {
		fgets(str, 299, fp);
		list = stringSplit(list, str);
	}

	TargetAnalysis(list);
	TagAnalysis(list);

	while (1) {
		num = choose();
		switch (num) {
		case 1:		//�����±׵��� ���� �м� �� ��� 
			printTag();
			break;
		case 2:		//Ÿ�� �±��� ���� �м� �� ��� 
			printtarget();
			break;
		case 3:		//Ÿ���� ��ġ ���� �� ��� 
			targetsearch();
			break;
		case 4:		//����
			printf("\n\n\n\n���α׷� ����......\n\n\n\n");
			exit(-1);
		default:
			printf("�ٽ� �Է� �ϼ���!!\n\n\n\n");
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
		if ((strcmp(result, "tag_id")) == 0) {	//�±� ���̵� ����
			result = strtok(NULL, " =,T");
			strcpy(node->id, result);
		}
		else if ((strcmp(result, "rssi")) == 0) {	//RSSI�� ����
			result = strtok(NULL, " =,T");
			node->rssi = atof(result);
		}
		else if ((strcmp(result, "time")) == 0) {	//�ð� ����
			result = strtok(NULL, " =,T");
			result = strtok(NULL, " =,T\n");
			time += atof(strtok(result, ":.\n")) * 3600;	//�ð��� �ʴ����� ��ȯ
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

	strcpy(target.id, targetID);	//Ÿ���±� ���̵� ����
	target.avgrssi = 0;				//Ÿ���±��� ������������ �ʱ�ȭ
	target.count = 0;
	target.maxRSSI = 0;
	target.minRSSI = 99999;
	target.avgInterval = 0;
	while (head != NULL) {
		if (strcmp(head->id, target.id) == 0) {		//Ÿ���±װ� �´��� Ȯ��
			if (time == 0)time = head->identifiedTime;	//������ ���ϱ����� �ð����� �ϳ��� �ð�����
			else {
				target.avgInterval += (time - head->identifiedTime);	//�ð��� �ð������� ���ݵ��� ����
				time = head->identifiedTime;
			}
			if (target.maxRSSI < head->rssi) target.maxRSSI = head->rssi;	//��ū RSSI���� ����
			if (target.minRSSI > head->rssi)target.minRSSI = head->rssi;	//������ RSSI���� ����
			target.count++;
			target.avgrssi += head->rssi;		//RSSI������ ��
		}
		head = head->next;
	}
	target.avgrssi = target.avgrssi / target.count;		//RSSI������ ���� ������ ������ ���RSSI���� ����
	target.avgInterval /= (target.count - 1);			//���ݵ��� ����-1 �� ������ �ð����ݵ��� ����� ����
	return;
}

void TagAnalysis(TAGINFO* head) {
	int i;
	double time=0;
	TAGINFO* current=NULL;

	for (i = 0; i < 60; i++) {		//60���� referenceTag���� TargetTag�м��� ���� ������� �м�
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
	for (j = 0; j < 60; j++) {	//60���� referenceTag���� �м����� ��� ���
		printf("ID:%s\tavgrssi:%.2f\n", refers[j].id, refers[j].avgrssi);
		printf("maxRSSI:%.0f\tminRSSI:%.0f\tavgInterval:%.3f\tcount:%d\n\n", refers[j].maxRSSI, refers[j].minRSSI, refers[j].avgInterval,refers[j].count);
	}
	printf("\n\n\n");
	return;
}

void printtarget(){
	printf("\ntargetID:%s\ttargetavgRSSI:%.2f\n", target.id, target.avgrssi);	//TargetTag�� ���� �м������
	printf("target maxRSSI:%.0f\ttarget minRSSI:%.0f\ttarget avgInterval:%.3f\tcount:%d\n", target.maxRSSI, target.minRSSI, target.avgInterval,target.count);
	printf("\n\n\n");
	return;
}

void targetsearch() {
	int N,i,j,rs,best,k;	
	int x = 0, y = 0;		//��ǥ�� ������ ����
	int check[60]={0};		//�����Ǿ����� Ȯ���ϴ� ����
	while (1) {
		printf("\n������ Reference Tag����:");
		scanf("%d", &N);
		if (N < 55)break;
		printf("�ٽ� �Է��ϼ���!!\n");
	}

	for (i = 0; i < N; i++) {		//���� ����� RSSi�� �Էµ� N�� ����
		best = 999999;	//���� RSSI���� ����� ���� ������ ���� �ʱ�ȭ
		k = -1;			//�迭�� ��ġ�� �����ϴ� ���� �ʱ�ȭ
		for (j = 0; j < 60; j++) {		//��� �м��� ��
			if (refers[j].avgrssi != 0 && check[j] == 0) {	//�м����� �ְ� �̹� �����Ǿ����� Ȯ��
				rs = target.avgrssi - refers[j].avgrssi;	//���RSSI�� �Ÿ� Ȯ��
				if (rs < 0)rs *= -1;		
				if (best > rs) {	//������� ���� ����� ������ ������� Ȯ��
					best = rs;		
					k = j;			//���� ����� ���� �迭��ġ ����
				}
			}
		}
		check[k] = 1;	//������ ������ ����� ���尡��� ���� �迭��ġ�� 1�� �����Ͽ� Ȯ��
	}

	for (i = 0; i < 60; i++) {
		if (check[i] == 1) {	
			x += referecePoints[i][0];	//x���� ��� ����
			y += referecePoints[i][1];	//y���� ��� ����
		}
	}
	x /= N;		//������ ����N���� ������ ����� ����
	y /= N;
	printf("\n\nTargetTag�� ��ġ���� ��ǥ: { %d , %d }\n\n\n",x,y);
	return;
}
