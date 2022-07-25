#pragma once

#include <QWidget>
#include <QtWidgets/QLabel>
#include<qstring.h> 
#include "ui_myPok.h"
#include"pokemonClient.h"

#ifdef WIN32 
#pragma execution_character_set("utf-8") 
#endif
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8") 
#endif

class GUImyPok : public QWidget
{
	Q_OBJECT

public:
	GUImyPok(player *p, QWidget *parent = Q_NULLPTR);//构造精灵背包窗口
	~GUImyPok();//析构
	void setupPoksWidget(QWidget *w, player *p);//构造精灵背包窗口

private:
	Ui::GUImyPok ui;//精灵背包窗口
	QLabel *pokImgLabel[16];//精灵图片
	QLabel *pokInfoLabel[16];//精灵详情
};
