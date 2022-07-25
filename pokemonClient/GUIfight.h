#pragma once

#include <QWidget>
#include<cstdlib>
#include<Qtime>
#include "ui_fight.h"
#include"pokemonClient.h"

#define PCPOKNUM 6

class GUIfight : public QWidget
{
	Q_OBJECT

public:
	GUIfight(player *Pl, bool fighttype, QWidget *parent = Q_NULLPTR);//����ս������
	~GUIfight();//����
	void updatePlayer();//�����������������

private:
	Ui::GUIfight ui;
	player *P;//���
	vector<Pokemon*> playerPoks;//��ҵ����о���
	vector<Pokemon*> pcPoks;//���ж��־���
	vector<Pokemon*> producePoks();//���ɾ���
	vector<Pokemon*>::iterator nowPlayerPok;//��ǰ��ҵľ���
	vector<Pokemon*>::iterator nowPcPok;//��ǰϵͳ�ľ���
	Pokemon *fplayerpok = nullptr;//���ѡ��ĳ�ս�ľ���
	Pokemon *fpcpok = nullptr;//���ѡ��Ķ��־���
	bool fightType;//��������,0Ϊ��������1Ϊ������
	void putPokImg(bool type, vector<Pokemon*>::iterator it);//������ͼ��type=0Ϊ��Ҿ��飬type=1Ϊϵͳ����
	void aniFight(Pokemon *playerPok, Pokemon *pcPok);//ս������
	float GUIround(vector< pair<ATTACK, ATTACK>>::iterator it, QLabel *firstAttack, QLabel *secondAttack,
		QLabel *firstInfo, QLabel *secondInfo, QProgressBar *firsthp, QProgressBar *secondhp, float hp1, float hp2);//ÿ�غϵĹ�����Ѫ��,����ʤ��һ����ʣ��Ѫ��
	void sleep(unsigned int msec);//������ʱ
	void updateMedals();//ѫ�¸���

private slots:
	void playerLastSlot();//�鿴��ҵ���һ������
	void playerNextSlot();//�鿴��ҵ���һ������
	void pcLastSlot();//�鿴ϵͳ����һ������
	void pcNextSlot();//�鿴ϵͳ����һ������
	void okplayerSlot();//��ս����ѡ��
	void okpcSlot();//���־���ѡ��

public slots:
	void returnSlot();//���ش���
};
