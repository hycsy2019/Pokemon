#pragma once

#include <QWidget>
#include "ui_victory.h"
#include"pokemonClient.h"
class victory : public QWidget
{
	Q_OBJECT

public:
	victory(Pokemon *winPok, Pokemon *losePok,player *P,float remainhp,bool type,QWidget *parent = Q_NULLPTR);//������type=0,������type=1.
	~victory();//����

private:
	Ui::victory ui;//ʤ������
	player *pp;//ʤ�������

private slots:
	void continueSlot();//���������Ϸ��ť
};
