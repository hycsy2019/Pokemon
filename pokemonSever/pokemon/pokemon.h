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

#define UPGTYPE (float)1.2//�����Լӳɸ���
#define UPG (float)1.1//�������������ӳ�

#define POKNUM 16//��������

#define CHOICE_LOGIN 0//��¼ѡ��
#define CHOICE_REGIST 1//ע��ѡ��
#define CHOICE_CHECK 2//�鿴�����û�����Ϣ
#define CHOICE_LOGOUT 3//�ǳ�
#define CHOICE_UPDATE 4//�������ս�����״̬

enum Type { ATK, HP, DF, ATKT };//�������ࣺ�����͡�����͡������͡�������

typedef struct attack ATTACK;

class Pokemon {
protected:
	enum Type { ATK, HP, DF, ATKT };//�������ࣺ�����͡�����͡������͡�������
	int pokSeq;//������
	Type type;//����
	string name;//����
	int lv = 1;//�ȼ�
	float atk;//������
	float df;//������
	float atkt;//�������
	float hp;//����ֵ
public:
	float exp = 0.0;//����ֵ
	void initPok(int Lv, float Exp)//���ݾ���ȼ��;���ֵ��ʼ������
	{
		if (this != nullptr)
		{
			while (lv < Lv) this->upgrade(0);
			exp = Exp;
		}
	}
	
	float getDf() { return df; }//���ط�����ֵ
	float getHp() { return hp; }//������������
	int getLv() { return lv; }//���صȼ�
	float getAtkt() { return atkt; }//���ع������
	string getName() { return name; };//��������
	int getSeq() { return pokSeq; }//���ؾ�����

	void printProperty(Pokemon pok);//��ӡ��������
	void upgrade(float newExp);//��һ��
	Pokemon* newPok(int Pok);//���ݱ�ŷ���һ�������ľ���ָ��
	virtual ATTACK attack(Pokemon& pok, int choice);//��������
	void deletePok(Pokemon* pok) { delete pok; }//ɾ���Ѿ������ľ���
};

class player
{
private:
	friend class server;//��������Ԫ�����ڶ�ȡ
	string name;//�û���
	string password;//����
	int pokNum;//ӵ�еľ�������
	int winnum=0;//Ӯ�ĳ���
	int totalnum=0;//�ܳ���
	vector<Pokemon*> poks;//ӵ�еľ�����ϸ��Ϣ
public:
	bool medal[7] = { 0 };//ӵ�е�ѫ��
	int Login=0;//�Ƿ��¼
	int clientSeq=-1;//��Ӧ�Ŀͻ����
	player(string Name) { name = Name; };//ͨ���û�������
	void assignPok();//�����������һ������
	bool regist(string Name, string Password,player& p);//ע��
	bool login(string Name, string Password,player& p, int Seq);//��¼
	void friend readPlayer(ifstream& fs);//���ļ����ж�ȡһ���������
	void writePlayer(ofstream& fs);//дһ���������
	void printPlayerInfo();//��ӡ�����Ϣ

	string getName() { return name; }//�õ��û���
};

struct fd_es_set
{
	unsigned short count;//�˿�����
	SOCKET sockall[100];//�洢socket
	WSAEVENT eventall[100];//�洢�¼�
};

class server
{
private:
	struct sockaddr_in si;//server��ַ
public:
	bool connectClient();//���з�����
	bool acceptEvent(int clientIndex);//��������
	bool readEvent(int clientIndex);//��ȡ�յ������ݰ�
	void closeEvent(WSANETWORKEVENTS NetworkEvents, int i);//�ͻ������ߴ���
	bool sendPok(SOCKET socketClient, player p);//������ҵľ�����Ϣ
};

typedef struct attack
{
	string pok="";//���о���
	string name = "";//��ʽ����
	int seq = 0;//��ʽ���
	float damage = 0;//�����˺�
	bool learn = 0;//�Ƿ�ϰ��
	float hpOppo = 0;//������з�ʣ��Ѫ��
	bool dodge = 0;//�Ƿ񱻵з�����
	bool strike = 0;//�Ƿ񱩻�
}ATTACK;

extern vector<player> Players;//�洢�û���Ϣ������

void readPlayer(ifstream& fs);//��һ�������Ϣ

#endif
