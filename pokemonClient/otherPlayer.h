#pragma once

#include <QWidget>
#include "ui_otherPlayer.h"
#include<qlabel.h>
#include"pokemonClient.h"

class otherPlayer : public QWidget
{
	Q_OBJECT

public:
	otherPlayer(player p,QWidget *parent = Q_NULLPTR);//�������������Ϣ����
	~otherPlayer();//����

private:
	Ui::otherPlayer ui;//���������Ϣ����
	QLabel *pokImgLabel[16];//����ͼƬ
	QLabel *pokLevLabel[16];//����ȼ�
};
