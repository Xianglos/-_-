#include "ruijianghong.h"

void new_file(struct MFD *user)
{
	//�����ļ�
	UFD *head;
	UFD *tail;
	head = user->next;
	//head->nextufd = NULL;
	tail = head;
	UFD *newfile = (struct UFD*)malloc(UFDLEN);
	bool isrepeat = false;//Ĭ��û������
	cout << "\n������Ҫ�½����ļ���(20���ַ�����): ";
	string newfilename;
	cin >> newfilename;
	strcpy(newfile->filename, newfilename.c_str());
	newfile->nextufd = NULL;
	newfile->nextlog = NULL;
	newfile->filelength = 0;
	if (head == NULL)
	{
		//����Ϊ�� 
		head = newfile;
		user->next = head;
		cout << "�½��ļ�" << head->filename << "�ɹ�!" << endl;
	}
	else
	{
		while (tail->nextufd != NULL)
		{
			if (!strcmp(tail->filename, newfile->filename))
			{
				//�������
				isrepeat = true;
			}
			//tailָ��β���
			tail = tail->nextufd;
		}
		if (!strcmp(tail->filename, newfile->filename))
		{
			//���β����Ƿ�����
			isrepeat = true;
		}
		if (!isrepeat)
		{
			tail->nextufd = newfile;
			cout << "�½��ļ�" << tail->nextufd->filename << "�ɹ�" << endl;
		}
		else
		{
			cout << "������������ȡ���½�" << endl;
			free(newfile);
		}
	}
	Sleep(1000);
}

void open_file(struct MFD *user, struct AFD *openfile)
{
	//���ļ�
	//����AFDͷ��㲻�������
	bool match_ufd = false;//Ĭ��UFD������û��ƥ����ļ���
	bool match_afd = false;//Ĭ��AFD������û��ƥ����ļ���
	string s_open_filename = "";
	cout << ednl << "������Ҫ�򿪵��ļ���: ";
	cin >> s_open_filename;
	UFD *p,*inx;
	p = user->next;
	inx = p;
	AFD *a, *head, *newopenfile;	
	head = openfile;//AFDͷ���
	a = head;
	while (p != NULL)
	{
		//��UFD����
		if (!strcmp(p->filename, s_open_filename.c_str()))
		{
			//��ƥ����ļ���
			match_ufd = true;
			inx = p;
			break;
		}
		p = p->nextufd;
	}
	if (!match_ufd)
	{
		cout << "UFD:�û�" << user->username << "���ļ�Ŀ¼��û���ҵ��ļ���Ϊ" << s_open_filename << "���ļ�" << ednl;
	}
	else
	{
		//��AFD����
		while (a->nextafd != NULL)
		{
			if (!strcmp(a->filename, s_open_filename.c_str()))
			{
				//��ƥ����ļ���
				match_afd = true;
			}
			a = a->nextafd;
		}
		if (!strcmp(a->filename, s_open_filename.c_str()))
		{
			//��ƥ����ļ���
			match_afd = true;
		}
		if (match_afd)
		{
			cout << "AFD:�ļ���Ϊ" << s_open_filename << "���ļ��Ѿ���" << ednl;
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
			cout << "�ļ�" << newopenfile->filename << "�򿪳ɹ�" << ednl;
		}
	}
	match_afd = false;
	match_ufd = false;
	Sleep(1500);
}

void display_directory(struct MFD *user)
{
	//��ʾĿ¼
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
	cout << "���� " << i_count << " ���ļ�����ȫ����ʾ." << endl;
	Sleep(3000);
}

void close_file(struct MFD *user, struct AFD *openfile) 
{
	//�ر��ļ�
	cout << ednl;
	bool match_afd = false;//Ĭ��AFD������û��ƥ����ļ���
	bool match_ufd = false;//Ĭ��UFD������û��ƥ����ļ���
	string s_closefilename = "";
	cout << "������Ҫ�رյ��ļ���: ";
	cin >> s_closefilename;
	AFD *a, *head, *inx, *befinx;
	head = openfile;//AFDͷ���
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
		cout << "AFD:û���ļ��Ǵ򿪵�" << ednl;
	}
	else
	{
		while (a->nextafd != NULL)
		{
			//��AFD����
			if (!strcmp(a->filename, s_closefilename.c_str()))
			{
				//��ƥ����ļ���
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
			//��ƥ����ļ���
			match_afd = true;
			inx = a;
		}
		if (a->flag == 0)
		{
			//ɾ�����ռ�
			befinx->nextafd = inx->nextafd;
			free(inx);
			cout << "�ļ�" << s_closefilename << "û�б��޸Ĺ�" << ednl;

		}
		else
		{
			//==========================================================
			//����¼���Ƶ�UFD��
			while (p != NULL)
			{
				//��UFD����
				if (!strcmp(p->filename, s_closefilename.c_str()))
				{
					//UFD��ƥ����ļ���
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
				cout << "LOG:��¼�Ѹ��Ƶ��û�" << user->username << "��UFD��" << ednl;
			}
			else
			{
				cout << "LOG:��¼����ʧ�ܣ���Ҳ��֪��Ϊʲô" << ednl;
				cout << "UFD:û�����û�" << user->username << "��UFD���ҵ��ļ���Ϊ" << s_closefilename << "���ļ�" << endl;
			}
			//==========================================================
			//cout << "flag��Ϊ0" << endl;
			befinx->nextafd = inx->nextafd;
			free(inx);

			inx->nextafd = NULL;
			inx->filelength = 0;
			string init = "";
			strcpy(inx->filename, init.c_str());
			inx->nextlog = NULL;
		}
		cout << "AFD:�ļ�" << s_closefilename << "�Ѿ����ر�" << ednl;
		match_afd = false;
	}	
	Sleep(1500);
}

void display_openedfile(struct AFD *openfile) 
{
	//��ʾ�Ѿ��򿪵��ļ�
	//����AFDͷ��㲻�������
	AFD *p = openfile;
	string s_filename = "";
	int i_count = -1;
	if (p->nextafd == NULL)
	{
		//AFD:û�б��򿪵��ļ�
		cout << ednl << "û���ļ�����" << ednl;
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
		cout << "���� " << i_count << " ���ļ�����ȫ����ʾ." << endl;
	}
	Sleep(3000);
}

void delete_file(struct MFD *user, struct AFD *openfile) 
{
	//ɾ���ļ�
	//����AFDͷ��㲻�������
	cout << endl;
	if (openfile->nextafd = NULL)
	{
		cout << "AFD:û���ļ�����" << ednl;
	}
	else
	{
		bool match_ufd = false;//Ĭ��UFD������û��ƥ����ļ���
		bool match_afd = false;//Ĭ��AFD������û��ƥ����ļ���
		string s_delete_filename = "";
		cout << "������Ҫɾ�����ļ���: ";
		cin >> s_delete_filename;
		UFD *p, *head, *inx, *befinx;
		head = user->next;//UFDͷ���
		p = head;
		befinx = head;
		inx = befinx->nextufd;
		AFD *a = openfile;//AFDͷ���

		while (p != NULL)
		{
			//��UFD����
			if (!strcmp(p->filename, s_delete_filename.c_str()))
			{
				//UFD��ƥ����ļ���
				match_ufd = true;
				inx = p;
				break;
			}
			befinx = p;
			p = p->nextufd;
		}
		//if (!strcmp(a->filename, s_delete_filename.c_str()) && match_ufd == false)
		//{
		//	//UFD��ƥ����ļ���
		//	match_ufd = true;
		//	inx = p;
		//}
		while (a->nextafd != NULL)
		{
			//��AFD����
			if (!strcmp(a->filename, s_delete_filename.c_str()))
			{
				//AFD��ƥ����ļ���
				match_afd = true;
			}
			a = a->nextafd;
		}
		if (!strcmp(a->filename, s_delete_filename.c_str()))
		{
			//AFD��ƥ����ļ���
			match_afd = true;
		}

		if (match_ufd)
		{
			//p = head;
			//match_ufd = false;
			//��Ҫɾ����������ļ�
			if (match_afd)
			{
				//����ļ��Ѿ�����
				cout << "AFD:�ļ�" << s_delete_filename << "�Ѿ�����" << endl;
				cout << "AFD:�����ر��ļ�" << s_delete_filename << ednl;
				close_file_in_delete(user, openfile, s_delete_filename);
			}
			///////////////////////

			if (inx == head)
			{
				//UFD��ͷ���������
				if (head->nextufd == NULL)
				{
					//���Ҫɾ������ͷ������޺�̽��
					//free(inx);
					//head = NULL;
					user->next = NULL;
				}
				else
				{
					//���Ҫɾ������ͷ������к�̽��
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
			
			cout << "UFD:�ļ�" << s_delete_filename << "�ѱ�ɾ��" << ednl;
		}
		else
		{
			cout << "UFD:û���ҵ��ļ���Ϊ" << s_delete_filename << "���ļ�" << endl;
		}
		match_afd = false;
		match_ufd = false;
	}	
	Sleep(1500);
}

void close_file_in_delete(struct MFD *user, struct AFD *openfile, string filename)
{
	//��ɾ���ļ��Ĺ����У�����ļ��Ѿ���AFD�У��Ѿ����򿪣������ô˺������ر��ļ�
	bool match_afd = false;//Ĭ��AFD������û��ƥ����ļ���
	bool match_ufd = false;//Ĭ��UFD������û��ƥ����ļ���
	string s_closefilename = "";
	s_closefilename = filename;
	AFD *a, *head, *inx, *befinx;
	head = openfile;//AFDͷ���
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
		//��AFD����
		if (!strcmp(a->filename, s_closefilename.c_str()))
		{
			//��ƥ����ļ���
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
		//��ƥ����ļ���
		match_afd = true;
		inx = a;
	}
	if (a->flag == 0)
	{
		//ɾ�����ռ�
		befinx->nextafd = inx->nextafd;
		free(inx);
		cout << "AFD:�ļ�" << s_closefilename << "�Ѿ����ر�" << ednl;
	}
	else
	{
		//==========================================================
		//����¼���Ƶ�UFD��
		while (p != NULL)
		{
			//��UFD����
			if (!strcmp(p->filename, s_closefilename.c_str()))
			{
				//UFD��ƥ����ļ���
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
			cout << "LOG:��¼�Ѹ��Ƶ��û�" << user->username << "��UFD��" << ednl;
		}
		else
		{
			cout << "LOG:��¼����ʧ�ܣ���Ҳ��֪��Ϊʲô" << ednl;
			cout << "UFD:û�����û�" << user->username << "��UFD���ҵ��ļ���Ϊ" << s_closefilename << "���ļ�" << endl;
		}
		//==========================================================
		//cout << "flag��Ϊ0" << endl;
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
	//�ر��û�
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
					//��UFD���ҵ�ͬ���ļ�
					u->filelength = a->filelength;
					u->nextlog = a->nextlog;
					cout << "AFD:�ļ�" << u->filename << "�ļ�¼�Ѿ������Ƶ�UFD��" << ednl;
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
	//д�ļ�
	cout << ednl;
	bool match_afd = false;//Ĭ��AFD������û��ƥ����ļ���
	bool match_ufd = false;//Ĭ��UFD������û��ƥ����ļ���
	string s_write_filename = "";
	string log_name = "";
	string los_sex = "";
	FILELOG *newlog = (struct FILELOG*)malloc(LOGLEN);
	FILELOG *loghead, *tail;
	UFD *ufd_head, *p,*ufd_inx,*ufd_befinx;
	ufd_head = user->next;
	p = ufd_head;
	cout << "�������ļ���:";
	cin >> s_write_filename;
	ufd_befinx = ufd_head;
	ufd_inx = ufd_befinx->nextufd;

	////////////////////////////////////////////////////////////////
	
	//string s_closefilename = "";
	//cout << ednl << "������Ҫ�رյ��ļ���: ";
	//cin >> s_closefilename;
	AFD *a, *head, *inx, *befinx;
	head = openfile;//AFDͷ���
	a = head;
	befinx = head;
	inx = befinx->nextafd;

	while (a->nextafd != NULL)
	{
		//��AFD����
		if (!strcmp(a->filename, s_write_filename.c_str()))
		{
			//AFD��ƥ����ļ���
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
		//AFD��ƥ����ļ���
		match_afd = true;
		inx = a;
	}
	////////////////////////////////////////////////////////////////////
	if (match_afd)
	{
		//��ʼд
		//inx->nextlog = (struct FILELOG*)malloc(LOGLEN);
		loghead = inx->nextlog;
		tail = loghead;
		cout << "����������:";
		cin >> log_name;
		cout << "�������Ա�:";
		cin >> los_sex;
		strcpy(newlog->username, log_name.c_str());
		strcpy(newlog->sex, los_sex.c_str());
		newlog->next = NULL;
		//===============================================================
		if (loghead == NULL)
		{
			//����Ϊ�� 
			loghead = newlog;
			inx->nextlog = loghead;
			//cout << "�½��ļ�" << head->filename << "�ɹ�!" << endl;
			cout << "FIRST LOG:���½�һ������Ϊ" << inx->nextlog->username << " �Ա�Ϊ" << inx->nextlog->sex << "�ļ�¼" << ednl;
		}
		else
		{
			while (tail->next != NULL)
			{
				//if (!strcmp(tail->username, newfile->filename))
				//{
				//	//�������
				//	isrepeat = true;
				//}
				//tailָ��β���
				tail = tail->next;
			}
			tail->next = newlog;
			cout << "LOG:���½�һ������Ϊ" << tail->next->username << " �Ա�Ϊ" << tail->next->sex << "�ļ�¼" << ednl;
			//if (!strcmp(tail->filename, newfile->filename))
			//{
			//	//���β����Ƿ�����
			//	isrepeat = true;
			//}
			//if (!isrepeat)
			//{
			//	tail->nextufd = newfile;
			//	cout << "�½��ļ�" << tail->nextufd->filename << "�ɹ�" << endl;
			//}
			//else
			//{
			//	cout << "������������ȡ���½�" << endl;
			//	free(newfile);
			//}
		}
		//===============================================================
		inx->flag = 1;
		inx->filelength = inx->filelength + 1;

		//����¼���Ƶ�UFD��
		while (p != NULL)
		{
			//��UFD����
			if (!strcmp(p->filename, s_write_filename.c_str()))
			{
				//UFD��ƥ����ļ���
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
			//cout << "LOG:��¼�Ѹ��Ƶ��û�" << user->username << "��UFD��" << ednl;
		}
		else
		{
			cout << "LOG:��¼����ʧ�ܣ���Ҳ��֪��Ϊʲô" << ednl;
			cout << "UFD:û�����û�" << user->username << "��UFD���ҵ��ļ���Ϊ" << s_write_filename << "���ļ�" << endl;
		}
	}
	else
	{
		cout << "AFD:û���ҵ��ļ���Ϊ" << s_write_filename << "���ļ�" << endl;
		cout << "����û�д������ļ����򴴽���û�д�" << ednl;
		free(newlog);
	}
	Sleep(1500);
}

void read_file(struct MFD *user, struct AFD *openfile)
{
	//���ļ�

	cout << ednl;
	//int Ri = 0;//��Ri����¼
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
		//	cout << "�ļ�" << a->filename << "û���޸ļ�¼" << endl;
		//}
		//else
		//{
			log_head = a->nextlog;
			f = log_head;
			while (f != NULL)
			{
				cout << "�ļ�" << a->filename << "�ĵ�" << count << "��¼��:";
				cout << "����:" << f->username << "  �Ա�:" << f->sex << ednl;
				f = f->next;
				count++;
				inall++;
			}
		//}		
		a = a->nextafd;
		count = 1;
		cout << ednl;
	}
	cout << "ȫ��" << inall << "����¼�����" << ednl;

	Sleep(inall*1000);
}

void read_file_log(struct MFD *user, struct AFD *openfile)
{
	//��ȡָ���ļ��ĵ�Ri����¼
	bool match_afd = false;//Ĭ��AFD������û��ƥ����ļ���
	bool match_log = false;//Ĭ��LOG������û��ƥ��ļ�¼
	cout << ednl;
	int Ri = 0;//��Ri����¼
	string s_filename = "";//ָ����һ���ļ���
	UFD *ufd_head, *u;
	ufd_head = user->next;
	u = ufd_head;
	AFD *afd_head, *a;
	afd_head = openfile;
	a = afd_head->nextafd;
	FILELOG *log_head, *f;
	int count = 1;
	int inall = 0;

	cout << "������Ҫ��ȡ���ļ���:";
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
		cout << "AFD:û���ҵ��ļ���Ϊ" << s_filename << "���ļ�" << ednl;
		cout << "�ļ�����û�б����������ߴ�����û�б���" << ednl;
	}
	else
	{
		cout << "AFD:����AFD���ҵ��ļ���Ϊ" << a->filename << "���ļ�" << endl;
		cout << "������Ҫ��ȡ�ļ�" << s_filename << "�ĵڼ�����¼��>0��:";
		cin >> Ri;
		if (Ri <= 0)
		{
			cout << "�����ֵ������Ҫ��" << ednl;
		}
		else
		{
			a = afd_head->nextafd;
			while (a != NULL)
			{
				//if (a->flag == 0)
				//{
				//	cout << "�ļ�" << a->filename << "û���޸ļ�¼" << endl;
				//}
				//else
				//{
				log_head = a->nextlog;
				f = log_head;
				while (f != NULL)
				{
					if (count == Ri && (!strcmp(s_filename.c_str(), a->filename)))
					{
						//�ļ�����ͬ���ǵ�Ri����¼
						cout << "�ļ�" << a->filename << "�ĵ�" << count << "��¼��:";
						cout << "����:" << f->username << "  �Ա�:" << f->sex << ednl;
						match_log = true;
					}
					//cout << "�ļ�" << a->filename << "�ĵ�" << count << "��¼��:";
					//cout << "����:" << f->username << "  �Ա�:" << f->sex << ednl;
					f = f->next;
					count++;
					inall++;
				}
				//}		
				a = a->nextafd;
				count = 1;
				//cout << ednl;
			}
			//cout << "ȫ��" << inall << "����¼�����" << ednl;
			if (match_log)
			{
				cout << "���ļ�����" << endl;
			}
			else
			{
				cout << "LOG:�ļ�" << s_filename << "��û���ҵ���" << Ri << "����¼" << ednl;
			}
		}
	}	

	Sleep(3000);
}

void exit(){}//�˳�

void change_file(struct MFD *user, struct AFD *openfile)
{
	//д�ļ�
	cout << ednl;
	bool match_afd = false;//Ĭ��AFD������û��ƥ����ļ���
	bool match_ufd = false;//Ĭ��UFD������û��ƥ����ļ���
	string s_write_filename = "";
	string log_name = "";
	string los_sex = "";
	FILELOG *newlog = (struct FILELOG*)malloc(LOGLEN);
	FILELOG *loghead, *tail,*log_inx;
	log_inx = NULL;
	UFD *ufd_head, *p, *ufd_inx, *ufd_befinx;
	ufd_head = user->next;
	p = ufd_head;
	cout << "�������ļ���:";
	cin >> s_write_filename;
	ufd_befinx = ufd_head;
	ufd_inx = ufd_befinx->nextufd; 
	
	//log_inx = loghead;

	////////////////////////////////////////////////////////////////

	//string s_closefilename = "";
	//cout << ednl << "������Ҫ�رյ��ļ���: ";
	//cin >> s_closefilename;
	AFD *a, *head, *inx, *befinx;
	head = openfile;//AFDͷ���
	a = head;
	befinx = head;
	inx = befinx->nextafd;

	while (a->nextafd != NULL)
	{
		//��AFD����
		if (!strcmp(a->filename, s_write_filename.c_str()))
		{
			//AFD��ƥ����ļ���
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
		//AFD��ƥ����ļ���
		match_afd = true;
		inx = a;
	}
	////////////////////////////////////////////////////////////////////
	if (match_afd)
	{
		//��ʼд
		//inx->nextlog = (struct FILELOG*)malloc(LOGLEN);
		bool isrepeat = false;
		loghead = inx->nextlog;
		tail = loghead;
		log_inx = loghead;
		cout << "��ԭ��¼������:";
		cin >> log_name;
		//cout << "�������Ա�:";
		//cin >> los_sex;
		strcpy(newlog->username, log_name.c_str());
		strcpy(newlog->sex, los_sex.c_str());
		newlog->next = NULL;
		//===============================================================
		if (loghead == NULL)
		{
			//����Ϊ�� 
			//loghead = newlog;
			//inx->nextlog = loghead;
			////cout << "�½��ļ�" << head->filename << "�ɹ�!" << endl;
			//cout << "FIRST LOG:���½�һ������Ϊ" << inx->nextlog->username << " �Ա�Ϊ" << inx->nextlog->sex << "�ļ�¼" << ednl;
			cout << "�ļ�û�м�¼" << endl;
		}
		else
		{
			while (tail->next != NULL)
			{
				if (!strcmp(tail->username, log_name.c_str()))
				{
					//�������
					isrepeat = true;
					log_inx = tail;
					cout << "���ҵ���Ϊ" << log_name << "�ļ�¼" << ednl;
					break;
				}
				//tailָ��β���
				tail = tail->next;
			}
			string newname, newsex;
			cout << "�����µ�����:";
			cin >> newname;
			cout << "�����µ��Ա�:";
			cin >> newsex;
			strcpy(log_inx->username, newname.c_str());
			strcpy(log_inx->sex, newsex.c_str());
			cout << "�ѽ���¼�������޸�Ϊ" << newname;
			cout << "�ѽ���¼���Ա��޸�Ϊ" << newsex;
			//tail->next = newlog;
			//cout << "LOG:���½�һ������Ϊ" << tail->next->username << " �Ա�Ϊ" << tail->next->sex << "�ļ�¼" << ednl;
		}
		//===============================================================
		inx->flag = 1;
		inx->filelength = inx->filelength + 1;

		//����¼���Ƶ�UFD��
		while (p != NULL)
		{
			//��UFD����
			if (!strcmp(p->filename, s_write_filename.c_str()))
			{
				//UFD��ƥ����ļ���
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
			cout << "LOG:��¼�Ѹ��Ƶ��û�" << user->username << "��UFD��" << ednl;
		}
		else
		{
			cout << "LOG:��¼����ʧ�ܣ���Ҳ��֪��Ϊʲô" << ednl;
			cout << "UFD:û�����û�" << user->username << "��UFD���ҵ��ļ���Ϊ" << s_write_filename << "���ļ�" << endl;
		}
	}
	else
	{
		cout << "AFD:û���ҵ��ļ���Ϊ" << s_write_filename << "���ļ�" << endl;
		cout << "����û�д������ļ����򴴽���û�д�" << ednl;
		free(newlog);
	}
	Sleep(1500);
}
