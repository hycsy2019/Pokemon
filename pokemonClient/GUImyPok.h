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
	GUImyPok(player *p, QWidget *parent = Q_NULLPTR);//���쾫�鱳������
	~GUImyPok();//����
	void setupPoksWidget(QWidget *w, player *p);//���쾫�鱳������

private:
	Ui::GUImyPok ui;//���鱳������
	QLabel *pokImgLabel[16];//����ͼƬ
	QLabel *pokInfoLabel[16];//��������
};
