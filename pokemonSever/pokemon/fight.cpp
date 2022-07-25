#include"pokemon.h"

class Fight
{
private:
	Pokemon *pok1, *pok2;//两只对战的精灵
	vector< pair<ATTACK, ATTACK>>  rounds;//保存两只精灵每回合的作战记录
	int first = (rand() % 2) +1 ;//随机决定先手方
public:
	Fight(Pokemon* pokA, Pokemon* pokB){pok1 = pokA; pok2 = pokB;}
	Pokemon* wholeFight();//战斗生成，返回获胜的精灵
	void round(Pokemon* pokFirst,Pokemon* pokSecond,float& hpFirst,float& hpSecond, int& strikeFir, int& strikeSec);//每个对战回合,返回双方剩余生命值
	bool dodge(Pokemon pokAttack, Pokemon pokOppo);//pok的攻击能否被敌方闪避成功
	bool strike(int& strikeN);//能否暴击
	bool printRounds();//输出每一回合的战况
	~Fight() { rounds.clear(); }
};

Pokemon* Fight::wholeFight()
{
	float hp1 = pok1->getHp(), hp2 = pok2->getHp();//初始生命值为上限
	int strikeN1 = 0, strikeN2 = 0;//累积未发生暴击的次数

	while (hp1 != 0.0 && hp2 != 0.0)//有一方血量为0时战斗结束
	{
		strikeN1++; strikeN2++;//未暴击次数增加
		//随机决定先攻击的精灵
		if (first == 1) round(pok1,pok2,hp1, hp2,strikeN1,strikeN2);
		else round(pok2,pok1,hp2, hp1,strikeN2,strikeN1);
	}

	if (hp1 == 0.0) return pok2;//精灵1的血量为0，则返回获胜的精灵2
	else return pok1;
}

bool Fight::dodge(Pokemon pokAtk,Pokemon pokDf)
{
	float hit = (3*pokAtk.getLv()*pokDf.getAtkt()) / ((pokAtk.getLv() + pokDf.getLv())*pokAtk.getAtkt());//命中率
	
	float r = rand() / float(RAND_MAX);//0-1的随机数
	if (r <= hit) return false;
	else return true;
}

bool Fight::strike(int& strikeN)
{
	float r = rand() / float(RAND_MAX);
	if (r < 0.08*strikeN)//根据未暴击次数累加暴击率
	{
		strikeN = 0;
		return true;
	}
	else return false;
}

void Fight::round(Pokemon* pokFirst, Pokemon* pokSecond, 
	float& hpFirst, float& hpSecond,int& strikeFir,int& strikeSec)
{
	ATTACK atkFir, atkSec;

	atkFir = pokFirst->attack(*pokSecond, 0);//先攻击的精灵使用的招式

	if (!dodge(*pokFirst, *pokSecond))//敌方闪避失败
	{
		if (strike(strikeFir))
		{
			atkFir.damage *= 1.5;//暴击成功，产生1.5倍伤害
			atkFir.strike = 1;
		}
	}
	else
	{
		atkFir.dodge = 1;
		atkFir.damage = 0;//被闪避无伤害
	}

	atkFir.hpOppo = hpSecond - atkFir.damage;//攻击后的敌方血量存到容器rounds里
	hpSecond -= atkFir.damage;//后攻击的精灵掉血

	if (atkFir.hpOppo < 0)
	{
		atkFir.hpOppo = 0;//血量下限为0
		hpSecond =0;//后攻击的精灵输掉比赛
	}
	else//敌方血量未减至0
	{
		atkSec = pokSecond->attack(*pokFirst, 0);

		if (!dodge(*pokSecond, *pokFirst))//敌方闪避失败
		{
			if (strike(strikeSec))
			{
				atkSec.damage *= 1.5;//暴击成功，产生1.5倍伤害
				atkSec.strike = 1;
			}
		}
		else
		{
			atkSec.dodge = 1;
			atkSec.damage = 0;//被闪避无伤害
		}

		atkSec.hpOppo = hpFirst - atkSec.damage;
		hpFirst -= atkSec.damage;
		if (atkSec.hpOppo < 0)
		{
			atkSec.hpOppo = 0;
			hpFirst = 0;//先攻击的精灵输掉比赛
		}
	}
	atkFir.pok = pokFirst->getName();
	atkSec.pok = pokSecond->getName();
	rounds.push_back(make_pair(atkFir, atkSec));//容器rounds尾部加入新的回合双方攻击信息
}

bool Fight::printRounds()
{
	int round = 1;
	float hp1, hp2;

	cout << "随机先手：";
	if (first == 1)
	{
		cout << pok1->getName() << endl;
		hp1 = pok1->getHp();
		hp2 = pok2->getHp();
	}
	else
	{
		cout << pok2->getName() << endl;
		hp1 = pok2->getHp();
		hp2 = pok1->getHp();
	}

	cout.setf(ios::fixed);

	for (vector< pair<ATTACK, ATTACK>>::iterator it = rounds.begin(); 
		it != rounds.end(); it++,round++)
	{
		if (it->first.hpOppo != 0.0)//对方血量未达到0，继续攻击
		{
			cout <<endl<< "第" << round << "回合" << endl;
			cout << it->first.pok<< "：" << endl;
			cout << "血量：" <<setprecision(2) << hp1 << endl;
			cout << "使用招式：" << it->first.name << endl;
			if (it->first.dodge) cout << "被闪避  " ;
			else cout << "命中  " ;
			if (it->first.strike) cout << "暴击" << endl;
			else cout << "普通攻击" << endl;
			cout << "造成伤害：" << setprecision(2) << it->first.damage << endl;
			hp2 = it->first.hpOppo;

			cout << endl << it->second.pok<< "：" << endl;
			cout << "血量：" << setprecision(2) << hp2 << endl;
			cout << "使用招式：" << it->second.name << endl;
			if (it->second.dodge) cout << "被闪避  ";
			else cout << "命中  ";
			if (it->second.strike) cout << "暴击" << endl;
			else cout << "普通攻击" << endl;
			cout << "造成伤害：" << setprecision(2) << it->second.damage << endl;
			hp1 = it->second.hpOppo;

			if (hp1 >= 0 && hp1<=0)  return true;
		}
		else return true;
	}
	return false;
}

int main()
{
	srand(time(NULL));
	int Pok;
	Pokemon *pok1 = nullptr;
	Pokemon *pok2 = nullptr;

	cout << "这是一个精灵测试程序" << endl;
	while (true)
	{
		cout << "请选择参战精灵1：1.妙蛙种子 2.皮卡丘 3.小火龙 4.杰尼龟 5.菊草叶 6.飞天螳螂 7.墨海马 ";
		cout << "8.胖可丁 9.喵喵 10.火爆猴 11.腕力 12.臭臭泥 13.菊石兽 14.皮皮 15.伊布" << endl;
		cin >> Pok;

		pok1 = pok1->newPok(Pok);
		pok1->printProperty(*pok1);

		cout << "请选择：1.升级 2.选择对手" << endl;
		int c;
		cin >> c;
		while (c == 1)
		{
			pok1->upgrade(0.0);
			pok1->printProperty(*pok1);
			cout << "请选择：1.升级 2.选择对手" << endl;
			cin >> c;
		}

		if (c == 2)
		{
			cout << "请选择参战精灵2：1.妙蛙种子 2.皮卡丘 3.小火龙 4.杰尼龟 5.菊草叶 6.飞天螳螂 7.墨海马 ";
			cout << "8.胖可丁 9.喵喵 10.火爆猴 11.腕力 12.臭臭泥 13.菊石兽 14.皮皮 15.伊布" << endl;
			cin >> Pok;

			pok2 = pok2->newPok(Pok);
			pok2->printProperty(*pok2);

			cout << "请选择：1.升级 2.开始战斗" << endl;
			cin >> c;
			while (c == 1)
			{
				pok2->upgrade(0.0);
				pok2->printProperty(*pok2);
				cout << "请选择：1.升级 2.开始战斗" << endl;
				cin >> c;
			}

			if (c == 2)
			{
				Fight F = Fight(pok1,pok2);
				Pokemon* winPok = F.wholeFight();
				F.printRounds();
				cout << winPok->getName() << "获胜"<<endl<<endl;
			}
		}
	}
}