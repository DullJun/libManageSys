#include "student.h"

void welcome_ui()
{
	printf("\t************************************\t\n");
	printf("\n");
	printf("\n");
	printf("\t\t欢迎进入学生管理系统\n");
	printf("\n");
	printf("\n");
	printf("\t\t请按任意键进入主界面\n");
	printf("\t************************************\t\n");
}

void choice_ui()
{
		printf("\t************************************\t\n");
		printf("\n");
		printf("\n");
		printf("\t\t[1]学生操作界面\n");
		printf("\n");
		printf("\n");
		printf("\t\t[2]教师操作界面\n");
		printf("\n");
		printf("\n");
		printf("\t\t[3]管理员登录界面\n");
		printf("\n");
		printf("\n");
		printf("\t\t[4]退出\n");
		printf("\n");
		printf("\n");
		printf("\t************************************\t\n");
		printf("请输入你的选择<1-4>：");
}

void register_login_ui()
{
					printf("\t************************************\t\n");
					printf("\n");
					printf("\n");
					printf("\t\t[1]账号注册\n");
					printf("\n");
					printf("\n");
					printf("\t\t[2]登录\n");
					printf("\n");
					printf("\n");
					printf("\t\t[0]返回上一层\n");
					printf("\t************************************\t\n");
					printf("请输入你的选择<0-2>：");
}

void ensure_login_ui()
{
		printf("\t************************************\t\n");
		printf("\n");
		printf("\n");
		printf("\t\t[1]ensure login\n");
		printf("\n");
		printf("\n");
		printf("\t\t[0]退出\n");
		printf("\n");
		printf("\n");
		printf("\t************************************\t\n");
		printf("请输入你的选择<0-1>：");
}

void student_ui()
{
		printf("\t************************************\t\n");
		printf("\n");
		printf("\n");
		printf("\t\t[1]check info.\n");
		printf("\n");
		printf("\n");
		printf("\t\t[2]change passwd\n");
		printf("\n");
		printf("\n");
		printf("\t\t[0]退出\n");
		printf("\n");
		printf("\n");
		printf("\t************************************\t\n");
		printf("请输入你的选择<0-2>：");
}

void manager_ui()
{
		printf("\t************************************\t\n");
		printf("\n");
		printf("\n");
		printf("\t\t[1]check info.\n");
		printf("\n");
		printf("\n");
		printf("\t\t[2]change passwd\n");
		printf("\n");
		printf("\n");
		printf("\t\t[3]manage student register\n");
		printf("\n");
		printf("\n");
		printf("\t\t[0]退出\n");
		printf("\n");
		printf("\n");
		printf("\t************************************\t\n");
		printf("请输入你的选择<0-3>：");
}

void show_student_info(stu_dlink *head)  //把学生的信息show出来
{
	if(head == NULL) return;
	stu_dlink *p = head->next;
	
	while(p != head)
	{
			printf("%s\t",p->student_info.name);
			printf("%d\t",p->student_info.English);
			printf("%d\t",p->student_info.Math);
			printf("%d\t",p->student_info.Chinese);
			printf("%d\t",p->student_info.pwd);
			printf("%d\t",p->student_info.num);
			printf("%d\t",p->student_info.sign);
			printf("\n");
			p = p->next;
	}	
}

bool isExist(stu_dlink *head,int num) //判断链表中是否存在该num
{
	if(head == NULL) return false;
	stu_dlink *p = head->next;
	while(p != head)
	{
		if(p->student_info.num == num)
		{
			printf("该num已经存在！\n");
			return 1;
		}
		p = p->next;
	}
	return false;
}
 
stu_dlink *create_dlink(int num,int pwd,int English,int Math,int Chinese,char name[],int sign)  //分配节点空间并且初始化
{
	stu_dlink *node = (stu_dlink *)malloc(sizeof(stu_dlink));
	if(node == NULL)
	{
		printf("create dlink fail!\n");
		return NULL;
	}
	node->student_info.num = num;
	node->student_info.pwd = pwd;
	node->student_info.English = English;
	node->student_info.Math =Math;
	node->student_info.Chinese = Chinese;
	node->student_info.sign=sign;
	strcpy(node->student_info.name,name);

	node->prev = node;
	node->next = node;

	return node;
}

bool insert_dlink_head(stu_dlink *head,int num,int pwd,int English,int Math,int Chinese,char name[],int sign) //学生注册，链表头插
{	
	if (head == NULL) return false;

	stu_dlink *node = create_dlink(num,pwd,English,Math,Chinese,name,sign);
	if(node == NULL)
	{
		perror("create dlink fail.\n");
		return NULL;
	}
	
	node->next = head->next;
	node->prev = head;
	head->next->prev = node;
	head->next = node;

	return true;
}

bool write_student_info(stu_dlink *head)   //把数据写入函数,并且把链表的空间释放掉
{
	FILE *fp = NULL;	
 	if((fp=fopen("test.txt","w")) == NULL)
	{
		printf("cannot open the file.\n");
		return false;
	}
	stu_dlink *p = head->next;
	stu_dlink *q = NULL;
	while(p!=head)
	{
		fwrite(&(p->student_info),sizeof(stu_info),1,fp);
		q = p;
		p = p->next;
		free(q);
	}
	fclose(fp);
	free(head);
	p = q = NULL;
	fp=NULL;
	return true;
}

 
 
stu_dlink *read_student_info()      //数据读出函数，动态创建链表并且读入
{
	 stu_dlink *head = create_dlink(0,0,0,0,0,"none",0);
	 stu_info student;
	 FILE *fp = NULL;
	 if((fp=fopen("test.txt","r")) == NULL)
	{
		 printf("cannot open the file.\n");
		 return NULL;
	 }
	 while(1 == fread(&student,sizeof(stu_info),1,fp))
	 {
		 insert_dlink_head(head,student.num,student.pwd,student.English,student.Math,student.Chinese,student.name,student.sign);
		  if(feof(fp))
		  {
			  break;
		  }
	 }
	 fclose(fp);
	 fp = NULL;

	 return head;
}

stu_dlink *stu_register()   //先把文件里的学生信息读出，判断是否存在改num,如果存在就结束本次循环，进入下一次循环
{
	int num,pwd;char name[16],ok;
	stu_dlink *p = read_student_info();
	if(p == NULL) 
	{
		p = create_dlink(0,0,0,0,0,"none",0);
	}
	//safe_flush(stdin); 
	do{
	printf("请输入num：\n");
	scanf("%d",&num);
	if(isExist(p,num))
	{
		return p;
	}
	printf("请输入名字：\n");
	scanf("%s",name);
	printf("请输入密码：\n");
	scanf("%d",&pwd);
	insert_dlink_head(p,num,pwd,0,0,0,name,1);
	printf("继续输入？（按y继续）：\n");
	scanf("%s",&ok);
	}while(ok == 'y');
	
	return p;
}

stu_dlink *student_change_passwd(stu_dlink *p)
{
    int x=0,y=0;
	int i=0;
	do
	{
		printf("请输入当前密码：");
        scanf("%d",&x);
        if(x!=p->student_info.pwd)
		{      
			printf("当前密码输入错误！\n");
        	i++;
        	if(i==3)
      		{
         		printf("三次当前密码输入错误！\n");
        		printf("密码修改失败！\n");
          		return 0;
        	}
      	}
     	else
      	{
        	break;
       	}
  	}while(1);
	do
   	{
		printf("输入新密码：\n");
  		scanf("%d",&x);
		printf("确认新密码：\n");
		scanf("%d",&y);
   		if(x==y)
  		{
         	i=0;
    	}
       	else
	    {
      		printf("两次密码输入不一致！\n请重新修改密码！\n");
         	i=1;
       	}
	}while(i);
	printf("change passwd success\n");
    p->student_info.pwd=x;
return p;
}

stu_dlink *student_login()
{
	stu_dlink *head=read_student_info();
	int a;
	do
	{
		ensure_login_ui();
		scanf(" %d",&a);
		if(a==1)
		{
			int num,pwd;
			printf("input student num\n");
			scanf(" %d",&num);
			
			printf("input student pwd\n");
			scanf(" %d",&pwd);

			int c=0;
			if(head == NULL) return false;
			stu_dlink *p = head->next;
			while(p != head)
			{
				if((p->student_info.num == num)&&(p->student_info.pwd==pwd)&&(p->student_info.sign == 2))
				{
					printf("login success\n");
					c=1;
					break;
				}
				else if((p->student_info.num == num)&&(p->student_info.pwd==pwd)&&(p->student_info.sign == 1))
				{
					printf("manager checked yet\n");
					break;
				}
				p = p->next;
			}
			if(c==1)
			{	
				int d,e,f;
				do
				{
					student_ui();
					scanf(" %d",&d);
					switch(d)
					{
						case 0:
							system("clear");
							break;
						case 1:
							do
							{
								printf("num:%d\n",p->student_info.num);
								printf("pwd:%d\n",p->student_info.pwd);
								printf("name:%s\n",p->student_info.name);
								printf("English:%d\n",p->student_info.English);
								printf("Math:%d\n",p->student_info.Math);
								printf("Chinese:%d\n",p->student_info.Chinese);
								printf("0:back\n");
								scanf(" %d",&e);
							}while(e!=0);break;
						case 2:
								student_change_passwd(p);
								break;
						default :printf("input error\n");break;
					}
				}while(d!=0);
			}
			else
			{
				printf("This num was not existed or checked without pass!\n");
				break;
			}
		}
		else
		{
			continue;
		}
	}while(a!=0);
return head;
}