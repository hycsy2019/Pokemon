#include"pokemon.h"

fd_set allSockets;
struct fd_es_set esSet = { 0,{0},{NULL} };

bool server::sendPok(SOCKET socketClient, player p)//���;�����Ϣ
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

bool server::acceptEvent(int clientIndex)//��������
{
	//��������
	SOCKET socketClient = accept(esSet.sockall[clientIndex], NULL, NULL);
	if (INVALID_SOCKET == socketClient)	return false;

	WSAEVENT wsaClientEvent = WSACreateEvent();//�����¼�����
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

	//װ���ṹ��
	esSet.sockall[esSet.count] = socketClient;
	esSet.eventall[esSet.count] = wsaClientEvent;
	printf("�û�%d�����ӷ�����\n", esSet.count);
	esSet.count++;

	return true;
}

bool server::readEvent(int clientIndex)//��ȡ�յ������ݰ�
{
	char strRecv[1500] = { 0 };
	if (SOCKET_ERROR == recv(esSet.sockall[clientIndex], strRecv, 1499, 0))
	{
		int a = WSAGetLastError();
		printf("recv fail,error code:%d\n", a);
		return false;
	}//����������Ϣ

	printf("recv data:%s\n", strRecv);

		int choice=-1;
		stringstream ss;
		string Name,Password;

		ss << strRecv;
		ss >> choice;
		
		if (choice == CHOICE_LOGIN)//��¼
		{
			ss>> Name>>Password;
			player p = player(Name);//�������ݰ���Ϣ����player����
			if (p.login(Name,Password, p,clientIndex))
			{
				if (!sendPok(esSet.sockall[clientIndex], p))//�����û��ľ�����Ϣ
				{
					cout << "������Ϣ����ʧ��" << endl;
					return false;
				}
				else
				{
					cout << "��¼�ɹ�" << endl;
					return true;
				}
			}
			else
			{
				if (!SOCKET_ERROR == send(esSet.sockall[clientIndex], "-1", strlen("-1"), 0))//����ʧ����Ϣ
				{
					cout << "��Ϣ����ʧ��" << endl;
					return false;
				}
				cout << "��¼ʧ��" << endl;
				return false;
			}
		}
		else if (choice == CHOICE_REGIST)//ע��
		{
			ss >> Name>>Password;
			player p = player(Name);//�������ݰ���Ϣ����player����
			
			if (p.regist(Name, Password,p))
			{
				if (!sendPok(esSet.sockall[clientIndex], p))//�����û��ľ�����Ϣ
				{
					cout << "������Ϣ����ʧ��" << endl;
					return false;
				}
				else
				{
					cout << "ע��ɹ�" << endl;
					return true;
				}
			}
			else
			{
				if (!SOCKET_ERROR == send(esSet.sockall[clientIndex], "-1", strlen("-1"), 0))//����ʧ����Ϣ
				{
					cout << "��Ϣ����ʧ��" << endl;
					return false;
				}
				cout << "ע��ʧ��" << endl;
				return false;
			}
		}
		else if (choice == CHOICE_CHECK)//�鿴�����û�����Ϣ
		{
			stringstream ss;
			for (vector<player>::iterator it = Players.begin(); it != Players.end()&&it->getName()!=""; it++)
			{
				ss << it->name << " " << it->pokNum<<" "<<it->Login<< endl;
				for (int i = 1; i <= 6; i++) ss << it->medal[i]<<" ";
				ss << it->winnum << " " << it->totalnum << " ";
				for (vector<Pokemon*>::iterator itt = it->poks.begin(); itt != it->poks.end(); itt++)
				{
					ss << (*itt)->getSeq() << " " << (*itt)->getLv() << " " << (*itt)->exp << endl;//д�뾫����Ϣ
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
			cout << "�û�" << clientIndex << "�ѵǳ�" << endl;
			return true;
		}
		else if (choice == CHOICE_UPDATE)
		{
		/*����ԭ����ҵ�������Ϣ*/
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

		/*����*/
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

				ss >> pokSeq >> lv >> exp;//���ζ�ȡ�����š��ȼ�������ֵ

				Pokemon* pok = nullptr;
				pok = pok->newPok(pokSeq);//��������
				pok->initPok(lv, exp);//�������ʼ��Ϊ���֮ǰ�������״̬
				pl->poks.push_back(pok);
			}

			/*��д�����ļ�*/
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

			/*����Players*/
			Players.clear();
			while (!fs1.eof())
				readPlayer(fs1);//��ȡ�ļ��������Ϣ
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

void server::closeEvent(WSANETWORKEVENTS NetworkEvents,int i)//�ͻ������ߴ���
{
	printf("�û�%d����\n",i);
	printf("client force out:%d\n", NetworkEvents.iErrorCode[FD_CLOSE_BIT]);
	//�������߿ͻ��ˡ��׽��֡��¼�
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

bool server::connectClient()//���з�����
{
	WORD wdVersion = MAKEWORD(2, 2);
	WSADATA wdSockMsg;
	int nRes = WSAStartup(wdVersion, &wdSockMsg);

	if (0 != nRes)
	{
		switch (nRes)
		{
		case WSASYSNOTREADY://ϵͳ�������⣬�������ԣ����ws2_32���Ƿ����
			cout << "�������ԣ����߼�������" << endl; break;
		case WSAVERNOTSUPPORTED://�汾�ⲻ֧��
			cout << "����������" << endl; break;
		case WSAEINPROGRESS://�����ڼ��������
			cout << "����������" << endl; break;
		case WSAEPROCLIM://Windows Socket������Ӧ�ó�������
			cout << "��ص�һЩ����Ҫ�����" << endl; break;
		}
		return 0;
	}

	if (2 != HIBYTE(wdSockMsg.wVersion) || 2 != LOBYTE(wdSockMsg.wVersion))
	{
		cout << "�汾����" << endl;
		//�汾���ԣ��ر������
		WSACleanup();
		return 0;
	}

	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//����������socket
	if (INVALID_SOCKET == socketServer)
	{
		int a = WSAGetLastError();
		cout << "����������socket����������:" << a << endl;
		//���������
		WSACleanup();
		return 0;
	}

	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (SOCKET_ERROR == bind(socketServer, (const struct sockaddr *)&si, sizeof(si)))
	{
		int a = WSAGetLastError();
		cout << "�󶨳���������:" << a<<endl;
		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN))
	{
		int a = WSAGetLastError();
		cout << "��������������:" << a << endl;
		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	WSAEVENT eventServer = WSACreateEvent();//�����¼�
	if (WSA_INVALID_EVENT == eventServer)
	{
		int a = WSAGetLastError();
		cout << "�����������¼�����������:" << a << endl;
		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	if (SOCKET_ERROR == WSAEventSelect(socketServer, eventServer, FD_ACCEPT))
	{
		int a = WSAGetLastError();
		cout << "������socket�������������:" << a << endl;
		WSACloseEvent(eventServer);//�ͷž��
		closesocket(socketServer);
		WSACleanup();
		return 0;
	}

	esSet.eventall[esSet.count] = eventServer;
	esSet.sockall[esSet.count] = socketServer;
	esSet.count++;
	ifstream fs("playerPok.txt", ifstream::in);
	while (!fs.eof())
		readPlayer(fs);//��ȡ�ļ��������Ϣ
	fs.close();

	while (1)
	{
		for (int i = 0; i < esSet.count; i++)
		{
			DWORD nRes = WSAWaitForMultipleEvents(1, &esSet.eventall[i], FALSE, 50, FALSE);
			if (WSA_WAIT_FAILED == nRes)
			{
				int a = WSAGetLastError();
				printf("�ȴ��¼�����������%d\n", a);
				continue;
			}
			if (WSA_WAIT_TIMEOUT == nRes) continue;

			WSANETWORKEVENTS NetworkEvents;
			if (SOCKET_ERROR == WSAEnumNetworkEvents(esSet.sockall[i], esSet.eventall[i], &NetworkEvents))
			{
				int a = WSAGetLastError();
				printf("�õ��¼�����������%d\n", a);
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
	WSACloseEvent(eventServer);//�ͷž��
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