#include"pokemonClient.h"

vector<player> Players;//存储用户信息的容器

void player::assignPok()//系统随机分配三个1级精灵
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
		pokSeq2 = (rand() % POKNUM) + 1;//保证三个精灵不重复
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
	poks = { p1,p2,p3 };//将初始精灵装入vector
}

bool player::login(string Name,player& p)//登录
{
	for (vector<player>::iterator it = Players.begin(); it != Players.end(); it++)
	{
		if (Name == it->name)
		{
			p = *it;//匹配用户名
			return true;
		}
	}
	return false;
}

void readPlayers(string s)//从字符流中读取一个玩家数据
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

			ss >> pokSeq >> lv >> exp;//依次读取精灵编号、等级、经验值

			Pokemon* pok = nullptr;
			pok = pok->newPok(pokSeq);//创建精灵
			pok->initPok(lv, exp);//将精灵初始化为玩家之前升级后的状态
			p.poks.push_back(pok);//加入玩家持有精灵的vector中
		}
		Players.push_back(p);
	}
}

void player::printPlayerInfo(int pokInfo,stringstream &out)//打印玩家信息，可以选择是否打印精灵详情
{
	out << "用户名：" << name << endl;
	out << "持有精灵数量：" << pokNum << endl;
	for (vector<Pokemon*>::iterator it = poks.begin(); it != poks.end(); it++)
	{
		if(pokInfo==1)
		(*it)->printProperty(**it,out);//打印精灵详情
		else
		{
			out << (*it)->getName() << " " << (*it)->getLv() << endl;//不打印精灵详情
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
		cout << "请选择：1.注册 2.登录 3.打印已注册玩家信息" << endl;
		cin >> choice;

		if (choice == 1)
		{
			cout << "请输入用户名:";
			cin >> Name;
			player p = player(Name);
			if (p.regist(Name, p)) cout << "注册成功" << endl;
			else cout << "注册失败" << endl;
		}
		else if (choice == 2)
		{
			cout << "请输入用户名:";
			cin >> Name;
			player p = player(Name);
			if (p.login(Name, p)) cout << "登录成功" << endl;
			else cout << "登录失败" << endl;
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
