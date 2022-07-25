#include"pokemon.h"

vector<player> Players;//�洢�û���Ϣ������

void player::assignPok()//ϵͳ�����������1������
{
	srand(time(NULL));
	int pokSeq1 = (rand() % POKNUM) + 1;
	
	int pokSeq2 = (rand() % POKNUM) + 1;
	
	int pokSeq3 = (rand() % POKNUM) + 1;
	while (pokSeq2 == pokSeq1)
	{
		
		pokSeq2 = (rand() % POKNUM) + 1;//��֤�������鲻�ظ�
	}
	while (pokSeq3 == pokSeq2 || pokSeq3 == pokSeq1)
	{
		
		pokSeq3 = (rand() % POKNUM) + 1;
	}

	Pokemon* p1 = nullptr;
	p1 = p1->newPok(pokSeq1);
	Pokemon* p2 = nullptr;
	p2 = p2->newPok(pokSeq2);
	Pokemon* p3 = nullptr;
	p3 = p3->newPok(pokSeq3);

	pokNum = 3;
	poks = { p1,p2,p3 };//����ʼ����װ��vector
}

bool player::regist(string Name,string Password,player& p)//ע��
{
	for (vector<player>::iterator it = Players.begin(); it != Players.end(); it++)
	{
		if (Name == it->name) return false;//����
	}

	p.password = Password;
	p.assignPok();
	ofstream fs("playerPok.txt", ofstream::app);
	p.writePlayer(fs);
	fs.close();
	for (vector<player>::iterator it = Players.begin(); it != Players.end(); it++)
	{
		if (it->getName() == "")
		{
			it=Players.erase(it);
			break;
		}
	}
	Players.push_back(p);//����ע����û������������
	return true;
}

bool player::login(string Name,string Password,player& p,int Seq)//��¼
{
	for (vector<player>::iterator it = Players.begin(); it != Players.end()&& it->getName() != ""; it++)
	{
		if (Name == it->name&&Password==it->password)
		{
			p = *it;//ƥ���û���
			p.Login = 1;
			it->Login = 1;
			it->clientSeq = Seq;
			return true;
		}
	}
	return false;
}

void readPlayer(ifstream& fs)//���ļ����ж�ȡһ���������
{
	if (!fs) { cout << "���������ļ�ʧ��\n"; }
	else
	{
		/*���ζ�ȡ�û��������롢����������ѫ�¡�Ӯ�ĳ��Ρ��ܳ���*/
		string playerName;
		fs >> playerName;
		player p = player(playerName);
		fs >> p.password >> p.pokNum;
		for (int i = 1; i <= 6; i++) fs >>p.medal[i];
		fs >> p.winnum >> p.totalnum;
		for (int i = 1; i <= p.pokNum; i++)
		{
				int pokSeq, lv;
				float exp;

				fs >> pokSeq >> lv >> exp;//���ζ�ȡ�����š��ȼ�������ֵ

				Pokemon* pok = nullptr;
				pok = pok->newPok(pokSeq);//��������
				pok->initPok(lv, exp);//�������ʼ��Ϊ���֮ǰ�������״̬
				p.poks.push_back(pok);
		}
		Players.push_back(p);
	}
}

void player::writePlayer(ofstream& fs)//дһ���������
{
	if (!fs.is_open()){ cout << "������д�ļ�ʧ��\n"; }
	else
	{
		fs << name << " " <<password<<" "<< pokNum << endl;
		for (int i = 1; i <= 6; i++) fs << medal[i] << " ";
		fs <<endl;
		fs << winnum <<" "<<totalnum<<endl;
		for (vector<Pokemon*>::iterator it = poks.begin(); it != poks.end(); it++)
		{
			fs << (*it)->getSeq() << " " << (*it)->getLv() << " " << (*it)->exp<<endl;//д�뾫����Ϣ
		}
	}
}

void player::printPlayerInfo()//��ӡ�����Ϣ
{
	cout << "�û�����" << name << endl;
	cout << "���о���������" << pokNum << endl;
	for (vector<Pokemon*>::iterator it = poks.begin(); it != poks.end(); it++)
	{
		(*it)->printProperty(**it);
	}
}
/*
int main()
{
	string Name;
	int choice;

	while (true)
	{
		ifstream fs("playerPok.txt", ifstream::in);
		while (!fs.eof())
			readPlayer(fs);
		fs.close();
		cout << "��ѡ��1.ע�� 2.��¼ 3.��ӡ��ע�������Ϣ" << endl;
		cin >> choice;

		if (choice == 1)
		{
			cout << "�������û���:";
			cin >> Name;
			player p = player(Name);
			if (p.regist(Name, p)) cout << "ע��ɹ�" << endl;
			else cout << "ע��ʧ��" << endl;
		}
		else if (choice == 2)
		{
			cout << "�������û���:";
			cin >> Name;
			player p = player(Name);
			if (p.login(Name, p)) cout << "��¼�ɹ�" << endl;
			else cout << "��¼ʧ��" << endl;
		}
		else if (choice == 3)
		{
			for (vector<player>::iterator it = Players.begin(); it != Players.end()&&it->getName()!=""; it++)
				it->printPlayerInfo();
		}
		else break;
	}
}
*/
