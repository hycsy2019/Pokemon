#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include<QMediaPlayer>
#include "ui_client.h"
#include"pokemonClient.h"

#define CHOICE_LOGIN 0//��¼ѡ��
#define CHOICE_REGIST 1//ע��ѡ��
#define CHOICE_CHECK 2//�鿴�����û�����Ϣ

class pcg : public QMainWindow
{
	Q_OBJECT

public:
	pcg(QWidget *parent = Q_NULLPTR);//�����¼����
	void GUIenter(int choice);//�����¼��ע��

private:
	Ui::pokBattle ui;//��¼����

private slots:
	void loginSlot() { GUIenter(CHOICE_LOGIN); }//�����¼
	void registSlot() { GUIenter(CHOICE_REGIST); }//���ע��
};



