#ifndef _MANAGER_H
#define _MANAGER_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct Mag_info
{
	int num;
	int pwd;
	char name[16];
}mag_info;

typedef struct Mag_dlink  //管理员
{
	mag_info manager_info;
	struct Mag_dlink *prev;
	struct Mag_dlink *next;
}mag_dlink;


mag_dlink *mag_create_dlink(int num,int pwd,char name[]);
bool mag_isExist(mag_dlink *head,int num);
bool mag_insert_dlink_head(mag_dlink *head,int num,int pwd,char name[]);
void show_manager_info(mag_dlink *head);
bool write_manager_info(mag_dlink *head);
mag_dlink *read_manager_info();
mag_dlink *mag_register();
mag_dlink *manager_change_passwd(mag_dlink *p);
mag_dlink *manager_login();
stu_dlink *change_sign(stu_dlink *head);
stu_dlink *delect(stu_dlink *head);

#endif