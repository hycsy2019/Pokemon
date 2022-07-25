#ifndef _POKEMON_H_
#define _POKEMON_H_

#include<iostream>
#include<iomanip>
#include<string>
#include<utility>
#include<vector>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<WinSock2.h>
#include<Ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define UPGTYPE (float)1.2//主属性加成更高
#define UPG (float)1.1//其余属性升级加成

#define POKNUM 16//精灵数量

#define CHOICE_LOGIN 0//登录选项
#define CHOICE_REGIST 1//注册选项
#define CHOICE_CHECK 2//查看所有用户的信息
#define CHOICE_LOGOUT 3//登出
#define CHOICE_UPDATE 4//更新玩家战斗后的状态

enum Type { ATK, HP, DF, ATKT };//精灵种类：力量型、肉盾型、防御型、敏捷型

typedef struct attack ATTACK;

class Pokemon {
protected:
	enum Type { ATK, HP, DF, ATKT };//精灵种类：力量型、肉盾型、防御型、敏捷型
	int pokSeq;//精灵编号
	Type type;//种类
	string name;//名字
	int lv = 1;//等级
	float atk;//攻击力
	float df;//防御力
	float atkt;//攻击间隔
	float hp;//生命值
public:
	float exp = 0.0;//经验值
	void initPok(int Lv, float Exp)//根据精灵等级和经验值初始化精灵
	{
		if (this != nullptr)
		{
			while (lv < Lv) this->upgrade(0);
			exp = Exp;
		}
	}
	
	float getDf() { return df; }//返回防御力值
	float getHp() { return hp; }//返回生命上限
	int getLv() { return lv; }//返回等级
	float getAtkt() { return atkt; }//返回攻击间隔
	string getName() { return name; };//返回名字
	int getSeq() { return pokSeq; }//返回精灵编号

	void printProperty(Pokemon pok);//打印精灵属性
	void upgrade(float newExp);//升一级
	Pokemon* newPok(int Pok);//根据编号返回一个创建的精灵指针
	virtual ATTACK attack(Pokemon& pok, int choice);//攻击方法
	void deletePok(Pokemon* pok) { delete pok; }//删除已经创建的精灵
};

class player
{
private:
	friend class server;//服务器友元，便于读取
	string name;//用户名
	string password;//密码
	int pokNum;//拥有的精灵数量
	int winnum=0;//赢的场次
	int totalnum=0;//总场次
	vector<Pokemon*> poks;//拥有的精灵详细信息
public:
	bool medal[7] = { 0 };//拥有的勋章
	int Login=0;//是否登录
	int clientSeq=-1;//对应的客户序号
	player(string Name) { name = Name; };//通过用户名构造
	void assignPok();//随机分配三个一级精灵
	bool regist(string Name, string Password,player& p);//注册
	bool login(string Name, string Password,player& p, int Seq);//登录
	void friend readPlayer(ifstream& fs);//从文件流中读取一个玩家数据
	void writePlayer(ofstream& fs);//写一个玩家数据
	void printPlayerInfo();//打印玩家信息

	string getName() { return name; }//得到用户名
};

struct fd_es_set
{
	unsigned short count;//端口总数
	SOCKET sockall[100];//存储socket
	WSAEVENT eventall[100];//存储事件
};

class server
{
private:
	struct sockaddr_in si;//server地址
public:
	bool connectClient();//运行服务器
	bool acceptEvent(int clientIndex);//建立连接
	bool readEvent(int clientIndex);//读取收到的数据包
	void closeEvent(WSANETWORKEVENTS NetworkEvents, int i);//客户端下线处理
	bool sendPok(SOCKET socketClient, player p);//发送玩家的精灵信息
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

void readPlayer(ifstream& fs);//读一个玩家信息

#endif
