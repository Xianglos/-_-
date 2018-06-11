#include "ruijianghong.h"

void new_file(struct MFD *user)
{
	//创建文件
	UFD *head;
	UFD *tail;
	head = user->next;
	//head->nextufd = NULL;
	tail = head;
	UFD *newfile = (struct UFD*)malloc(UFDLEN);
	bool isrepeat = false;//默认没有重名
	cout << "\n请输入要新建的文件名(20个字符以内): ";
	string newfilename;
	cin >> newfilename;
	strcpy(newfile->filename, newfilename.c_str());
	newfile->nextufd = NULL;
	newfile->nextlog = NULL;
	newfile->filelength = 0;
	if (head == NULL)
	{
		//链表为空 
		head = newfile;
		user->next = head;
		cout << "新建文件" << head->filename << "成功!" << endl;
	}
	else
	{
		while (tail->nextufd != NULL)
		{
			if (!strcmp(tail->filename, newfile->filename))
			{
				//检查重名
				isrepeat = true;
			}
			//tail指向尾结点
			tail = tail->nextufd;
		}
		if (!strcmp(tail->filename, newfile->filename))
		{
			//检查尾结点是否重名
			isrepeat = true;
		}
		if (!isrepeat)
		{
			tail->nextufd = newfile;
			cout << "新建文件" << tail->nextufd->filename << "成功" << endl;
		}
		else
		{
			cout << "出现重名，已取消新建" << endl;
			free(newfile);
		}
	}
	Sleep(1000);
}

void open_file(struct MFD *user, struct AFD *openfile)
{
	//打开文件
	//链表AFD头结点不存放数据
	bool match_ufd = false;//默认UFD链表内没有匹配的文件名
	bool match_afd = false;//默认AFD链表内没有匹配的文件名
	string s_open_filename = "";
	cout << ednl << "请输入要打开的文件名: ";
	cin >> s_open_filename;
	UFD *p,*inx;
	p = user->next;
	inx = p;
	AFD *a, *head, *newopenfile;	
	head = openfile;//AFD头结点
	a = head;
	while (p != NULL)
	{
		//在UFD里找
		if (!strcmp(p->filename, s_open_filename.c_str()))
		{
			//有匹配的文件名
			match_ufd = true;
			inx = p;
			break;
		}
		p = p->nextufd;
	}
	if (!match_ufd)
	{
		cout << "UFD:用户" << user->username << "的文件目录中没有找到文件名为" << s_open_filename << "的文件" << ednl;
	}
	else
	{
		//在AFD里找
		while (a->nextafd != NULL)
		{
			if (!strcmp(a->filename, s_open_filename.c_str()))
			{
				//有匹配的文件名
				match_afd = true;
			}
			a = a->nextafd;
		}
		if (!strcmp(a->filename, s_open_filename.c_str()))
		{
			//有匹配的文件名
			match_afd = true;
		}
		if (match_afd)
		{
			cout << "AFD:文件名为" << s_open_filename << "的文件已经打开" << ednl;
		}
		else
		{
			newopenfile = (struct AFD*)malloc(AFDLEN);
			//newopenfile->filelength = 0;
			//newopenfile->flag = 0;
			//newopenfile->nextlog = NULL;
			//newopenfile->nextafd = NULL;
			newopenfile->filelength = inx->filelength;
			newopenfile->flag = 0;
			newopenfile->nextafd = NULL;
			newopenfile->nextlog = inx->nextlog;
			strcpy(newopenfile->filename, s_open_filename.c_str());
			//a->nextafd = newopenfile;
			//a = newopenfile;
			if (head->nextafd == NULL)
			{
				head->nextafd = newopenfile;
			}
			else
			{
				newopenfile->nextafd = head->nextafd;
				head->nextafd = newopenfile;
			}
			cout << "文件" << newopenfile->filename << "打开成功" << ednl;
		}
	}
	match_afd = false;
	match_ufd = false;
	Sleep(1500);
}

void display_directory(struct MFD *user)
{
	//显示目录
	cout << endl;
	UFD *head = user->next;
	UFD *p = head;
	string s_filename = "";
	int i_count = 0;
	while (p != NULL)
	{
		s_filename = p->filename;
		cout << s_filename << endl;
		p = p->nextufd;
		i_count++;
	}
	cout << "共计 " << i_count << " 个文件，已全部显示." << endl;
	Sleep(3000);
}

void close_file(struct MFD *user, struct AFD *openfile) 
{
	//关闭文件
	cout << ednl;
	bool match_afd = false;//默认AFD链表内没有匹配的文件名
	bool match_ufd = false;//默认UFD链表内没有匹配的文件名
	string s_closefilename = "";
	cout << "请输入要关闭的文件名: ";
	cin >> s_closefilename;
	AFD *a, *head, *inx, *befinx;
	head = openfile;//AFD头结点
	a = head;
	befinx = head;
	inx = befinx->nextafd;
	UFD *ufd_head, *p, *ufd_inx, *ufd_befinx;
	ufd_head = user->next;
	p = ufd_head;
	ufd_befinx = ufd_head;
	ufd_inx = ufd_befinx->nextufd;
	if(head->nextafd==NULL)
	{
		cout << "AFD:没有文件是打开的" << ednl;
	}
	else
	{
		while (a->nextafd != NULL)
		{
			//在AFD里找
			if (!strcmp(a->filename, s_closefilename.c_str()))
			{
				//有匹配的文件名
				match_afd = true;
				inx = a;
				break;
			}
			else
			{
				befinx = a;
			}
			a = a->nextafd;
		}
		if (!strcmp(a->filename, s_closefilename.c_str()) && match_afd == false)
		{
			//有匹配的文件名
			match_afd = true;
			inx = a;
		}
		if (a->flag == 0)
		{
			//删除结点空间
			befinx->nextafd = inx->nextafd;
			free(inx);
			cout << "文件" << s_closefilename << "没有被修改过" << ednl;

		}
		else
		{
			//==========================================================
			//将记录复制到UFD中
			while (p != NULL)
			{
				//在UFD里找
				if (!strcmp(p->filename, s_closefilename.c_str()))
				{
					//UFD有匹配的文件名
					match_ufd = true;
					ufd_inx = p;
					break;
				}
				ufd_befinx = p;
				p = p->nextufd;
			}
			if (match_ufd)
			{
				ufd_inx->nextlog = inx->nextlog;
				ufd_inx->filelength = inx->filelength;
				cout << "LOG:记录已复制到用户" << user->username << "的UFD中" << ednl;
			}
			else
			{
				cout << "LOG:记录复制失败，我也不知道为什么" << ednl;
				cout << "UFD:没有在用户" << user->username << "的UFD中找到文件名为" << s_closefilename << "的文件" << endl;
			}
			//==========================================================
			//cout << "flag不为0" << endl;
			befinx->nextafd = inx->nextafd;
			free(inx);

			inx->nextafd = NULL;
			inx->filelength = 0;
			string init = "";
			strcpy(inx->filename, init.c_str());
			inx->nextlog = NULL;
		}
		cout << "AFD:文件" << s_closefilename << "已经被关闭" << ednl;
		match_afd = false;
	}	
	Sleep(1500);
}

void display_openedfile(struct AFD *openfile) 
{
	//显示已经打开的文件
	//链表AFD头结点不存放数据
	AFD *p = openfile;
	string s_filename = "";
	int i_count = -1;
	if (p->nextafd == NULL)
	{
		//AFD:没有被打开的文件
		cout << ednl << "没有文件被打开" << ednl;
	}
	else
	{
		while (p != NULL)
		{
			s_filename = p->filename;
			cout << s_filename << endl;
			p = p->nextafd;
			i_count++;
		}
		cout << "共计 " << i_count << " 个文件，已全部显示." << endl;
	}
	Sleep(3000);
}

void delete_file(struct MFD *user, struct AFD *openfile) 
{
	//删除文件
	//链表AFD头结点不存放数据
	cout << endl;
	if (openfile->nextafd = NULL)
	{
		cout << "AFD:没有文件被打开" << ednl;
	}
	else
	{
		bool match_ufd = false;//默认UFD链表内没有匹配的文件名
		bool match_afd = false;//默认AFD链表内没有匹配的文件名
		string s_delete_filename = "";
		cout << "请输入要删除的文件名: ";
		cin >> s_delete_filename;
		UFD *p, *head, *inx, *befinx;
		head = user->next;//UFD头结点
		p = head;
		befinx = head;
		inx = befinx->nextufd;
		AFD *a = openfile;//AFD头结点

		while (p != NULL)
		{
			//在UFD里找
			if (!strcmp(p->filename, s_delete_filename.c_str()))
			{
				//UFD有匹配的文件名
				match_ufd = true;
				inx = p;
				break;
			}
			befinx = p;
			p = p->nextufd;
		}
		//if (!strcmp(a->filename, s_delete_filename.c_str()) && match_ufd == false)
		//{
		//	//UFD有匹配的文件名
		//	match_ufd = true;
		//	inx = p;
		//}
		while (a->nextafd != NULL)
		{
			//在AFD里找
			if (!strcmp(a->filename, s_delete_filename.c_str()))
			{
				//AFD有匹配的文件名
				match_afd = true;
			}
			a = a->nextafd;
		}
		if (!strcmp(a->filename, s_delete_filename.c_str()))
		{
			//AFD有匹配的文件名
			match_afd = true;
		}

		if (match_ufd)
		{
			//p = head;
			//match_ufd = false;
			//你要删除的是你的文件
			if (match_afd)
			{
				//如果文件已经被打开
				cout << "AFD:文件" << s_delete_filename << "已经被打开" << endl;
				cout << "AFD:即将关闭文件" << s_delete_filename << ednl;
				close_file_in_delete(user, openfile, s_delete_filename);
			}
			///////////////////////

			if (inx == head)
			{
				//UFD的头结点有数据
				if (head->nextufd == NULL)
				{
					//如果要删除的是头结点且无后继结点
					//free(inx);
					//head = NULL;
					user->next = NULL;
				}
				else
				{
					//如果要删除的是头结点且有后继结点
					inx = inx->nextufd;
					befinx->nextufd = inx->nextufd;
					befinx->filelength = inx->filelength;
					befinx->nextlog = inx->nextlog;
					strcpy(befinx->filename, inx->filename);
					free(inx);
				}

			}
			else
			{
				befinx->nextufd = inx->nextufd;
				//befinx->filelength = inx->nextufd->filelength;
				//befinx->nextlog = inx->nextufd->nextlog;
				//strcpy(befinx->filename, inx->nextufd->filename);
				free(inx);
			}
			
			cout << "UFD:文件" << s_delete_filename << "已被删除" << ednl;
		}
		else
		{
			cout << "UFD:没有找到文件名为" << s_delete_filename << "的文件" << endl;
		}
		match_afd = false;
		match_ufd = false;
	}	
	Sleep(1500);
}

void close_file_in_delete(struct MFD *user, struct AFD *openfile, string filename)
{
	//在删除文件的过程中，如果文件已经在AFD中（已经被打开），调用此函数来关闭文件
	bool match_afd = false;//默认AFD链表内没有匹配的文件名
	bool match_ufd = false;//默认UFD链表内没有匹配的文件名
	string s_closefilename = "";
	s_closefilename = filename;
	AFD *a, *head, *inx, *befinx;
	head = openfile;//AFD头结点
	a = head;
	befinx = head;
	inx = befinx->nextafd;
	UFD *ufd_head, *p, *ufd_inx, *ufd_befinx;
	ufd_head = user->next;
	p = ufd_head;
	ufd_befinx = ufd_head;
	ufd_inx = ufd_befinx->nextufd;

	while (a->nextafd != NULL)
	{
		//在AFD里找
		if (!strcmp(a->filename, s_closefilename.c_str()))
		{
			//有匹配的文件名
			match_afd = true;
			inx = a;
			break;
		}
		else
		{
			befinx = a;
		}
		a = a->nextafd;
	}
	if (!strcmp(a->filename, s_closefilename.c_str()) && match_afd == false)
	{
		//有匹配的文件名
		match_afd = true;
		inx = a;
	}
	if (a->flag == 0)
	{
		//删除结点空间
		befinx->nextafd = inx->nextafd;
		free(inx);
		cout << "AFD:文件" << s_closefilename << "已经被关闭" << ednl;
	}
	else
	{
		//==========================================================
		//将记录复制到UFD中
		while (p != NULL)
		{
			//在UFD里找
			if (!strcmp(p->filename, s_closefilename.c_str()))
			{
				//UFD有匹配的文件名
				match_ufd = true;
				ufd_inx = p;
				break;
			}
			ufd_befinx = p;
			p = p->nextufd;
		}
		if (match_ufd)
		{
			ufd_inx->nextlog = inx->nextlog;
			ufd_inx->filelength = inx->filelength;
			cout << "LOG:记录已复制到用户" << user->username << "的UFD中" << ednl;
		}
		else
		{
			cout << "LOG:记录复制失败，我也不知道为什么" << ednl;
			cout << "UFD:没有在用户" << user->username << "的UFD中找到文件名为" << s_closefilename << "的文件" << endl;
		}
		//==========================================================
		//cout << "flag不为0" << endl;
		befinx->nextafd = inx->nextafd;
		free(inx);
		inx->nextafd = NULL;
		inx->filelength = 0;
		string init = "";
		strcpy(inx->filename, init.c_str());
		inx->nextlog = NULL;
	}
	match_afd = false;
	Sleep(1500);
}

void close_user(struct MFD *user, struct AFD *openfile)
{
	//关闭用户
	cout << endl;
	string s_filename = "";
	AFD *afd_head, *a,*inx;
	afd_head = openfile;
	a = afd_head->nextafd;
	inx = a;
	UFD *ufd_haed, *u;
	ufd_haed = user->next;
	u = ufd_haed;
	string init = "";

	while (a != NULL)
	{
		if (a->flag == 1)
		{
			a->flag = 0;
			s_filename = a->filename;
			while (u != NULL)
			{
				if (!strcmp(s_filename.c_str(),u->filename))
				{
					//在UFD中找到同名文件
					u->filelength = a->filelength;
					u->nextlog = a->nextlog;
					cout << "AFD:文件" << u->filename << "的记录已经被复制到UFD中" << ednl;
				}
				u = u->nextufd;
			}
		}
		inx = a;
		a = a->nextafd;
		free(inx);
		inx->nextafd = NULL;
		inx->filelength = 0;		
		strcpy(inx->filename, init.c_str());
		inx->nextlog = NULL;
	}
	free(a);
	//a->filelength = 0;
	//a->flag = 0;
	//a->nextafd = NULL;
	//a->nextlog = NULL;
	//strcpy(a->filename, init.c_str());
	openfile->nextafd = NULL;

}

void write_file(struct MFD *user, struct AFD *openfile) 
{
	//写文件
	cout << ednl;
	bool match_afd = false;//默认AFD链表内没有匹配的文件名
	bool match_ufd = false;//默认UFD链表内没有匹配的文件名
	string s_write_filename = "";
	string log_name = "";
	string los_sex = "";
	FILELOG *newlog = (struct FILELOG*)malloc(LOGLEN);
	FILELOG *loghead, *tail;
	UFD *ufd_head, *p,*ufd_inx,*ufd_befinx;
	ufd_head = user->next;
	p = ufd_head;
	cout << "请输入文件名:";
	cin >> s_write_filename;
	ufd_befinx = ufd_head;
	ufd_inx = ufd_befinx->nextufd;

	////////////////////////////////////////////////////////////////
	
	//string s_closefilename = "";
	//cout << ednl << "请输入要关闭的文件名: ";
	//cin >> s_closefilename;
	AFD *a, *head, *inx, *befinx;
	head = openfile;//AFD头结点
	a = head;
	befinx = head;
	inx = befinx->nextafd;

	while (a->nextafd != NULL)
	{
		//在AFD里找
		if (!strcmp(a->filename, s_write_filename.c_str()))
		{
			//AFD有匹配的文件名
			match_afd = true;
			inx = a;
			break;
		}
		else
		{
			befinx = a;
		}
		a = a->nextafd;
	}
	if (!strcmp(a->filename, s_write_filename.c_str()) && match_afd == false)
	{
		//AFD有匹配的文件名
		match_afd = true;
		inx = a;
	}
	////////////////////////////////////////////////////////////////////
	if (match_afd)
	{
		//开始写
		//inx->nextlog = (struct FILELOG*)malloc(LOGLEN);
		loghead = inx->nextlog;
		tail = loghead;
		cout << "请输入姓名:";
		cin >> log_name;
		cout << "请输入性别:";
		cin >> los_sex;
		strcpy(newlog->username, log_name.c_str());
		strcpy(newlog->sex, los_sex.c_str());
		newlog->next = NULL;
		//===============================================================
		if (loghead == NULL)
		{
			//链表为空 
			loghead = newlog;
			inx->nextlog = loghead;
			//cout << "新建文件" << head->filename << "成功!" << endl;
			cout << "FIRST LOG:已新建一条姓名为" << inx->nextlog->username << " 性别为" << inx->nextlog->sex << "的记录" << ednl;
		}
		else
		{
			while (tail->next != NULL)
			{
				//if (!strcmp(tail->username, newfile->filename))
				//{
				//	//检查重名
				//	isrepeat = true;
				//}
				//tail指向尾结点
				tail = tail->next;
			}
			tail->next = newlog;
			cout << "LOG:已新建一条姓名为" << tail->next->username << " 性别为" << tail->next->sex << "的记录" << ednl;
			//if (!strcmp(tail->filename, newfile->filename))
			//{
			//	//检查尾结点是否重名
			//	isrepeat = true;
			//}
			//if (!isrepeat)
			//{
			//	tail->nextufd = newfile;
			//	cout << "新建文件" << tail->nextufd->filename << "成功" << endl;
			//}
			//else
			//{
			//	cout << "出现重名，已取消新建" << endl;
			//	free(newfile);
			//}
		}
		//===============================================================
		inx->flag = 1;
		inx->filelength = inx->filelength + 1;

		//将记录复制到UFD中
		while (p != NULL)
		{
			//在UFD里找
			if (!strcmp(p->filename, s_write_filename.c_str()))
			{
				//UFD有匹配的文件名
				match_ufd = true;
				ufd_inx = p;
				break;
			}
			ufd_befinx = p;
			p = p->nextufd;
		}
		if (match_ufd)
		{
			ufd_inx->nextlog = inx->nextlog;
			ufd_inx->filelength = inx->filelength;
			//cout << "LOG:记录已复制到用户" << user->username << "的UFD中" << ednl;
		}
		else
		{
			cout << "LOG:记录复制失败，我也不知道为什么" << ednl;
			cout << "UFD:没有在用户" << user->username << "的UFD中找到文件名为" << s_write_filename << "的文件" << endl;
		}
	}
	else
	{
		cout << "AFD:没有找到文件名为" << s_write_filename << "的文件" << endl;
		cout << "可能没有创建该文件，或创建了没有打开" << ednl;
		free(newlog);
	}
	Sleep(1500);
}

void read_file(struct MFD *user, struct AFD *openfile)
{
	//读文件

	cout << ednl;
	//int Ri = 0;//第Ri条记录
	UFD *ufd_head, *u;
	ufd_head = user->next;
	u = ufd_head;
	AFD *afd_head, *a;
	afd_head = openfile;
	a = afd_head->nextafd;
	FILELOG *log_head, *f;
	int count = 1;
	int inall = 0;

	while (a != NULL)
	{
		//if (a->flag == 0)
		//{
		//	cout << "文件" << a->filename << "没有修改记录" << endl;
		//}
		//else
		//{
			log_head = a->nextlog;
			f = log_head;
			while (f != NULL)
			{
				cout << "文件" << a->filename << "的第" << count << "记录是:";
				cout << "姓名:" << f->username << "  性别:" << f->sex << ednl;
				f = f->next;
				count++;
				inall++;
			}
		//}		
		a = a->nextafd;
		count = 1;
		cout << ednl;
	}
	cout << "全部" << inall << "条记录已输出" << ednl;

	Sleep(inall*1000);
}

void read_file_log(struct MFD *user, struct AFD *openfile)
{
	//读取指定文件的第Ri条记录
	bool match_afd = false;//默认AFD链表内没有匹配的文件名
	bool match_log = false;//默认LOG链表内没有匹配的记录
	cout << ednl;
	int Ri = 0;//第Ri条记录
	string s_filename = "";//指定的一个文件名
	UFD *ufd_head, *u;
	ufd_head = user->next;
	u = ufd_head;
	AFD *afd_head, *a;
	afd_head = openfile;
	a = afd_head->nextafd;
	FILELOG *log_head, *f;
	int count = 1;
	int inall = 0;

	cout << "请输入要读取的文件名:";
	cin >> s_filename;
	while (a != NULL)
	{
		if (!strcmp(a->filename, s_filename.c_str()))
		{
			match_afd = true;
			break;
		}
		a = a->nextafd;
	}
	if (!match_afd)
	{
		cout << "AFD:没有找到文件名为" << s_filename << "的文件" << ednl;
		cout << "文件可能没有被创建，或者创建了没有被打开" << ednl;
	}
	else
	{
		cout << "AFD:已在AFD中找到文件名为" << a->filename << "的文件" << endl;
		cout << "请输入要读取文件" << s_filename << "的第几条记录（>0）:";
		cin >> Ri;
		if (Ri <= 0)
		{
			cout << "输入的值不符合要求" << ednl;
		}
		else
		{
			a = afd_head->nextafd;
			while (a != NULL)
			{
				//if (a->flag == 0)
				//{
				//	cout << "文件" << a->filename << "没有修改记录" << endl;
				//}
				//else
				//{
				log_head = a->nextlog;
				f = log_head;
				while (f != NULL)
				{
					if (count == Ri && (!strcmp(s_filename.c_str(), a->filename)))
					{
						//文件名相同且是第Ri条记录
						cout << "文件" << a->filename << "的第" << count << "记录是:";
						cout << "姓名:" << f->username << "  性别:" << f->sex << ednl;
						match_log = true;
					}
					//cout << "文件" << a->filename << "的第" << count << "记录是:";
					//cout << "姓名:" << f->username << "  性别:" << f->sex << ednl;
					f = f->next;
					count++;
					inall++;
				}
				//}		
				a = a->nextafd;
				count = 1;
				//cout << ednl;
			}
			//cout << "全部" << inall << "条记录已输出" << ednl;
			if (match_log)
			{
				cout << "读文件结束" << endl;
			}
			else
			{
				cout << "LOG:文件" << s_filename << "中没有找到第" << Ri << "条记录" << ednl;
			}
		}
	}	

	Sleep(3000);
}

void exit(){}//退出

void change_file(struct MFD *user, struct AFD *openfile)
{
	//写文件
	cout << ednl;
	bool match_afd = false;//默认AFD链表内没有匹配的文件名
	bool match_ufd = false;//默认UFD链表内没有匹配的文件名
	string s_write_filename = "";
	string log_name = "";
	string los_sex = "";
	FILELOG *newlog = (struct FILELOG*)malloc(LOGLEN);
	FILELOG *loghead, *tail,*log_inx;
	log_inx = NULL;
	UFD *ufd_head, *p, *ufd_inx, *ufd_befinx;
	ufd_head = user->next;
	p = ufd_head;
	cout << "请输入文件名:";
	cin >> s_write_filename;
	ufd_befinx = ufd_head;
	ufd_inx = ufd_befinx->nextufd; 
	
	//log_inx = loghead;

	////////////////////////////////////////////////////////////////

	//string s_closefilename = "";
	//cout << ednl << "请输入要关闭的文件名: ";
	//cin >> s_closefilename;
	AFD *a, *head, *inx, *befinx;
	head = openfile;//AFD头结点
	a = head;
	befinx = head;
	inx = befinx->nextafd;

	while (a->nextafd != NULL)
	{
		//在AFD里找
		if (!strcmp(a->filename, s_write_filename.c_str()))
		{
			//AFD有匹配的文件名
			match_afd = true;
			inx = a;
			break;
		}
		else
		{
			befinx = a;
		}
		a = a->nextafd;
	}
	if (!strcmp(a->filename, s_write_filename.c_str()) && match_afd == false)
	{
		//AFD有匹配的文件名
		match_afd = true;
		inx = a;
	}
	////////////////////////////////////////////////////////////////////
	if (match_afd)
	{
		//开始写
		//inx->nextlog = (struct FILELOG*)malloc(LOGLEN);
		bool isrepeat = false;
		loghead = inx->nextlog;
		tail = loghead;
		log_inx = loghead;
		cout << "请原记录的姓名:";
		cin >> log_name;
		//cout << "请输入性别:";
		//cin >> los_sex;
		strcpy(newlog->username, log_name.c_str());
		strcpy(newlog->sex, los_sex.c_str());
		newlog->next = NULL;
		//===============================================================
		if (loghead == NULL)
		{
			//链表为空 
			//loghead = newlog;
			//inx->nextlog = loghead;
			////cout << "新建文件" << head->filename << "成功!" << endl;
			//cout << "FIRST LOG:已新建一条姓名为" << inx->nextlog->username << " 性别为" << inx->nextlog->sex << "的记录" << ednl;
			cout << "文件没有记录" << endl;
		}
		else
		{
			while (tail->next != NULL)
			{
				if (!strcmp(tail->username, log_name.c_str()))
				{
					//检查重名
					isrepeat = true;
					log_inx = tail;
					cout << "已找到名为" << log_name << "的记录" << ednl;
					break;
				}
				//tail指向尾结点
				tail = tail->next;
			}
			string newname, newsex;
			cout << "输入新的姓名:";
			cin >> newname;
			cout << "输入新的性别:";
			cin >> newsex;
			strcpy(log_inx->username, newname.c_str());
			strcpy(log_inx->sex, newsex.c_str());
			cout << "已将记录的姓名修改为" << newname;
			cout << "已将记录的性别修改为" << newsex;
			//tail->next = newlog;
			//cout << "LOG:已新建一条姓名为" << tail->next->username << " 性别为" << tail->next->sex << "的记录" << ednl;
		}
		//===============================================================
		inx->flag = 1;
		inx->filelength = inx->filelength + 1;

		//将记录复制到UFD中
		while (p != NULL)
		{
			//在UFD里找
			if (!strcmp(p->filename, s_write_filename.c_str()))
			{
				//UFD有匹配的文件名
				match_ufd = true;
				ufd_inx = p;
				break;
			}
			ufd_befinx = p;
			p = p->nextufd;
		}
		if (match_ufd)
		{
			ufd_inx->nextlog = inx->nextlog;
			ufd_inx->filelength = inx->filelength;
			cout << "LOG:记录已复制到用户" << user->username << "的UFD中" << ednl;
		}
		else
		{
			cout << "LOG:记录复制失败，我也不知道为什么" << ednl;
			cout << "UFD:没有在用户" << user->username << "的UFD中找到文件名为" << s_write_filename << "的文件" << endl;
		}
	}
	else
	{
		cout << "AFD:没有找到文件名为" << s_write_filename << "的文件" << endl;
		cout << "可能没有创建该文件，或创建了没有打开" << ednl;
		free(newlog);
	}
	Sleep(1500);
}
