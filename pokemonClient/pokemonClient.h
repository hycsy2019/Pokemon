#ifndef _POKEMONCLIENT_H_
#define _POKEMONCLIENT_H_

#include<iostream>
#include<iomanip>
#include<string>
#include<utility>
#include<vector>
#include<iomanip>
#include<fstream>
#include<iostream>
#include<WinSock2.h>
#include<Ws2tcpip.h>
#include<sstream>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

enum Type { ATK, HP, DF, ATKT };//精灵种类：力量型、肉盾型、防御型、敏捷型

typedef struct attack ATTACK;//攻击详情

class Pokemon {
protected:
	enum Type { ATK, HP, DF, ATKT };//精灵种类：力量型、肉盾型、防御型、敏捷型
	int pokSeq;//精灵编号
	Type type;//种类
	string name;//名字
	string lettername;//拼音名字
	int lv = 1;//等级
	float atk;//攻击力
	float df;//防御力
	float atkt;//攻击间隔
	float hp;//生命值
public:
	float exp = 0.0;//经验值
	void initPok(int Lv, float Exp)//根据精灵等级和经验值初始化精灵
	{
		if (this != NULL)
		{
			while (lv < Lv) this->upgrade(0);
			exp = Exp;
		}
	}
	
	float getDf() { return df; }//返回防御力值
	float getHp() { return hp; }//返回生命上限
	int getLv() { return lv; }//返回等级
	float getAtkt() { return atkt; }//返回攻击间隔
	string getLetterName() { return lettername; };//返回拼音名字
	string getName() { return name; };//返回名字
	int getSeq() { return pokSeq; }//返回精灵编号

	void printProperty(Pokemon pok, stringstream &out);//打印精灵属性
	void upgrade(float newExp);//升一级
	Pokemon* newPok(int Pok);//根据编号返回一个创建的精灵指针
	virtual ATTACK attack(Pokemon& pok, int choice);//攻击方法
	void deletePok(Pokemon* pok) { delete pok; }//删除已经创建的精灵
};

class player
{
private:
	string name,password;//用户名密码
	
public:
	int pokNum;//精灵数
	int winnum=0;//赢的场次
	int totalnum=0;//比赛总共次数
	bool medal[7];//勋章
	vector<Pokemon*> poks;//精灵
	int Login;//是否已登录
	player(string Name) { name = Name; };//构造玩家对象
	void assignPok();//随机分配三个一级精灵
	bool login(string Name,player& p);//登录
	void friend readPlayers(string s);//从字符流中读取一个玩家数据
	void printPlayerInfo(int pokInfo,stringstream &out);//打印玩家信息，可以选择是否打印精灵详情
	
	SOCKET connectServer();//连接服务器
	bool enter(SOCKET socketServer,int choice,string Password);//进入游戏，注册或登录

	string getName() { return name; }//获取用户名
	string getPassword() { return password; }//获取密码
};

class Fight
{
private:
	Pokemon *pok1, *pok2;//两只对战的精灵
	vector< pair<ATTACK, ATTACK>>  rounds;//保存两只精灵每回合的作战记录
	int first = (rand() % 2) + 1;//随机决定先手方
	friend class GUIfight;
public:
	Fight(Pokemon* pokA, Pokemon* pokB) { pok1 = pokA; pok2 = pokB; }//构造对战
	Pokemon* wholeFight();//战斗生成，返回获胜的精灵
	void round(Pokemon* pokFirst, Pokemon* pokSecond, float& hpFirst, float& hpSecond, int& strikeFir, int& strikeSec);//每个对战回合
	bool dodge(Pokemon pokAttack, Pokemon pokOppo);//pok的攻击能否被敌方闪避成功
	bool strike(int& strikeN);//能否暴击
	bool printRounds();//输出每一回合的战况
	~Fight() { rounds.clear(); }//析构
};

typedef struct attack
{
	string pok="";//出招精灵
	string name = "";//招式名称
	int seq = 0;//招式序号
	float damage = 0;//攻击伤害
	bool learn = 0;//是否习得
	float hpOppo = 0;//攻击后敌方剩余血量
	bool dodge = 0;//是否被敌方闪避
	bool strike = 0;//是否暴击
}ATTACK;

extern vector<player> Players;//存储用户信息的容器

#define UPGTYPE (float)1.2//主属性加成更高
#define UPG (float)1.1//其余属性升级加成

#define POKNUM 15//精灵数量

#endif
