#pragma once

#ifndef _RUIJIANGHONG_H_
#define _RUIJIANGHONG_H_

#pragma warning(disable : 4996)
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include<malloc.h>
using namespace std;

#define MFDLEN sizeof(struct MFD)
#define UFDLEN sizeof(struct UFD)
#define AFDLEN sizeof(struct AFD)
#define LOGLEN sizeof(struct FILELOG)
#define ture true
#define ednl endl

struct MFD//主目录
{
	string username;//用户名
	string sex;//性别
	struct UFD *next;//用户文件目录指针
};

struct UFD//用户文件目录
{
	char filename[20];//文件名
	int filelength;//文件长度
	struct FILELOG *nextlog;//文件记录链表的头指针
	struct UFD *nextufd;//文件表目链表指针
};

struct AFD//打开文件表
{
	//链表AFD头结点不存放数据
	char filename[20];//文件名
	int filelength;//文件长度
	int flag;//修改标志flag
	struct FILELOG *nextlog;//文件记录头指针
	struct AFD *nextafd;//文件表目链表指针
};

struct FILELOG//文件记录型
{
	char username[20];//用户名
	char sex[20];//性别
	struct FILELOG *next;//下一条记录的链接指针
};
void new_file(struct MFD *user);//创建文件
void display_directory(struct MFD *user);//显示目录
void close_user(struct MFD *user, struct AFD *openfile);//关闭用户
void open_file(struct MFD *user, struct AFD *openfile);//打开文件
void close_file(struct MFD *user, struct AFD *openfile);//关闭文件
void display_openedfile(struct AFD *openfile);//显示文件
void delete_file(struct MFD *user, struct AFD *openfile);//删除文件
void close_file_in_delete(struct MFD *user, struct AFD *openfile, string filename);//关闭的时候删除文件
void write_file(struct MFD *user, struct AFD *openfile);//写文件
void change_file(struct MFD *user, struct AFD *openfile);//修改文件
void read_file(struct MFD *user, struct AFD *openfile);//读文件
void read_file_log(struct MFD *user, struct AFD *openfile);//读取指定文件的第Ri条记录
void exit();//退出


#endif // _RUIJIANGHONG_H_
