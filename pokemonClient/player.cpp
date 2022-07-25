#include"pokemonClient.h"

vector<player> Players;//�洢�û���Ϣ������

void player::assignPok()//ϵͳ�����������1������
{
	srand(time(NULL));
	int pokSeq1 = (rand() % POKNUM) + 1;
	srand(time(NULL));
	int pokSeq2 = (rand() % POKNUM) + 1;
	srand(time(NULL));
	int pokSeq3 = (rand() % POKNUM) + 1;
	while (pokSeq2 == pokSeq1)
	{
		srand(time(NULL));
		pokSeq2 = (rand() % POKNUM) + 1;//��֤�������鲻�ظ�
	}
	while (pokSeq3 == pokSeq2 || pokSeq3 == pokSeq1)
	{
		srand(time(NULL));
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

bool player::login(string Name,player& p)//��¼
{
	for (vector<player>::iterator it = Players.begin(); it != Players.end(); it++)
	{
		if (Name == it->name)
		{
			p = *it;//ƥ���û���
			return true;
		}
	}
	return false;
}

void readPlayers(string s)//���ַ����ж�ȡһ���������
{
	Players.clear();
	stringstream ss;
	ss.str(s);
	while (!ss.eof())
	{
		string playerName;
		ss >> playerName;
		player p = player(playerName);
		ss >> p.pokNum >> p.Login;
		for (int i = 1; i <= 6; i++) ss >> p.medal[i];
		ss >> p.winnum >> p.totalnum;
		for (int i = 1; i <= p.pokNum; i++)
		{
			int pokSeq, lv;
			float exp;

			ss >> pokSeq >> lv >> exp;//���ζ�ȡ�����š��ȼ�������ֵ

			Pokemon* pok = nullptr;
			pok = pok->newPok(pokSeq);//��������
			pok->initPok(lv, exp);//�������ʼ��Ϊ���֮ǰ�������״̬
			p.poks.push_back(pok);//������ҳ��о����vector��
		}
		Players.push_back(p);
	}
}

void player::printPlayerInfo(int pokInfo,stringstream &out)//��ӡ�����Ϣ������ѡ���Ƿ��ӡ��������
{
	out << "�û�����" << name << endl;
	out << "���о���������" << pokNum << endl;
	for (vector<Pokemon*>::iterator it = poks.begin(); it != poks.end(); it++)
	{
		if(pokInfo==1)
		(*it)->printProperty(**it,out);//��ӡ��������
		else
		{
			out << (*it)->getName() << " " << (*it)->getLv() << endl;//����ӡ��������
		}
	}
	out << endl;
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
