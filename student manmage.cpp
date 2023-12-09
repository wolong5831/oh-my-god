#include"studentManmage.h"

void welcome()
{
	printf("**********************************\n");
	printf("**\t学生信息管理系统\t**\n");
	printf("**********************************\n");
	printf("**\t选择功能列表\t\t**\n"); 
	printf("**********************************\n");
	printf("*\t1.录入学生信息\t\t*\n");
	printf("*\t2.打印学生信息\t\t*\n");
	printf("*\t3.统计学生人数\t\t*\n");
	printf("*\t4.查找学生信息\t\t*\n");
	printf("*\t5.修改学生信息\t\t*\n");
	printf("*\t6.删除学生信息\t\t*\n");
	printf("*\t7.按成绩排序\t\t*\n");
	printf("*\t8.退出系统\t\t*\n");
	printf("**********************************\n");
}

int main()
{
	//创建头节点
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	loadstudent(head);

	while (1)
	{
		welcome();

		char c = _getch();

		switch (c)
		{
		case'1':
			//录入学生信息
			intputStudent(head);
			break;
		case'2':
			//打印学生信息
			printStudent(head);
			break;
		case'3':
			//统计学生人数
			countstudent(head);
			break;
		case'4':
			//查找学生信息
			findstudent(head);
			break;
		case'5':
			//修改学生信息
			modifystudent(head);
			break;
		case'6':
			//删除学生信息
			deletestudent(head);
			break;
		case'7':
			//按成绩排序
			sortstudent(head);
			break;
		case'8':
			//退出系统
			system("cls");
			printf("Goodbye!");
			exit(0);
			break;
		default:
			printf("请重新输入：\n");
			break;
		}
	}
	
	return 0;
}

void intputStudent(Node * head)
{
	Node* fresh = (Node*)malloc(sizeof(Node));
	fresh->next = NULL;
	printf("请输入学生的学号，姓名，成绩");
	scanf("%d%s%d", &fresh->student.stunum, &fresh->student.name, &fresh->student.score);

	Node* move = head;
	while (move->next != NULL)
	{
		move = move->next;
	}
	//将信息插入尾部
	move->next = fresh;
	savestudent(head);//保存输入的信息
	//暂停程序
	system("pause");
	//清空控制台
	system("cls");
}

void printStudent(Node* head)
{
	Node* move = head->next;
	while (move != NULL)
	{
		printf("学号：%d 姓名：%s 成绩：%d\n", move->student.stunum, move->student.name, move->student.score);
		move = move->next;
	}
	//暂停程序
	system("pause");
	//清空控制台
	system("cls");
}

void countstudent(Node* head)
{
	int count = 1;
	Node* move = head->next;
	while (move != NULL)
	{
		count++;
		move = move->next;
	}
	printf("学生总人数为%d\n", count-1);
}

void findstudent(Node* head)
{
	printf("请输入想要查找的学生的学号：\n");
	int stuNum;
	scanf("%d", &stuNum);
	Node* move = head->next;
	while (move != NULL)
	{
		if (stuNum == move->student.stunum)
		{
			printf("学号：%d 姓名：%s 成绩：%d\n", move->student.stunum, move->student.name, move->student.score);
			return;
		}
		move = move->next;
	}
	printf("未找到学生信息");
	//暂停程序
	system("pause");
	//清空控制台
	system("cls");
}

void savestudent(Node* head)
{
	//打开文件
	FILE* file = fopen("./stu.info", "w");
	Node* move = head->next;
	while (move != NULL)
	{
		if (fwrite(&move->student, sizeof(student), 1, file) != 1)
		{
			printf("写入失败\n");
			return;
		}
		move = move->next;
	}
	fclose(file);
}

void loadstudent(Node* head)
{
	//读取文件
	FILE* file = fopen("./stu.info", "r");
	if (!file)
	{
		printf("没有学生信息，跳过读取");
		return;
	}
	Node* fresh = (Node*)malloc(sizeof(Node));
	fresh->next = NULL;
	Node* move = head;
	while(fread(&fresh->student, sizeof(student), 1, file)==1)
	{
		move->next = fresh;
		move = fresh;
		fresh = (Node*)malloc(sizeof(student));
		fresh->next = NULL;
	}
	free(fresh);
	fclose(file);
	printf("读取成功\n");
}

void modifystudent(Node* head)
{
	printf("请输入需要修改的学生的学号：\n");
	int stuSum;
	scanf("%d", &stuSum);
	Node* move = head->next;
	while (move != NULL)
	{
		if (move->student.stunum == stuSum)
		{
			printf("请输入学生姓名，成绩:\n");
			scanf("%s%d", move->student.name, &move->student.score);
			savestudent(head);
			printf("修改成功");
			//暂停程序
			system("pause");
			//清空控制台
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("未找到学生信息");
	//暂停程序
	system("pause");
	//清空控制台
	system("cls");
}

void deletestudent(Node* head)
{
	printf("请输入要删除的学生学号\n");
	int stuSum = 0;
	scanf("%d", &stuSum);
	Node* move = head;
	while (move->next != NULL)
	{
		if (move->next->student.stunum == stuSum)
		{
			Node* tmp = move->next;
			move->next = move->next->next;
			free(tmp);
			tmp = NULL;
			savestudent(head);
			printf("删除成功\n");
			return;
			//暂停程序
			system("pause");
			//清空控制台
			system("cls");
		}
		move = move->next;
	}
	printf("未找到学生信息\n");
	//暂停程序
	system("pause");
	//清空控制台
	system("cls");
}

void sortstudent(Node* head)
{
	Node* save = NULL;
	Node* move = NULL;
	for (Node* turn = head->next; turn->next != NULL; turn = turn->next)
	{
		for (move = head->next; move->next != save; move = move->next)
		{
			if (move->student.score > move->next->student.score)
			{
				STD temp = move->student;
				move->student = move->next->student;
				move->next->student = temp;
			}
		}
		save = move;
	}
	printStudent(head);
}