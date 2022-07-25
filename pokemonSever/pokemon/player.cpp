#include"pokemon.h"

vector<player> Players;//存储用户信息的容器

void player::assignPok()//系统随机分配三个1级精灵
{
	srand(time(NULL));
	int pokSeq1 = (rand() % POKNUM) + 1;
	
	int pokSeq2 = (rand() % POKNUM) + 1;
	
	int pokSeq3 = (rand() % POKNUM) + 1;
	while (pokSeq2 == pokSeq1)
	{
		
		pokSeq2 = (rand() % POKNUM) + 1;//保证三个精灵不重复
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
	poks = { p1,p2,p3 };//将初始精灵装入vector
}

bool player::regist(string Name,string Password,player& p)//注册
{
	for (vector<player>::iterator it = Players.begin(); it != Players.end(); it++)
	{
		if (Name == it->name) return false;//重名
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
	Players.push_back(p);//将新注册的用户加入玩家容器
	return true;
}

bool player::login(string Name,string Password,player& p,int Seq)//登录
{
	for (vector<player>::iterator it = Players.begin(); it != Players.end()&& it->getName() != ""; it++)
	{
		if (Name == it->name&&Password==it->password)
		{
			p = *it;//匹配用户名
			p.Login = 1;
			it->Login = 1;
			it->clientSeq = Seq;
			return true;
		}
	}
	return false;
}

void readPlayer(ifstream& fs)//从文件流中读取一个玩家数据
{
	if (!fs) { cout << "服务器读文件失败\n"; }
	else
	{
		/*依次读取用户名、密码、精灵数量、勋章、赢的场次、总场次*/
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

				fs >> pokSeq >> lv >> exp;//依次读取精灵编号、等级、经验值

				Pokemon* pok = nullptr;
				pok = pok->newPok(pokSeq);//创建精灵
				pok->initPok(lv, exp);//将精灵初始化为玩家之前升级后的状态
				p.poks.push_back(pok);
		}
		Players.push_back(p);
	}
}

void player::writePlayer(ofstream& fs)//写一个玩家数据
{
	if (!fs.is_open()){ cout << "服务器写文件失败\n"; }
	else
	{
		fs << name << " " <<password<<" "<< pokNum << endl;
		for (int i = 1; i <= 6; i++) fs << medal[i] << " ";
		fs <<endl;
		fs << winnum <<" "<<totalnum<<endl;
		for (vector<Pokemon*>::iterator it = poks.begin(); it != poks.end(); it++)
		{
			fs << (*it)->getSeq() << " " << (*it)->getLv() << " " << (*it)->exp<<endl;//写入精灵信息
		}
	}
}

void player::printPlayerInfo()//打印玩家信息
{
	cout << "用户名：" << name << endl;
	cout << "持有精灵数量：" << pokNum << endl;
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
