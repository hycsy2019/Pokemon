#pragma once

#include <QWidget>
#include<cstdlib>
#include<Qtime>
#include "ui_fight.h"
#include"pokemonClient.h"

#define PCPOKNUM 6

class GUIfight : public QWidget
{
	Q_OBJECT

public:
	GUIfight(player *Pl, bool fighttype, QWidget *parent = Q_NULLPTR);//构造战斗界面
	~GUIfight();//析构
	void updatePlayer();//服务器更新玩家数据

private:
	Ui::GUIfight ui;
	player *P;//玩家
	vector<Pokemon*> playerPoks;//玩家的所有精灵
	vector<Pokemon*> pcPoks;//所有对手精灵
	vector<Pokemon*> producePoks();//生成精灵
	vector<Pokemon*>::iterator nowPlayerPok;//当前玩家的精灵
	vector<Pokemon*>::iterator nowPcPok;//当前系统的精灵
	Pokemon *fplayerpok = nullptr;//玩家选择的出战的精灵
	Pokemon *fpcpok = nullptr;//玩家选择的对手精灵
	bool fightType;//比赛类型,0为升级赛，1为决斗赛
	void putPokImg(bool type, vector<Pokemon*>::iterator it);//精灵贴图，type=0为玩家精灵，type=1为系统精灵
	void aniFight(Pokemon *playerPok, Pokemon *pcPok);//战斗动画
	float GUIround(vector< pair<ATTACK, ATTACK>>::iterator it, QLabel *firstAttack, QLabel *secondAttack,
		QLabel *firstInfo, QLabel *secondInfo, QProgressBar *firsthp, QProgressBar *secondhp, float hp1, float hp2);//每回合的攻击、血量,返回胜利一方的剩余血量
	void sleep(unsigned int msec);//动画延时
	void updateMedals();//勋章更新

private slots:
	void playerLastSlot();//查看玩家的上一个精灵
	void playerNextSlot();//查看玩家的下一个精灵
	void pcLastSlot();//查看系统的上一个精灵
	void pcNextSlot();//查看系统的下一个精灵
	void okplayerSlot();//出战精灵选定
	void okpcSlot();//对手精灵选定

public slots:
	void returnSlot();//返回大厅
};
