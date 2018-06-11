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

struct MFD//��Ŀ¼
{
	string username;//�û���
	string sex;//�Ա�
	struct UFD *next;//�û��ļ�Ŀ¼ָ��
};

struct UFD//�û��ļ�Ŀ¼
{
	char filename[20];//�ļ���
	int filelength;//�ļ�����
	struct FILELOG *nextlog;//�ļ���¼�����ͷָ��
	struct UFD *nextufd;//�ļ���Ŀ����ָ��
};

struct AFD//���ļ���
{
	//����AFDͷ��㲻�������
	char filename[20];//�ļ���
	int filelength;//�ļ�����
	int flag;//�޸ı�־flag
	struct FILELOG *nextlog;//�ļ���¼ͷָ��
	struct AFD *nextafd;//�ļ���Ŀ����ָ��
};

struct FILELOG//�ļ���¼��
{
	char username[20];//�û���
	char sex[20];//�Ա�
	struct FILELOG *next;//��һ����¼������ָ��
};
void new_file(struct MFD *user);//�����ļ�
void display_directory(struct MFD *user);//��ʾĿ¼
void close_user(struct MFD *user, struct AFD *openfile);//�ر��û�
void open_file(struct MFD *user, struct AFD *openfile);//���ļ�
void close_file(struct MFD *user, struct AFD *openfile);//�ر��ļ�
void display_openedfile(struct AFD *openfile);//��ʾ�ļ�
void delete_file(struct MFD *user, struct AFD *openfile);//ɾ���ļ�
void close_file_in_delete(struct MFD *user, struct AFD *openfile, string filename);//�رյ�ʱ��ɾ���ļ�
void write_file(struct MFD *user, struct AFD *openfile);//д�ļ�
void change_file(struct MFD *user, struct AFD *openfile);//�޸��ļ�
void read_file(struct MFD *user, struct AFD *openfile);//���ļ�
void read_file_log(struct MFD *user, struct AFD *openfile);//��ȡָ���ļ��ĵ�Ri����¼
void exit();//�˳�


#endif // _RUIJIANGHONG_H_
