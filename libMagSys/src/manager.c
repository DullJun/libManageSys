#include "manager.h"

////////////////////////////////////////////////////manager


void show_manager_info(mag_dlink *head)  //把manager的信息show出来
{
	if(head == NULL) return;
	mag_dlink *p = head->next;
	
	while(p != head)
	{
			printf("%d\t",p->manager_info.num);
			printf("%d\t",p->manager_info.pwd);
			printf("%s\t",p->manager_info.name);
			printf("\n");
			p = p->next;
	}	
}

bool mag_isExist(mag_dlink *head,int num) //判断链表中是否存在该num
{
	if(head == NULL) return false;
	mag_dlink *p = head->next;
	while(p != head)
	{
		if(p->manager_info.num == num)
		{
			printf("该num已经存在！\n");//ll
			return 1;
		}
		p = p->next;
	}
	return false;
}
 
mag_dlink *mag_create_dlink(int num,int pwd,char name[])  //分配节点空间并且初始化
{
	mag_dlink *node = (mag_dlink *)malloc(sizeof(mag_dlink));
	if(node == NULL)
	{
		printf("create dlink fail!\n");
		return NULL;
	}
	node->manager_info.num = num;
	node->manager_info.pwd = pwd;
	strcpy(node->manager_info.name,name);

	node->prev = node;
	node->next = node;

	return node;
}

bool mag_insert_dlink_head(mag_dlink *head,int num,int pwd,char name[]) //manager注册，链表头插
{	
	if (head == NULL) return false;

	mag_dlink *node = mag_create_dlink(num,pwd,name);
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

bool write_manager_info(mag_dlink *head)   //把数据写入函数,并且把链表的空间释放掉
{
	FILE *fp = NULL;	
 	if((fp=fopen("test_mag.txt","w")) == NULL)
	{
		printf("cannot open the file.\n");
		return false;
	}
	mag_dlink *p = head->next;
	mag_dlink *q = NULL;
	while(p!=head)
	{
		fwrite(&(p->manager_info),sizeof(mag_info),1,fp);
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
 
mag_dlink *read_manager_info()      //数据读出函数，动态创建链表并且读入
{
	 mag_dlink *head = mag_create_dlink(0,0,"none");
	 mag_info manager;
	 FILE *fp = NULL;
	 if((fp=fopen("test_mag.txt","r")) == NULL)
	{
		 printf("cannot open the file.\n");
		 return NULL;
	 }
	 while(1 == fread(&manager,sizeof(mag_info),1,fp))
	 {
		  mag_insert_dlink_head(head,manager.num,manager.pwd,manager.name);
		  if(feof(fp))
		  {
			  break;
		  }
	 }
	 fclose(fp);
	 fp = NULL;

	 return head;
}


mag_dlink *mag_register()   //先把文件里的manager信息读出，判断是否存在改num,如果存在就结束本次循环，进入下一次循环
{
	int num,pwd;char name[16],ok;
	mag_dlink *p = read_manager_info();
	if(p == NULL) 
	{
		p = mag_create_dlink(0,0,"none");
	}
	//safe_flush(stdin); 
	do{
	printf("请输入num：\n");
	scanf("%d",&num);
	if(mag_isExist(p,num))
	{
		return p;
	}
	printf("请输入名字：\n");
	scanf("%s",name);
	printf("请输入密码：\n");
	scanf("%d",&pwd);
	mag_insert_dlink_head(p,num,pwd,name);
	printf("继续输入？（按y继续）：\n");
	scanf("%s",&ok);
	}while(ok == 'y');
	
	return p;
}
mag_dlink *manager_change_passwd(mag_dlink *p)
{
    int x=0,y=0;
	int i=0;
	do
	{
		printf("请输入当前密码：");
        scanf("%d",&x);
        if(x!=p->manager_info.pwd)
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
    p->manager_info.pwd=x;
return p;
}

mag_dlink *manager_login()
{
	mag_dlink *head=read_manager_info();
	//show_manager_info(head);
	int a;
	do
	{
		
		ensure_login_ui();
		scanf(" %d",&a);
		if(a==1)
		{
			int num,pwd;
			printf("input manager num\n");
			scanf(" %d",&num);
			
			printf("input manager pwd\n");
			scanf(" %d",&pwd);
			
			int c=0;
			if(head == NULL) return false;
			mag_dlink *p = head->next;
			while(p != head)
			{
				if((p->manager_info.num == num)&&(p->manager_info.pwd==pwd))
				{
					printf("login success\n");
					c=1;
					break;
				}
				p = p->next;
			}
			if(c==1)
			{	
				int d,e,f;
				do
				{
					manager_ui();
					scanf(" %d",&d);
					switch(d)
					{
						case 0:
							system("clear");
							break;
						case 1:
							do
							{
								printf("\tnum:%d\n",p->manager_info.num);
								printf("\tpwd:%d\n",p->manager_info.pwd);
								printf("\tname:%s\n",p->manager_info.name);
								printf("0:back\n");
								scanf(" %d",&e);
							}while(e!=0);break;
						case 2:
								manager_change_passwd(p);
								//p=manager_change_passwd(p);
								//write_manager_info(mag_register());
								break;
						case 3:
			write_student_info(delect(change_sign(read_student_info())));
								
								break;
						default :printf("input error\n");break;
					}
				}while(d!=0);
			}
			else
			{
				printf("login failed\n");
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

stu_dlink *change_sign(stu_dlink *head)
{
	int order;
	if(head==NULL)return NULL;
	stu_dlink *p;
	p=head->next;
	while(p!=head)
	{
		if((p->student_info.sign)!=2)
		{
			printf("%d\n",p->student_info.num);
			printf("%d\n",p->student_info.pwd);
			printf("%s\n",p->student_info.name);
			printf("please check and input'1'or'0','1'means pass,'0'means false\n");
			scanf("%d",&order);
			if(order==1)
			{
				p->student_info.sign=2;
				//return true;
			}
			else
			{
				p->student_info.sign=0;
				//return false;
			}
		}
		p=p->next;   	
	}
return head;
}

stu_dlink *delect(stu_dlink *head)
{
	if(head==NULL)return NULL;
	stu_dlink *q;
	q=head->next;
	while(q!=head)
	{
		if(q->student_info.sign==0)
		{
			q->next->prev=q->prev;
			q->prev->next=q->next;
			free(q);
			//return true;
		}
		q=q->next;
	}
	if(q==head)
	{
		printf("unchecked user not existed\n");
		//return false;
	}
return head;
}
