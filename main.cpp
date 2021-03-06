// 两级文件系统.cpp: 定义控制台应用程序的入口点。
//
#include "ruijianghong.h"


int main()
{
	static int COUNT = -1;
	static int index = -1;//当前操作的用户
	int page1, page2;
	page1 = -1;
	page2 = -1;
	string loginname;
	static bool acc_name = false;//已有用户登录专用
	static bool gooperate = false;//去往操作页面
	static bool gologin = false;//去往登录页面
	string initfilename = "";

	AFD openfile;//定义打开文件链表
	openfile.filelength = 0;
	strcpy(openfile.filename, initfilename.c_str());
	openfile.flag = 0;
	openfile.nextafd = NULL;
	openfile.nextlog = NULL;

	MFD user[4];//定义用户,最多4人
	for (int i = 0; i < 4; i++)
	{
		//初始化用户
		user[i].username = "";
		user[i].sex = "";
		user[i].next = (struct UFD*)malloc(UFDLEN);
		strcpy(user[i].next->filename, initfilename.c_str());
		user[i].next = NULL;
	}

	while (1)
	{
		while (1)
		{
			system("cls");//清屏
			////////////////////用户注册&登录///////////////
			printf("1.新建用户\n");
			printf("2.已有用户登录\n");
			printf("3.退出\n");
			printf("请选择你需要的功能:");
			scanf("%d", &page1);
			if (page1 == 1)
			{
				//1.新建用户
				COUNT++;
				if (COUNT >= 4)
				{
					//最多4个用户
					printf("\n新建用户:用户数量已达到上限！");
					COUNT--;
				}
				else
				{
					printf("\n新建用户:请输入新的用户名:");
					cin >> user[COUNT].username;
					printf("新建用户:请输入新用户的性别:");
					cin >> user[COUNT].sex;
					for (int i = 0; i <= COUNT; i++)
					{
						if ((!strcmp(user[COUNT].username.c_str(), user[i].username.c_str())) && COUNT != 0)
						{
							//出现重名
							printf("\n新建用户:出现重名，即将跳回至首页面");
							gooperate = false;
							COUNT--;
							break;
						}
						else
						{
							//新用户注册成功
							printf("\n新建用户:新用户注册成功，即将跳转至操作界面");
							index = COUNT;
							gooperate = true;
							break;
						}
					}

				}
				Sleep(1500);//延时1500ms
			}
			else if (page1 == 2)
			{
				//2.已有用户登录
				printf("\n登录用户:请输入用户名:");
				//scanf("%s", loginname);
				cin >> loginname;
				for (int i = 0; i <= COUNT; i++)
				{
					if (!strcmp(user[i].username.c_str(), loginname.c_str()))
					{
						//用户名匹配
						acc_name = ture;
						index = i;
					}
					if (i == COUNT)
					{
						if (acc_name)
						{
							//全部比较完且出现用户名匹配
							gooperate = true;//跳向登录
							cout << endl << "登录用户:用户" << user[index].username << "登录成功，即将跳转至登录页面" << endl;
						}
						else
						{
							cout << ednl << "登录用户:不存在这个用户！" << endl;
						}
					}

				}
				Sleep(1500);//延时1500ms
			}
			else if (page1 == 3)
			{
				//退出
				return 0;
			}
			else
			{
				printf("输入无效!");
				Sleep(1000);
				//goto END;
			}
			page1 = -1;
			////////////////////////////////////////////////
			if (gooperate)
			{
				gooperate = false;
				break;
			}
			system("cls");//清屏
		}
		////////////////////登录后的操作////////////////
		while (1)
		{
			system("cls");//登录成功，进入操作页面
			printf("当前用户");
			cout << user[index].username;
			printf("登录成功，可以执行下列的操作\n");
			printf("1.新建一个文件\n");
			printf("2.显示所有文件目录\n");
			printf("3.打开一个文件\n");
			printf("4.显示已经打开的文件\n");
			printf("5.写文件\n");
			printf("6.读文件\n");
			printf("7.关闭文件\n");
			printf("8.删除文件\n");
			printf("9.退出当前用户\n");
			printf("10.修改文件\n");
			printf("请选择要执行的操作:");
			scanf("%d", &page2);
			if (page2 == 1)
			{
				//新建文件
				new_file(&user[index]);
			}
			else if (page2 == 2)
			{
				//显示目录
				display_directory(&user[index]);
			}
			else if (page2 == 3)
			{
				//打开文件
				open_file(&user[index], &openfile);
			}
			else if (page2 == 4)
			{
				//显示已经打开的文件
				display_openedfile(&openfile);
			}
			else if (page2 == 5)
			{
				//写文件
				write_file(&user[index], &openfile);
			}
			else if (page2 == 6)
			{
				//读文件
				//read_file(&user[index], &openfile);
				read_file_log(&user[index], &openfile);
			}
			else if (page2 == 7)
			{
				//关闭文件
				close_file(&user[index], &openfile);
			}
			else if (page2 == 8)
			{
				//删除文件
				delete_file(&user[index], &openfile);
			}
			else if (page2 == 9)
			{
				//退出当前用户
				close_user(&user[index], &openfile);
				cout << endl << "退出用户" << user[index].username << endl;
				gologin = ture;
				index = -1;
				Sleep(2000);
				//goto PAGE1;
			}
			else if (page2 = 10)
			{
				change_file(&user[index], &openfile);
			}
			else
			{
				//输入无效
				printf("\n输入无效!");
				Sleep(1000);
				//goto LOGIN;
				continue;
			}
			if (gologin)
			{
				//去往登录页面
				gologin = false;
				break;
			}
		}
	}
	
	////////////////////////////////////////////////	

    return 0;
}