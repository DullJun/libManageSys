#ifndef _STUDENT_H
#define _STUDENT_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct Stu_info //学生信息的结构体
{
	int pwd;
	int num;
	int English;
	int Math;
	int Chinese;
	char name[16];
	int sign;
}stu_info;

typedef struct Stu_dlink  //学生链表
{
	stu_info student_info;
	struct Stu_dlink *prev;
	struct Stu_dlink *next;
}stu_dlink;

//////////////////////界面
void welcome_ui();
void choice_ui();
void register_login_ui();
void ensure_login_ui();
void student_ui();
void manager_ui();
//////////////////////student
stu_dlink *create_dlink(int num,int pwd,int English,int Math,int Chinese,char name[],int sign);
bool isExist(stu_dlink *head,int num);
bool insert_dlink_head(stu_dlink *head,int num,int pwd, int English,int Math,int Chinese,char name[],int sign);
void show_student_info(stu_dlink *head);
bool write_student_info(stu_dlink *head);
stu_dlink *read_student_info();
stu_dlink *stu_register();
stu_dlink *student_change_passwd(stu_dlink *p);
stu_dlink *student_login();

#endif