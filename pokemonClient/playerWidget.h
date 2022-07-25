#pragma once

#include <QWidget>
#include "ui_playerWidget.h"
#include"pokemonClient.h"
class playerWidget : public QWidget
{
	Q_OBJECT

public:
	playerWidget(player *P,QWidget *parent = Q_NULLPTR);//�����������
	~playerWidget();//����
	player *client;//�����Ϣ

private:
	Ui::playerWidget ui;//��������
	
private slots:
	void returnSlot();//����ǳ���ť
	void myPokSlot();//����ҵľ���
	void upgradeSlot();//���������
	void duelSlot();//���������
	void playersSlot();//����������
};
