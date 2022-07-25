#pragma once

#include <QWidget>
#include "ui_playerWidget.h"
#include"pokemonClient.h"
class playerWidget : public QWidget
{
	Q_OBJECT

public:
	playerWidget(player *P,QWidget *parent = Q_NULLPTR);//构造大厅界面
	~playerWidget();//析构
	player *client;//玩家信息

private:
	Ui::playerWidget ui;//大厅界面
	
private slots:
	void returnSlot();//点击登出按钮
	void myPokSlot();//点击我的精灵
	void upgradeSlot();//点击升级赛
	void duelSlot();//点击决斗赛
	void playersSlot();//点击其他玩家
};
