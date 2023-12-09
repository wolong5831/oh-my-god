#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//学生信息
typedef struct student
{
	int stunum;
	char name[20];
	int score;
}STD;

//节点信息
typedef struct node
{
	STD student;
	struct node* next;
}Node;

void welcome();

void intputStudent(Node* head);

void printStudent(Node* head);

void countstudent(Node* head);

void findstudent(Node* head);

void savestudent(Node* head);

void loadstudent(Node* head);

void modifystudent(Node* head);

void deletestudent(Node* head);

void sortstudent(Node* head);