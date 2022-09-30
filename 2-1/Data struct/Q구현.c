#include<stdio.h>
#include<windows.h>
#define MAX 100
#define true 1
#define false 0

int Q[MAX]={0};
int front=-1,rear=-1;

void enQueue();
void deQueue();
void print();
int isempty();


void main(){
int num;
while(1){
	printf("1.enqueue\n2.dequeue\n3.print\n4.exit\nenter:");
	scanf("%d",&num);
	switch(num){
		case 1:enQueue();
		break;
		case 2:deQueue();
		break;
		case 3:print();
		break;
		default:exit (-1);
	}
	system("pause");
	system("cls");
}
}

void enQueue(){
	
	int data;
	printf("Enter:");
	scanf("%d",&data);
	Q[++rear%100]=data;
	return;
}

void deQueue(){
	
	if(isempty()==1)printf("Empty!!!!!\n");
	else printf("%d\n",Q[++front%100]);
	return;
}

void print(){
	int i;
	if(isempty()==1){
		printf("Empty!!!!!\n");
		return;
	}
	for(i=front+1;i<=rear;i++)printf("%d ",Q[i%100]);
	printf("\n");
	return;
}


int isempty(){
	if(rear==front)return true;
	else return false;
}
