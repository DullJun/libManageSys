#include "student.h"
#include "manager.h"

int main()
{
	int choice_top,choice_stu,choice_mag;
	welcome_ui();
	getchar();	
	do{
		choice_ui();
		scanf(" %d",&choice_top);
		switch(choice_top)
		{
			case 1:
				do{
					register_login_ui();
					scanf(" %d",&choice_stu);
					switch(choice_stu)
					{
						case 1:
							write_student_info(stu_register());
							show_student_info(read_student_info());
							break;
						case 2:
							//student_login();
							write_student_info(student_login());
							break;
						case 0:
							system("clear");
							break;
						default :break;
					  }
				}while(choice_stu!=0);
				break;
			case 2:
				//教师登录的界面
				if(1){}
				break;
			case 3:
				do{
					register_login_ui();
					scanf(" %d",&choice_mag);
					switch(choice_mag)
					{
						case 1:
							write_manager_info(mag_register());
                                                        printf("please wait the result after manager checked\n");
							show_manager_info(read_manager_info());
							break;
						case 2:
							//manager_login();//管理员登录
							write_manager_info(manager_login());
							//show_manager_info(read_manager_info());
							break;
						case 0:
							system("clear");
							break;
						default :break;
					 }
				}while(choice_mag!=0);
				break;
			case 4:
				system("clear");
				printf("\t\t[3]感谢你的使用！\n");
				break;
			default :break;
		}
	}while(choice_top!=4); 
	
	
/* 	stu_dlink *head = create_dlink(0,0,0,0,0,"none",0);

	insert_dlink_head(head,88,1,1,1,1,"lzh",88);
	insert_dlink_head(head,78,2,2,2,2,"lzj",99);
	insert_dlink_head(head,54,3,3,3,3,"lyf",89);
	insert_dlink_head(head,45,4,4,4,4,"hhh",9);
	insert_dlink_head(head,56,5,5,5,5,"nnn",45);
	insert_dlink_head(head,68,6,6,6,6,"zzz",7);
	insert_dlink_head(head,73,7,7,7,7,"lll",6);

	show_student_info(head);
	
	printf("---\n");
	printf("---\n");
	printf("---\n");
	
	write_student_info(head);
	stu_dlink *p = read_student_info();


	show_student_info(p);
	
	stu_register();  */

	return 0;
}
