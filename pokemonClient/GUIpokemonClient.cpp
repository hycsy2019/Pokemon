#include "pokemonClientGUI.h"
#include"pokemonClient.h"
#include"playerWidget.h"
#include <QtMultimedia/QMediaPlayer>
#include<qdir.h>

SOCKET socketServer;//服务器socket
pcg *loginW;//登录界面
QMediaPlayer *bgm;//背景音乐
extern QString runPath;//可执行文件绝对路径

extern playerWidget *playerW;//游戏主界面

pcg::pcg(QWidget *parent)//构造登录界面
    : QMainWindow(parent)
{
	bgm = new QMediaPlayer;
	bgm->setMedia(QUrl::fromLocalFile(runPath + "/music/pikaqiu.mp3"));
	bgm->setVolume(50);
	bgm->play();
   ui.setupUi(this);
   ui.loginFailLabel->hide();
   ui.registFailLabel->hide();
   ui.registSuccess->hide();
}

void pcg::GUIenter(int choice)//登录或注册
{
	string id = ui.idbox->text().toStdString();
	string Password = ui.passwordbox->text().toStdString();
	player *pp = new player(id);
	socketServer = pp->connectServer();
	int flag=0;
	flag= pp->enter(socketServer,choice, Password);
	if (id == "" || Password == "") flag = 0;

	if (flag == 0)
	{
		/*显示登录或注册失败提示*/
		if (choice == CHOICE_LOGIN)
		{
			ui.loginFailLabel->show();
			ui.registFailLabel->hide();
			ui.registSuccess->hide();
		}
		else if (choice == CHOICE_REGIST)
		{
			ui.registFailLabel->show();
			ui.loginFailLabel->hide();
			ui.registSuccess->hide();
		}
	}
	else
	{
		if (choice == CHOICE_LOGIN)
		{
			/*进入玩家界面*/
			this->hide();
			playerW = new playerWidget(pp);
			playerW->show();
			delete loginW;
		}
		else if (choice == CHOICE_REGIST)
		{
			ui.registSuccess->show();
			ui.registFailLabel->hide();
			ui.loginFailLabel->hide();
		}
	}
}

