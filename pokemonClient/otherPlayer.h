#pragma once

#include <QWidget>
#include "ui_otherPlayer.h"
#include<qlabel.h>
#include"pokemonClient.h"

class otherPlayer : public QWidget
{
	Q_OBJECT

public:
	otherPlayer(player p,QWidget *parent = Q_NULLPTR);//构造其他玩家信息窗口
	~otherPlayer();//析构

private:
	Ui::otherPlayer ui;//其他玩家信息窗口
	QLabel *pokImgLabel[16];//精灵图片
	QLabel *pokLevLabel[16];//精灵等级
};
