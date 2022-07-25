#include "playerWidget.h"
#include"pokemonClient.h"
#include"pokemonClientGUI.h"
#include"GUImyPok.h"
#include"otherPlayer.h"
#include"GUIfight.h"
#include <QtMultimedia/QMediaPlayer>

playerWidget *playerW;//大厅界面
extern pcg *loginW;//登录界面
extern playerWidget *playerW;//游戏主界面
extern GUImyPok *mypokW;//精灵背包
extern otherPlayer *otherplayerW;//其他玩家信息
extern GUIfight *fightW;//战斗界面
extern SOCKET socketServer;//服务器socket
extern QMediaPlayer *bgm;//背景音乐
extern QString runPath;//可执行文件绝对路径

playerWidget::playerWidget(player *P,QWidget *parent)//构造大厅界面
	: QWidget(parent)
{
	client = P;
	ui.setupUi(this);

	/*向服务器询问当前在线玩家*/
	if (SOCKET_ERROR == send(socketServer, "2", 1, 0))//发送选项
	{
		int a = WSAGetLastError();
		cout << "发送出错，错误码：" << a << endl;
	}
	char recvBuf[1500] = { '\0' };
	int res = recv(socketServer, recvBuf, 1499, 0);
	readPlayers(recvBuf);

	/*打印玩家列表*/
	int y = 0;
	for (vector<player>::iterator it = Players.begin(); it != Players.end() && it->getName() != ""; it++, y += 20)
	{
		QPushButton *playerButton;
		playerButton = new QPushButton(ui.playerListWidget);
		playerButton->setGeometry(QRect(80, 60 + y, 400, 30));
		QFont font;
		font.setPointSize(9);
		if (it->Login) playerButton->setStyleSheet("color:green;background-color:transparent;");
		else playerButton->setStyleSheet("color:grey;background-color:transparent;");
		playerButton->setFont(font);
		playerButton->setCursor(QCursor(Qt::PointingHandCursor));
		QString playerName;
		stringstream s;
		s << it->getName();
		playerName = QString::fromLocal8Bit(s.str().c_str());
		playerButton->setText(playerName);
		QObject::connect(playerButton, SIGNAL(clicked()),this, SLOT(playersSlot()));
		ui.playerListScroll->setGeometry(QRect(750, 0, 521 + y, 251));
	}
	ui.playerListScroll->setWidget(ui.playerListWidget);

	/*徽章显示*/
	for (int i = 1; i <= 6; i++)
	{
		if (!client->medal[i])
		{
			switch (i)
			{
			case 1:
				ui.pokcopper->hide();
			case 2:
				ui.poksilver->hide();
			case 3:
				ui.pokgold->hide();
			case 4:
				ui.levelcopper->hide();
			case 5:
				ui.levelsilver->hide();
			case 6:
				ui.levelgold->hide();
			}
		}
	}
}

playerWidget::~playerWidget()//析构
{
}

void playerWidget::returnSlot()//点击登出按钮
{
	/*登出*/
	if (SOCKET_ERROR == send(socketServer, "3", 1, 0))//发送选项
	{
		int a = WSAGetLastError();
		return;
	}

	for (vector<player>::iterator it = Players.begin(); it != Players.end(); it++)
	{
		if (client->getName() == it->getName())
		{
			it->Login = 0;
		}
	}
	/*返回登录界面*/
	bgm->setMedia(QUrl::fromLocalFile(runPath + "/music/pikaqiu.mp3"));
	this->hide();
	loginW = new pcg;
	loginW->show();
	delete playerW;
}

void playerWidget::myPokSlot()//点击我的精灵
{
	/*显示精灵窗口*/
	mypokW =new GUImyPok(client);
	mypokW->show();
}

void playerWidget::playersSlot()//点击其他玩家
{
	/*显示其他玩家拥有的精灵*/
	player p("");
	for (vector<player>::iterator it = Players.begin(); it != Players.end() && it->getName() != ""; it++)
	{
		if (((QPushButton*)sender())->text().toStdString() == it->getName())
			p = *it;
	}
	otherplayerW =new otherPlayer(p);
	otherplayerW->show();
}

void playerWidget::upgradeSlot()//点击升级赛
{
	/*升级赛*/
	fightW =new GUIfight(client, 0);
	this->hide();
	fightW->show();
	delete playerW;
}

void playerWidget::duelSlot()//点击决斗赛
{
	/*决斗赛*/
	fightW = new GUIfight(client, 1);
	this->hide();
	fightW->show();
	delete playerW;
}

//int main(int argc, char **argv)
//{
//	QApplication app(argc, argv);
//	player p1("test11111");
//	player p2("test22");
//	p1.Login = 0;
//	p2.Login = 1;
//	p2.medal[1] = 1;
//	p2.medal[2] = 1;
//	Pokemon *pok1 = nullptr; 
//	pok1=pok1->newPok(4);
//	Pokemon *pok2 = nullptr; 
//	pok2=pok2->newPok(2);
//	Pokemon *pok3 = nullptr;
//	pok3 = pok3->newPok(10);
//	p1.poks.push_back(pok1);
//	p1.poks.push_back(pok2);
//	p1.poks.push_back(pok3);
//	p2.poks.push_back(pok1);
//	p2.poks.push_back(pok2);
//	Players.push_back(p1);
//	Players.push_back(p2);
//	playerWidget w(&p2);
//	w.show();
//	return app.exec();
//}