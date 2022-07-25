#pragma once

#include <QWidget>
#include"pokemonClient.h"
#include "ui_lose.h"

class lose : public QWidget
{
	Q_OBJECT

public:
	lose(Pokemon* losePok, player *p, bool type, float remainhp, QWidget *parent= Q_NULLPTR);//����ʧ�ܽ��㴰��
	~lose();//����

private:
	Ui::lose ui;//ʧ�ܽ���
	player *pl;//��ǰ���
	Pokemon* leftPok;//��߱�ѡ����
	Pokemon* centerPok;//�м䱸ѡ����
	Pokemon* rightPok;//�ұ߱�ѡ����

private slots:
	void leftSlot();//�����ߵľ���
	void centerSlot();//����м�ľ���
	void rightSlot();//����ұߵľ���
	void fightingSlot();//����ٽ�����
};
