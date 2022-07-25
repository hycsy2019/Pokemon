#include "GUIfight.h"
#include"pokemonClient.h"
#include"victory.h"
#include"lose.h"
#include"playerWidget.h"
#include"pokemonClientGUI.h"
#include<string.h>
#include <QtMultimedia/QMediaPlayer>

GUIfight *fightW;//战斗界面
extern playerWidget *playerW;//游戏主界面
extern victory *victoryW;//胜利窗口
extern lose *loseW;//失败窗口
extern pcg *loginW;//登录界面
extern SOCKET socketServer;//服务器socket
extern QMediaPlayer *bgm;//背景音乐
extern QString runPath;//可执行文件绝对路径

vector<Pokemon*> GUIfight:: producePoks()
{
	/*求得玩家精灵的平均等级*/
	int levsum = 0,num=0;
	for (vector<Pokemon*>::iterator it = playerPoks.begin(); it != playerPoks.end(); it++)
	{
		levsum += (*it)->getLv();
		num++;
	}
	int avelev = levsum / num;

	/*升级赛随机生成等级接近的精灵，决斗赛精灵完全随机*/
	vector<Pokemon*> pcpoks;
	srand((int)time(0));
	if (fightType == 0)
	{
		avelev--;
		for (int i = 1; i <= PCPOKNUM; i++)
		{
			int pokSeq = (rand() % POKNUM) + 1;
			Pokemon* pok = nullptr;
			pok = pok->newPok(pokSeq);
			int poklev = (rand() % 4) + avelev - 2;
			while (pok->getLv() <= poklev) pok->upgrade(0);
			pcpoks.push_back(pok);
		}
	}
	else
	{
		for (int i = 1; i <= PCPOKNUM; i++)
		{
			int pokSeq = (rand() % POKNUM) + 1;
			Pokemon* pok = nullptr;
			pok = pok->newPok(pokSeq);
			int poklev = rand() % 15 + 1;
			while (pok->getLv() <= poklev) pok->upgrade(0);
			pcpoks.push_back(pok);
		}
	}

	return pcpoks;
}

void GUIfight::putPokImg(bool type, vector<Pokemon*>::iterator it)//精灵贴图，type=0为玩家精灵，type=1为系统精灵
{
	QString filename;
	filename = ":/pokpic/" + filename.fromStdString((*it)->getLetterName()) + ".png";
	QString lv;
	stringstream s;
	s << (*it)->getLv();
	lv = "Lv." + QString::fromLocal8Bit(s.str().c_str());

	if (type == 0)
	{
		QPixmap *pixm = new QPixmap(filename);
		pixm->scaled(ui.playerPokLabel->size(), Qt::KeepAspectRatio);
		ui.playerPokLabel->setScaledContents(true);
		ui.playerPokLabel->setPixmap(*pixm);
		ui.playerlv->setText(lv);
		ui.playerhp->setMaximum((*it)->getHp());
		ui.playerhp->setValue((*it)->getHp());
	}

	else
	{
		QPixmap *pixm = new QPixmap(filename);
		pixm->scaled(ui.playerPokLabel->size(), Qt::KeepAspectRatio);
		ui.pcPokLabel->setScaledContents(true);
		ui.pcPokLabel->setPixmap(*pixm);
		ui.pclv->setText(lv);
		ui.pchp->setMaximum((*it)->getHp());
		ui.pchp->setValue((*it)->getHp());
	}

	this->update();
}

GUIfight::GUIfight(player *Pl, bool fighttype, QWidget *parent)//构造战斗界面
	:QWidget(parent)
{
	bgm->setMedia(QUrl::fromLocalFile(runPath+"/music/fight.mp3"));
	bgm->setVolume(40);
	bgm->play();
	ui.setupUi(this);
	ui.setupUi(this);
	setFixedSize(this->width(), this->height());

	playerPoks = Pl->poks;
	P = Pl;
	fightType = fighttype;

	/*玩家精灵贴图*/
	putPokImg(0, playerPoks.begin());
	nowPlayerPok = playerPoks.begin();
	QObject::connect(ui.playerlastPok, SIGNAL(clicked()), this, SLOT(playerLastSlot()));
	QObject::connect(ui.playernextPok, SIGNAL(clicked()), this, SLOT(playerNextSlot()));

	/*系统根据比赛类型生成等级较为接近的对战精灵*/
	pcPoks = producePoks();

	/*对手精灵贴图*/
	putPokImg(1, pcPoks.begin());
	nowPcPok = pcPoks.begin();
	QObject::connect(ui.pclastPok, SIGNAL(clicked()), this, SLOT(pcLastSlot()));
	QObject::connect(ui.pcnextPok, SIGNAL(clicked()), this, SLOT(pcNextSlot()));
}

void GUIfight::sleep(unsigned int msec)//动画延时
{
	QTime reachTime = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < reachTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

float GUIfight::GUIround(vector< pair<ATTACK, ATTACK>>::iterator it,QLabel *firstAttack,QLabel *secondAttack, 
	QLabel *firstInfo, QLabel *secondInfo,QProgressBar *firsthp,QProgressBar *secondhp,float hp1,float hp2)//每回合的攻击、血量,返回胜利一方的剩余血量
{
	if (it->first.hpOppo != 0.0)//对方血量未达到0，继续攻击
	{
		firstAttack->setText(QString::fromLocal8Bit(it->first.name.c_str()));
		if (it->first.dodge)
		{
			secondAttack->setText(QString::fromLocal8Bit("闪避"));
			secondAttack->show();
		}
		if (it->first.strike)
		{
			firstInfo->setText(QString::fromLocal8Bit("暴击"));
			firstInfo->show();
		}
		stringstream s1;
		s1.setf(ios::fixed);
		s1 <<"-"<< setprecision(1)<<it->first.damage;
		secondInfo->setText(s1.str().c_str());
		hp2 = it->first.hpOppo;
		firstAttack->show();
		secondInfo->show();
		this->update();
		sleep(1000);

		firstAttack->hide();
		secondAttack->hide();
		firstInfo->hide();
		secondInfo->hide();
		secondhp->setValue(it->first.hpOppo);
		secondhp->show();
		this->update();
		sleep(200);

		secondAttack->setText(QString::fromLocal8Bit(it->second.name.c_str()));
		if (it->second.dodge)
		{
			firstAttack->setText(QString::fromLocal8Bit("闪避"));
			firstAttack->show();
		}
		if (it->second.strike)
		{
			secondInfo->setText(QString::fromLocal8Bit("暴击"));
			secondInfo->show();
		}
		stringstream s2;
		s2.setf(ios::fixed);
		s2 << "-" << setprecision(1)<<it->second.damage;
		firstInfo->setText(s2.str().c_str());
		firstInfo->show();
		secondAttack->show();
		hp1 = it->second.hpOppo;
		this->update();
		sleep(1000);
	
		firstAttack->hide();
		secondAttack->hide();
		firstInfo->hide();
		secondInfo->hide();
		firsthp->setValue(it->second.hpOppo);
		firsthp->show();
		this->update();
		sleep(200);

		if (hp1 >= 0 && hp1 <= 0)  
			return hp2;
		else return -1;
	}
	else
	{
		firstAttack->setText(QString::fromLocal8Bit(it->first.name.c_str()));
		if (it->first.dodge)
		{
			secondAttack->setText(QString::fromLocal8Bit("闪避"));
			secondAttack->show();
		}
		if (it->first.strike)
		{
			firstInfo->setText(QString::fromLocal8Bit("暴击"));
			firstInfo->show();
		}
		stringstream s1;
		s1.setf(ios::fixed);
		s1 << "-" << setprecision(1) << it->first.damage;
		secondInfo->setText(s1.str().c_str());
		hp2 = it->first.hpOppo;
		firstAttack->show();
		secondInfo->show();
		this->update();
		sleep(1000);


		firstAttack->hide();
		secondAttack->hide();
		firstInfo->hide();
		secondInfo->hide();
		secondhp->setValue(it->first.hpOppo);
		secondhp->show();
		this->update();
		
		return hp1;
	}
}

void GUIfight::updateMedals()//勋章更新
{
	for(int i=1;i<=6;i++) P->medal[i]=false;

	if (P->pokNum >= 5)
	{
		P->medal[1] = true;
		if (P->pokNum >= 10)
		{
			P->medal[2] = true;
			if (P->pokNum >= 15)
				P->medal[3] = true;
		}
	}
	
	int num=0;
	for (vector<Pokemon*>::iterator it = P->poks.begin(); it != P->poks.end(); it++)
	{
		if ((*it)->getLv() == 15) num++;
	}

	if (num >= 5)
	{
		P->medal[4] = true;
		if (num >= 10)
		{
			P->medal[5] = true;
			if (num >= 15)
				P->medal[6] = true;
		}
	}

}

void GUIfight::updatePlayer()//服务器更新玩家数据
{
	stringstream sendss;
	char sendBuf[1500] = { '\0' };
	sendss << 4 << " ";
	sendss << P->getName() << " " << P->getPassword() << " ";
	sendss << P->pokNum << " ";
	for (int i = 1; i <= 6; i++) sendss << P->medal[i] << " ";
	sendss << P->winnum <<" "<< P->totalnum<<" ";
	for (vector<Pokemon*>::iterator it =P->poks.begin(); it != P->poks.end(); it++)
	{
		sendss << (*it)->getSeq() << " " << (*it)->getLv() << " " << (*it)->exp << " ";
	}
	sendss << "\0";
	memcpy(sendBuf, sendss.str().c_str(), 1500);
	if (SOCKET_ERROR == send(socketServer, sendBuf, strlen(sendBuf), 0))
	{
		int a = WSAGetLastError();
	}

	for (vector<player>::iterator it = Players.begin(); it != Players.end() && it->getName() != ""; it++)
	{
		if (P->getName() == (*it).getName())
			(*it) = (*P);
	}
}

void GUIfight::aniFight(Pokemon *playerPok, Pokemon *pcPok)//战斗动画
{
	//生成对战过程
	Fight F = Fight(playerPok, pcPok);
	Pokemon* winPok = F.wholeFight();
	F.printRounds();
	QFont font5;
	font5.setFamily(QString::fromUtf8("\346\200\235\346\272\220\351\273\221\344\275\223"));
	font5.setPointSize(30);
	font5.setBold(true);
	font5.setItalic(false);
	font5.setWeight(75);
	ui.chuzhan->setFont(font5);
	ui.chuzhan->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
	ui.duishou->setFont(font5);
	ui.duishou->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
	ui.exit->hide();

	//随机先手
	ui.VSlabel->setFont(font5);
	stringstream s;
	float remainHP;
	if (F.first == 1)
	{
		s << "随机先手:\n" << playerPok->getName();
		ui.VSlabel->setText(QString::fromLocal8Bit(s.str().c_str()));
		ui.VSlabel->show();
		this->update();
		sleep(1000);
		ui.VSlabel->hide();

		//输出对战过程动画
		for (vector< pair<ATTACK, ATTACK>>::iterator it = F.rounds.begin();
			it != F.rounds.end(); it++)
		{
			remainHP=GUIround(it, ui.playerAttack, ui.pcAttack, ui.chuzhan, ui.duishou, ui.playerhp, ui.pchp, playerPok->getHp(), pcPok->getHp());
		}
	}
	else
	{
		s << "随机先手:\n" << pcPok->getName() << endl;
		ui.VSlabel->setText(QString::fromLocal8Bit(s.str().c_str()));
		ui.VSlabel->show();
		this->update();
		sleep(1000);
		ui.VSlabel->hide();

		//输出对战过程动画
		for (vector< pair<ATTACK, ATTACK>>::iterator it = F.rounds.begin();
			it != F.rounds.end(); it++)
		{
			remainHP=GUIround(it, ui.pcAttack, ui.playerAttack, ui.duishou, ui.chuzhan, ui.pchp, ui.playerhp, pcPok->getHp(), playerPok->getHp());
		}
	}

	/*输出结算窗口*/
	if (winPok == playerPok)
	{
		victoryW = new victory(playerPok, pcPok, P, remainHP, fightType);
		victoryW->show();
		P->winnum++;
		P->totalnum++;
	}
	else
	{
		loseW = new lose(playerPok, P, fightType, remainHP);
		loseW->show();
		P->totalnum++;
	}

	/*进行勋章的更新*/
	updateMedals();
}

void GUIfight::playerLastSlot()//查看玩家的上一个精灵
{
	if (nowPlayerPok != playerPoks.begin())
	{
		nowPlayerPok--;
		putPokImg(0, nowPlayerPok);
	}
}

void GUIfight::playerNextSlot()//查看玩家的下一个精灵
{
	if (nowPlayerPok+1 != playerPoks.end())
	{
		nowPlayerPok++;
		putPokImg(0, nowPlayerPok);
	}
}

void GUIfight::pcLastSlot()//查看系统的上一个精灵
{
	if (nowPcPok != pcPoks.begin())
	{
		nowPcPok--;
		putPokImg(1, nowPcPok);
	}
}

void GUIfight::pcNextSlot()//查看系统的下一个精灵
{
	if (nowPcPok+1 != pcPoks.end())
	{
		nowPcPok++;
		putPokImg(1, nowPcPok);
	}
}

GUIfight::~GUIfight()//析构
{
}

void GUIfight::okplayerSlot()//出战精灵选定
{
	fplayerpok = *nowPlayerPok;
	ui.playerhp->setMaximum((fplayerpok)->getHp());
	ui.playerhp->setValue(fplayerpok->getHp());
	if (fplayerpok != nullptr&&fpcpok != nullptr)
		aniFight(fplayerpok, fpcpok);
}

void GUIfight::okpcSlot()//对手精灵选定
{
	fpcpok = *nowPcPok;
	ui.pchp->setMaximum((fpcpok)->getHp());
	ui.pchp->setValue(fpcpok->getHp());
	if (fplayerpok != nullptr&&fpcpok != nullptr)
		aniFight(fplayerpok, fpcpok);
}

void GUIfight::returnSlot()//返回大厅
{
	/*隐藏当前页面，返回上一页面*/
	bgm->setMedia(QUrl::fromLocalFile(runPath + "/music/pikaqiu.mp3"));
	bgm->setVolume(50);
	bgm->play();
	this->hide();
	playerW=new playerWidget(P);
	playerW->show();
	delete fightW;
}

//int main(int argc, char **argv)
//{
//	QApplication app(argc, argv);
//	player p("test11111");
//	Pokemon *pok1 = nullptr; 
//	pok1=pok1->newPok(4);
//	Pokemon *pok2 = nullptr; 
//	pok2=pok2->newPok(2);
//	Pokemon *pok3 = nullptr;
//	pok3 = pok3->newPok(16);
//	p.poks.push_back(pok1);
//	p.poks.push_back(pok2);
//	p.poks.push_back(pok3);
//	GUIfight w(&p, 0);
//	w.show();
//	return app.exec();
//}