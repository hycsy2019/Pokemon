#include "pokemonClient.h"

extern SOCKET socketServer;//服务器socket

BOOL WINAPI fun(DWORD dwCtrlType)
{
	switch (dwCtrlType)
	{
	case CTRL_CLOSE_EVENT:
		/*登出*/
		if (SOCKET_ERROR == send(socketServer, "3", 1, 0))//发送选项
		{
			int a = WSAGetLastError();
		}
	}
	return true;
}

SOCKET player::connectServer()//连接服务器
{
	SetConsoleCtrlHandler(fun, TRUE);//点×退出

	WORD wdVersion = MAKEWORD(2, 2);
	WSADATA wdSockMsg;
	int nRes = WSAStartup(wdVersion, &wdSockMsg);

	if (0 != nRes)//检查网络库是否顺利打开
	{
		switch (nRes)
		{
		case WSASYSNOTREADY:
			cout << "重启电脑或检查网络库" << endl; break;
		case WSAVERNOTSUPPORTED:
			cout << "请更新网络库" << endl; break;
		case WSAEINPROGRESS:
			cout << "请重新启动" << endl; break;
		case WSAEPROCLIM:
			cout << "请关掉一些不必要的软件"; break;
		}
	}

	if (2 != HIBYTE(wdSockMsg.wVersion) || 2 != LOBYTE(wdSockMsg.wVersion))//检查网络库版本号
	{
		cout << "网络库版本出错" << endl;
		WSACleanup();
		return 0;
	}

	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == socketServer)//检查socket是否成功创建
	{
		int a = WSAGetLastError();
		WSACleanup();
		return 0;
	}

	struct sockaddr_in serverMsg;//绑定服务器socket的地址端口
	inet_pton(AF_INET, "127.0.0.1", &serverMsg.sin_addr.S_un.S_addr);
	serverMsg.sin_family = AF_INET;
	serverMsg.sin_port = htons(12345);
	serverMsg.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (SOCKET_ERROR == connect(socketServer, (const struct sockaddr*)&serverMsg, sizeof(serverMsg)))//检查是否绑定成功
	{
		int a = WSAGetLastError();
		cout << "连接错误，错误码：" << a << endl;
		closesocket(socketServer);
		WSACleanup();
		return false;
	}
	return socketServer;
}

bool player::enter(SOCKET socketServer,int choice,string Password)//进入游戏，注册或登录
{
	stringstream ss;
	ss << choice << " " << name<<" "<<Password<<"\0";
	char sendBuf[1500] = { '\0' };
	memcpy(sendBuf, ss.str().c_str(), 1500);
	
	if (SOCKET_ERROR == send(socketServer,sendBuf, name.length() +Password.length()+ 3, 0))//发送登录或注册的选择+用户名+密码
	{
		int a = WSAGetLastError();
		cout << "发送出错，错误码：" << a<<endl;
		return false;
	}

	char recvBuf[1500] = { 0 };
	int res = recv(socketServer, recvBuf, 1499, 0);
	if (0 == res)
	{
		cout << "接收中断，服务器下线" << endl;
		return false;
	}
	else if (SOCKET_ERROR == res)
	{
		int a = WSAGetLastError();
		cout << "接收出错，错误码" <<a<< endl;
		return false;
	}
	else
	{
		string s = recvBuf;
		stringstream ss(s);

		password = Password;
		//获取玩家持有的精灵信息
		ss >> pokNum;
		for (int i = 1; i <= 6; i++) ss >> medal[i];
		ss >> winnum >> totalnum;
		if (pokNum == -1)
		{
			cout << "失败" << endl;
			return false;
		}
		for (int i = 1; i <= pokNum; i++)
		{
			int pokSeq, lv;
			float exp;

			ss >> pokSeq >> lv >> exp;//依次读取精灵编号、等级、经验值

			Pokemon* pok = nullptr;
			pok = pok->newPok(pokSeq);//创建精灵
			pok->initPok(lv, exp);//将精灵初始化为玩家之前升级后的状态
			poks.push_back(pok);//加入玩家持有精灵的vector中
		}
		return true;
	}
}

/*
int main()
{
	while (1)
	{
		cout << "请选择：0.登录，1.注册" << endl;
		int choice;
		cin >> choice;

		string Name, Password;
		cout << "请输入用户名：";
		cin >> Name;
		player p = player(Name);
		cout << "请输入密码：";
		cin >> Password;

		SOCKET socketServer = p.connectServer();
		int flag=p.enter(socketServer, choice, Password);
		if(flag) p.printPlayerInfo(1);

		while (1)
		{
			if (flag)
			{
				if (choice == 1) break;
				cout << "请选择：1.查看所有用户拥有的精灵 2.查看当前在线用户 3.登出" << endl;
				char c;
				cin >> c;
				if (c != '3')
				{
					if (SOCKET_ERROR == send(socketServer, "2", 1, 0))//发送选项
					{
						int a = WSAGetLastError();
						cout << "发送出错，错误码：" << a << endl;
						return -1;
					}
					char recvBuf[1500] = {'\0'};
					int res = recv(socketServer, recvBuf, 1499, 0);
					if (0 == res)
					{
						cout << "接收中断，服务器下线" << endl;
						return -1;
					}
					else if (SOCKET_ERROR == res)
					{
						int a = WSAGetLastError();
						cout << "接收出错，错误码" << a << endl;
						return -1;
					}
					else
					{
						readPlayers(recvBuf);
						if (c == '1')
						{
							for (vector<player>::iterator it = Players.begin(); it != Players.end() - 1 && it->getName() != ""; it++)
								it->printPlayerInfo(0);
						}
						else if (c == '2')
						{
							cout << "当前在线用户" << endl;
							for (vector<player>::iterator it = Players.begin(); it != Players.end() - 1 && it->getName() != ""; it++)
							{
								if (it->Login) cout << it->getName() << endl;
							}
						}
					}
				}
				else
				{
					if (SOCKET_ERROR == send(socketServer, "3", 1, 0))//发送选项
					{
						int a = WSAGetLastError();
						cout << "发送出错，错误码：" << a << endl;
						return -1;
					}
				
						for (vector<player>::iterator it = Players.begin(); it != Players.end(); it++)
						{
							if (p.getName()==it->getName())
							{
								it->Login = 0;
							}
						}
						break;//跳回登录注册状态
				}
			}
			else return -1;
		}
	}
	return 0;
}
*/