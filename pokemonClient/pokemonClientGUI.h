#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include<QMediaPlayer>
#include "ui_client.h"
#include"pokemonClient.h"

#define CHOICE_LOGIN 0//登录选项
#define CHOICE_REGIST 1//注册选项
#define CHOICE_CHECK 2//查看所有用户的信息

class pcg : public QMainWindow
{
	Q_OBJECT

public:
	pcg(QWidget *parent = Q_NULLPTR);//构造登录界面
	void GUIenter(int choice);//点击登录或注册

private:
	Ui::pokBattle ui;//登录界面

private slots:
	void loginSlot() { GUIenter(CHOICE_LOGIN); }//点击登录
	void registSlot() { GUIenter(CHOICE_REGIST); }//点击注册
};



