#pragma once

#include <QWidget>
#include "ui_victory.h"
#include"pokemonClient.h"
class victory : public QWidget
{
	Q_OBJECT

public:
	victory(Pokemon *winPok, Pokemon *losePok,player *P,float remainhp,bool type,QWidget *parent = Q_NULLPTR);//升级赛type=0,决斗赛type=1.
	~victory();//析构

private:
	Ui::victory ui;//胜利界面
	player *pp;//胜利的玩家

private slots:
	void continueSlot();//点击继续游戏按钮
};
