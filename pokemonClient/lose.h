#pragma once

#include <QWidget>
#include"pokemonClient.h"
#include "ui_lose.h"

class lose : public QWidget
{
	Q_OBJECT

public:
	lose(Pokemon* losePok, player *p, bool type, float remainhp, QWidget *parent= Q_NULLPTR);//构造失败结算窗口
	~lose();//析构

private:
	Ui::lose ui;//失败界面
	player *pl;//当前玩家
	Pokemon* leftPok;//左边备选精灵
	Pokemon* centerPok;//中间备选精灵
	Pokemon* rightPok;//右边备选精灵

private slots:
	void leftSlot();//点击左边的精灵
	void centerSlot();//点击中间的精灵
	void rightSlot();//点击右边的精灵
	void fightingSlot();//点击再接再厉
};
