#include"pokemon.h"

fd_set allSockets;
struct fd_es_set esSet = { 0,{0},{NULL} };

bool server::sendPok(SOCKET socketClient, player p)//发送精灵信息
{
	stringstream sendss;
	char sendBuf[1500] = { '\0' };
	sendss << p.pokNum << " ";
	for (int i = 1; i <= 6; i++) sendss << p.medal[i] << " ";
	sendss << p.winnum <<" "<< p.totalnum<<" ";
	for (vector<Pokemon*>::iterator it = p.poks.begin(); it != p.poks.end(); it++)
	{
		sendss << (*it)->getSeq() << " " << (*it)->getLv() << " " << (*it)->exp << " ";
	}
	sendss << "\0";
	memcpy(sendBuf, sendss.str().c_str(), 1500);
	if (SOCKET_ERROR == send(socketClient, sendBuf, strlen(sendBuf), 0))
	{
		int a = WSAGetLastError();
		printf("send fail,error code:%d\n", a);
		return false;
	}
	return true;
}

bool server::acceptEvent(int clientIndex)//建立连接
{
	//正常处理
	SOCKET socketClient = accept(esSet.sockall[clientIndex], NULL, NULL);
	if (INVALID_SOCKET == socketClient)	return false;

	WSAEVENT wsaClientEvent = WSACreateEvent();//创建事件对象
	if (WSA_INVALID_EVENT == wsaClientEvent)
	{
		closesocket(socketClient);
		return false;
	}
	if (SOCKET_ERROR == WSAEventSelect(socketClient, wsaClientEvent, FD_READ | FD_CLOSE | FD_WRITE))
	{
		closesocket(socketClient);
		WSACloseEvent(wsaClientEvent);
		return false;
	}

	//装进结构体
	esSet.sockall[esSet.count] = socketClient;
	esSet.eventall[esSet.count] = wsaClientEvent;
	printf("用户%d已连接服务器\n", esSet.count);
	esSet.count++;

	return true;
}

bool server::readEvent(int clientIndex)//读取收到的数据包
{
	char strRecv[1500] = { 0 };
	if (SOCKET_ERROR == recv(esSet.sockall[clientIndex], strRecv, 1499, 0))
	{
		int a = WSAGetLastError();
		printf("recv fail,error code:%d\n", a);
		return false;
	}//接收数据信息

	printf("recv data:%s\n", strRecv);

		int choice=-1;
		stringstream ss;
		string Name,Password;

		ss << strRecv;
		ss >> choice;
		
		if (choice == CHOICE_LOGIN)//登录
		{
			ss>> Name>>Password;
			player p = player(Name);//根据数据包信息构造player对象
			if (p.login(Name,Password, p,clientIndex))
			{
				if (!sendPok(esSet.sockall[clientIndex], p))//发送用户的精灵信息
				{
					cout << "精灵信息发送失败" << endl;
					return false;
				}
				else
				{
					cout << "登录成功" << endl;
					return true;
				}
			}
			else
			{
				if (!SOCKET_ERROR == send(esSet.sockall[clientIndex], "-1", strlen("-1"), 0))//发送失败消息
				{
					cout << "消息发送失败" << endl;
					return false;
				}
				cout << "登录失败" << endl;
				return false;
			}
		}
		else if (choice == CHOICE_REGIST)//注册
		{
			ss >> Name>>Password;
			player p = player(Name);//根据数据包信息构造player对象
			
			if (p.regist(Name, Password,p))
			{
				if (!sendPok(esSet.sockall[clientIndex], p))//发送用户的精灵信息
				{
					cout << "精灵信息发送失败" << endl;
					return false;
				}
				else
				{
					cout << "注册成功" << endl;
					return true;
				}
			}
			else
			{
				if (!SOCKET_ERROR == send(esSet.sockall[clientIndex], "-1", strlen("-1"), 0))//发送失败消息
				{
					cout << "消息发送失败" << endl;
					return false;
				}
				cout << "注册失败" << endl;
				return false;
			}
		}
		else if (choice == CHOICE_CHECK)//查看所有用户的信息
		{
			stringstream ss;
			for (vector<player>::iterator it = Players.begin(); it != Players.end()&&it->getName()!=""; it++)
			{
				ss << it->name << " " << it->pokNum<<" "<<it->Login<< endl;
				for (int i = 1; i <= 6; i++) ss << it->medal[i]<<" ";
				ss << it->winnum << " " << it->totalnum << " ";
				for (vector<Pokemon*>::iterator itt = it->poks.begin(); itt != it->poks.end(); itt++)
				{
					ss << (*itt)->getSeq() << " " << (*itt)->getLv() << " " << (*itt)->exp << endl;//写入精灵信息
				}
			}
			ss << '\0';
			char sendBuf[1500] = {'\0'};
			memcpy(sendBuf, ss.str().c_str(), ss.str().length());
			if (SOCKET_ERROR == send(esSet.sockall[clientIndex], sendBuf, strlen(sendBuf), 0))
			{
				int a = WSAGetLastError();
				printf("send fail,error code:%d\n", a);
				return false;
			}
			return true;
		}
		else if (choice == CHOICE_LOGOUT)
		{
			for (vector<player>::iterator it = Players.begin(); it != Players.end(); it++)
			{
				if (clientIndex == it->clientSeq)
				{
					it->Login = 0;
				}
			}
			cout << "用户" << clientIndex << "已登出" << endl;
			return true;
		}
		else if (choice == CHOICE_UPDATE)
		{
		/*保留原有玩家的在线信息*/
		ifstream fs1("playerPok.txt", ifstream::in);
		bool *loginFlag; int *clientSeqs;
		loginFlag = new bool[Players.size()];
		clientSeqs = new int[Players.size()];
		int k = 0;
		for (vector<player>::iterator it = Players.begin(); it != Players.end() && it->getName() != ""; it++, k++)
		{
			loginFlag[k] = it->Login;
			clientSeqs[k] = it->clientSeq;
		}

		/*读包*/
			string playerName;
			ss >> playerName;
			player* pl = new player(playerName);
			ss >> pl->password >> pl->pokNum;
			for (int i = 1; i <= 6; i++) ss >> pl->medal[i];
			ss >> pl->winnum >> pl->totalnum;
			for (int i = 1; i <= pl->pokNum; i++)
			{
				int pokSeq, lv;
				float exp;

				ss >> pokSeq >> lv >> exp;//依次读取精灵编号、等级、经验值

				Pokemon* pok = nullptr;
				pok = pok->newPok(pokSeq);//创建精灵
				pok->initPok(lv, exp);//将精灵初始化为玩家之前升级后的状态
				pl->poks.push_back(pok);
			}

			/*重写数据文件*/
			ofstream fs("playerPok.txt", ios::out | ios::trunc);

			for (vector<player>::iterator it = Players.begin(); it != Players.end()&& it->getName() != ""; it++)
			{
				if (playerName == it->getName())
				{
					(*it) = *pl;
				}
				it->writePlayer(fs);
			}
			fs.close();

			/*更新Players*/
			Players.clear();
			while (!fs1.eof())
				readPlayer(fs1);//读取文件中玩家信息
			fs1.close();
			k = 0;
			for (vector<player>::iterator it = Players.begin(); it != Players.end() && it->getName() != ""; it++, k++)
			{
				it->Login = loginFlag[k];
				it->clientSeq = clientSeqs[k];
			}
			delete loginFlag;
			delete clientSeqs;

			return true;
		}
		else return false;
}

void server::closeEvent(WSANETWORKEVENTS NetworkEvents,int i)//客户端下线处理
{
	printf("用户%d下线\n",i);
	printf("client force out:%d\n", NetworkEvents.iErrorCode[FD_CLOSE_BIT]);
	//清理下线客户端、套接字、事件
	for (vector<player>::iterator it = Players.begin(); it != Players.end(); it++)
	{
		if (i==it->clientSeq)
		{
			it->Login = 0;
		}
	}
	closesocket(esSet.sockall[i]);
	esSet.sockall[i] = esSet.sockall[esSet.count - 1];
	WSACloseEvent(esSet.eventall[i]);
	esSet.eventall[i] = esSet.eventall[esSet.count - 1];
	esSet.count--;
}

bool server::connectClient()//运行服务器
{
	WORD wdVersion = MAKEWORD(2, 2);
	WSADATA wdSockMsg;
	int nRes = WSAStartup(wdVersion, &wdSockMsg);

	if (0 != nRes)
	{
		switch (nRes)
		{
		case WSASYSNOTREADY://系统配置问题，重启电脑，检查ws2_32库是否存在
			cout << "重启电脑，或者检查网络库" << endl; break;
		case WSAVERNOTSUPPORTED://版本库不支持
			cout << "请更新网络库" << endl; break;
		case WSAEINPROGRESS://运行期间出现阻塞
			cout << "请重新启动" << endl; break;
		case WSAEPROCLIM://Windows Socket限制了应用程序数量
			cout << "请关掉一些不必要的软件" << endl; break;
		}
		return 0;
	}

	if (2 != HIBYTE(wdSockMsg.wVersion) || 2 != LOBYTE(wdSockMsg.wVersion))
	{
		cout << "版本出错" << endl;
		//版本不对，关闭网络库
		WSACleanup();
		return 0;
	}

	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建服务器socket
	if (INVALID_SOCKET == socketServer)
	{
		int a = WSAGetLastError();
		cout << "创建服务器socket出错，错误码:" << a << endl;
		//清理网络库
		WSACleanup();
		return 0;
	}

	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (SOCKET_ERROR == bind(socketServer, (const struct sockaddr *)&si, sizeof(si)))
	{
		int a = WSAGetLastError();
		cout << "绑定出错，错误码:" << a<<endl;
		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN))
	{
		int a = WSAGetLastError();
		cout << "监听出错，错误码:" << a << endl;
		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	WSAEVENT eventServer = WSACreateEvent();//创建事件
	if (WSA_INVALID_EVENT == eventServer)
	{
		int a = WSAGetLastError();
		cout << "创建服务器事件出错，错误码:" << a << endl;
		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	if (SOCKET_ERROR == WSAEventSelect(socketServer, eventServer, FD_ACCEPT))
	{
		int a = WSAGetLastError();
		cout << "服务器socket加入出错，错误码:" << a << endl;
		WSACloseEvent(eventServer);//释放句柄
		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	esSet.eventall[esSet.count] = eventServer;
	esSet.sockall[esSet.count] = socketServer;
	esSet.count++;
	ifstream fs("playerPok.txt", ifstream::in);
	while (!fs.eof())
		readPlayer(fs);//读取文件中玩家信息
	fs.close();

	while (1)
	{
		for (int i = 0; i < esSet.count; i++)
		{
			DWORD nRes = WSAWaitForMultipleEvents(1, &esSet.eventall[i], FALSE, 50, FALSE);
			if (WSA_WAIT_FAILED == nRes)
			{
				int a = WSAGetLastError();
				printf("等待事件出错，错误码%d\n", a);
				continue;
			}
			if (WSA_WAIT_TIMEOUT == nRes) continue;

			WSANETWORKEVENTS NetworkEvents;
			if (SOCKET_ERROR == WSAEnumNetworkEvents(esSet.sockall[i], esSet.eventall[i], &NetworkEvents))
			{
				int a = WSAGetLastError();
				printf("得到事件出错，错误码%d\n", a);
				break;
			}
			else
			{
				if (NetworkEvents.lNetworkEvents&FD_ACCEPT)
				{
					if (0 == NetworkEvents.iErrorCode[FD_ACCEPT_BIT])
					{
						acceptEvent(i);
					}
					else continue;
				}

				if (NetworkEvents.lNetworkEvents&FD_READ)
				{
					if (0 == NetworkEvents.iErrorCode[FD_READ_BIT])
					{
						if (!readEvent(i)) continue;
					}
					else
					{
						printf("socket fail,error code:%d\n", NetworkEvents.iErrorCode[FD_READ_BIT]);
						continue;
					}
				}
				if (NetworkEvents.lNetworkEvents&FD_CLOSE)
				{
					closeEvent(NetworkEvents, i);
				}
			}
		}
	}
	WSACloseEvent(eventServer);//释放句柄
	closesocket(socketServer);
	WSACleanup();
}

//int main()
//{
//	server server;
//	while (true)
//	{
//		server.connectClient();
//	}
//}