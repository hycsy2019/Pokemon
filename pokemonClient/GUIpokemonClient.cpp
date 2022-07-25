#include "pokemonClientGUI.h"
#include"pokemonClient.h"
#include"playerWidget.h"
#include <QtMultimedia/QMediaPlayer>
#include<qdir.h>

SOCKET socketServer;//������socket
pcg *loginW;//��¼����
QMediaPlayer *bgm;//��������
extern QString runPath;//��ִ���ļ�����·��

extern playerWidget *playerW;//��Ϸ������

pcg::pcg(QWidget *parent)//�����¼����
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

void pcg::GUIenter(int choice)//��¼��ע��
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
		/*��ʾ��¼��ע��ʧ����ʾ*/
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
			/*������ҽ���*/
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

