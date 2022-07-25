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

enum Type { ATK, HP, DF, ATKT };//�������ࣺ�����͡�����͡������͡�������

typedef struct attack ATTACK;//��������

class Pokemon {
protected:
	enum Type { ATK, HP, DF, ATKT };//�������ࣺ�����͡�����͡������͡�������
	int pokSeq;//������
	Type type;//����
	string name;//����
	string lettername;//ƴ������
	int lv = 1;//�ȼ�
	float atk;//������
	float df;//������
	float atkt;//�������
	float hp;//����ֵ
public:
	float exp = 0.0;//����ֵ
	void initPok(int Lv, float Exp)//���ݾ���ȼ��;���ֵ��ʼ������
	{
		if (this != NULL)
		{
			while (lv < Lv) this->upgrade(0);
			exp = Exp;
		}
	}
	
	float getDf() { return df; }//���ط�����ֵ
	float getHp() { return hp; }//������������
	int getLv() { return lv; }//���صȼ�
	float getAtkt() { return atkt; }//���ع������
	string getLetterName() { return lettername; };//����ƴ������
	string getName() { return name; };//��������
	int getSeq() { return pokSeq; }//���ؾ�����

	void printProperty(Pokemon pok, stringstream &out);//��ӡ��������
	void upgrade(float newExp);//��һ��
	Pokemon* newPok(int Pok);//���ݱ�ŷ���һ�������ľ���ָ��
	virtual ATTACK attack(Pokemon& pok, int choice);//��������
	void deletePok(Pokemon* pok) { delete pok; }//ɾ���Ѿ������ľ���
};

class player
{
private:
	string name,password;//�û�������
	
public:
	int pokNum;//������
	int winnum=0;//Ӯ�ĳ���
	int totalnum=0;//�����ܹ�����
	bool medal[7];//ѫ��
	vector<Pokemon*> poks;//����
	int Login;//�Ƿ��ѵ�¼
	player(string Name) { name = Name; };//������Ҷ���
	void assignPok();//�����������һ������
	bool login(string Name,player& p);//��¼
	void friend readPlayers(string s);//���ַ����ж�ȡһ���������
	void printPlayerInfo(int pokInfo,stringstream &out);//��ӡ�����Ϣ������ѡ���Ƿ��ӡ��������
	
	SOCKET connectServer();//���ӷ�����
	bool enter(SOCKET socketServer,int choice,string Password);//������Ϸ��ע����¼

	string getName() { return name; }//��ȡ�û���
	string getPassword() { return password; }//��ȡ����
};

class Fight
{
private:
	Pokemon *pok1, *pok2;//��ֻ��ս�ľ���
	vector< pair<ATTACK, ATTACK>>  rounds;//������ֻ����ÿ�غϵ���ս��¼
	int first = (rand() % 2) + 1;//����������ַ�
	friend class GUIfight;
public:
	Fight(Pokemon* pokA, Pokemon* pokB) { pok1 = pokA; pok2 = pokB; }//�����ս
	Pokemon* wholeFight();//ս�����ɣ����ػ�ʤ�ľ���
	void round(Pokemon* pokFirst, Pokemon* pokSecond, float& hpFirst, float& hpSecond, int& strikeFir, int& strikeSec);//ÿ����ս�غ�
	bool dodge(Pokemon pokAttack, Pokemon pokOppo);//pok�Ĺ����ܷ񱻵з����ܳɹ�
	bool strike(int& strikeN);//�ܷ񱩻�
	bool printRounds();//���ÿһ�غϵ�ս��
	~Fight() { rounds.clear(); }//����
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

#define UPGTYPE (float)1.2//�����Լӳɸ���
#define UPG (float)1.1//�������������ӳ�

#define POKNUM 15//��������

#endif
