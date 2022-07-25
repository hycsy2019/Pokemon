#include"pokemonClient.h"

ATTACK Pokemon::attack(Pokemon& pok, int choice)//攻击方法
{
	ATTACK atkNull;
	return atkNull;
}//攻击方法

void Pokemon::printProperty(Pokemon pok,stringstream &out)//打印精灵属性
{
	out << name << endl;
	switch (type)
	{
	case ATK:
		out << "力量型"<<endl;
		break;
	case HP:
		out << "肉盾型" << endl;
		break;
	case DF:
		out << "防御型" << endl;
		break;
	case ATKT:
		out << "敏捷型" << endl;
		break;
	default: 
		break;
	}
	out << "等级" << lv << endl;
	out << "生命：" << hp << endl;
	out << "攻击：" << atk << endl;
	out << "防御：" << df << endl;
	out << "攻击间隔：" << atkt << endl;
	out << "经验：" << exp << endl;
	out << "已学习招式：";

	int moves=1;

	ATTACK attackWay = attack(pok, moves);
	while ((attackWay.damage!=0)&&attackWay.learn)
	{
		out << attackWay.name << " ";
		moves++;
		attackWay = attack(pok, moves);
	}
	out << endl;
	if (attackWay.damage != 0) out << "未学习招式：";
	while(attackWay.damage != 0)
	{
		out << attackWay.name << " ";
		moves++;
		attackWay = attack(pok, moves);
	}
	out << endl<<endl;
}

void Pokemon::upgrade(float newExp)//升一级属性值少量增加，主属性增加量相对较多
{
	if (lv < 15)
	{
		switch (type)
		{
		case ATK:
			atk *= UPGTYPE;
			hp *= UPG;
			df *= UPG;
			atkt /= UPG;
			break;
		case HP:
			atk *= UPG;
			hp *= UPGTYPE;
			df *= UPG;
			atkt /= UPG;
			break;
		case DF:
			atk *= UPG;
			hp *= UPG;
			df *= UPGTYPE;
			atkt /= UPG;
			break;
		case ATKT:
			atk *= UPG;
			hp *= UPG;
			df *= UPG;
			atkt /= UPGTYPE;
			break;
		}
		lv++;
		exp = newExp;
	}
}

//1.妙蛙种子ATK
class miaoWaZhongZi:public Pokemon
{
public:
	miaoWaZhongZi()
	{
		pokSeq = 1;
		type = ATK;
		name = "妙蛙种子";
		lettername = "miaowazhongzi";
		hp = 45;
		atk = 49;
		df = 49;
		atkt = 22;
	}
	virtual ATTACK attack(Pokemon& pok, int choice) override;
};

ATTACK miaoWaZhongZi::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 12)  moves = 3;
	else if (lv >=4) moves = 2;
	else moves = 1;
	
	if(choice==0) choice = (rand() % moves) + 1;//随机选择招式   
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "藤鞭";
		power = 45;
		break;
	case 2:
		Atk.name = "飞叶快刀";
		power = 55;
		break;
	case 3:
		Atk.name = "种子炸弹";
		power = 80;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//2.皮卡丘ATKT
class piKaQiu :public Pokemon
{
public:
	piKaQiu()
	{
		pokSeq = 2;
		type = ATKT;
		name = "皮卡丘";
		lettername = "pikaqiu";
		hp = 35;
		atk = 55;
		df = 40;
		atkt = 10;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK piKaQiu::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >=13)  moves = 4;
	else if (lv >= 10) moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//随机选择招式
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "电击";
		power = 40;
		break;
	case 2:
		Atk.name = "电光";
		power = 65;
		break;
	case 3:
		Atk.name = "放电";
		power = 80;
		break;
	case 4:
		Atk.name = "十万伏特";
		power = 90;
		break;
	default: return Atk;
		break;
	}

	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//3.小火龙ATKT
class xiaoHuoLong :public Pokemon
{
public:
	xiaoHuoLong()
	{
		pokSeq = 3;
		type = ATKT;
		name = "小火龙";
		lettername = "xiaohuolong";
		hp = 39;
		atk = 52;
		df = 43;
		atkt = 15;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK xiaoHuoLong::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 14)  moves = 4;
	else if (lv >=10 ) moves = 3;
	else if (lv >= 2) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//随机选择招式
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "火漩涡";
		power = 15;
		break;
	case 2:
		Atk.name = "火花";
		power = 40;
		break;
	case 3:
		Atk.name = "火焰放射";
		power = 95;
		break;
	case 4:
		Atk.name = "十字火";
		power = 120;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//4.杰尼龟DF
class jieNiGui :public Pokemon
{
public:
	jieNiGui()
	{
		pokSeq = 4;
		type = DF;
		name = "杰尼龟";
		lettername = "jienigui";
		hp = 44;
		atk = 48;
		df = 65;
		atkt = 23;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK jieNiGui::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 13)  moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//随机选择招式
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "冰冻之风";
		power = 55;
		break;
	case 2:
		Atk.name = "水之波动";
		power = 60;
		break;
	case 3:
		Atk.name = "水炮";
		power = 110;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//5.菊草叶DF
class juCaoYe :public Pokemon
{
public:
	juCaoYe()
	{
		pokSeq = 5;
		type = DF;
		name = "菊草叶";
		lettername = "jucaoye";
		hp = 45;
		atk = 49;
		df = 65;
		atkt = 22;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK juCaoYe::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 14)  moves = 4;
	else if (lv >=9 ) moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//随机选择招式
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "魔法叶";
		power = 60;
		break;
	case 2:
		Atk.name = "草之誓约";
		power = 80;
		break;
	case 3:
		Atk.name = "能量球";
		power = 90;
		break;
	case 4:
		Atk.name = "日光束";
		power = 120;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//6.飞天螳螂ATK
class feiTianTangLang:public Pokemon
{
public:
	feiTianTangLang()
	{
		pokSeq = 6;
		type = ATK;
		name = "飞天螳螂";
		lettername = "feitiantanglang";
		hp = 70;
		atk = 110;
		df = 80;
		atkt = 10;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK feiTianTangLang::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 10)  moves = 4;
	else if (lv >= 8) moves = 3;
	else if (lv >= 4) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//随机选择招式
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "连斩";
		power = 40;
		break;
	case 2:
		Atk.name = "翅膀攻击";
		power = 60;
		break;
	case 3:
		Atk.name = "空气斩";
		power = 75;
		break;
	case 4:
		Atk.name = "十字剪";
		power = 80;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//7.墨海马DF
class moHaiMa :public Pokemon
{
public:
	moHaiMa()
	{
		pokSeq = 7;
		type = DF;
		name = "墨海马";
		lettername = "mohaima";
		hp = 30;
		atk = 40;
		df = 70;
		atkt = 17;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK moHaiMa::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 11) moves = 5;
	else if (lv >= 10)  moves = 4;
	else if (lv >= 8) moves = 3;
	else if (lv >= 3) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//随机选择招式
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "潮旋";
		power = 35;
		break;
	case 2:
		Atk.name = "水枪";
		power = 40;
		break;
	case 3:
		Atk.name = "泡沫光线";
		power = 65;
		break;
	case 4:
		Atk.name = "攀瀑";
		power = 80;
		break;
	case 5:
		Atk.name = "水流裂破";
		power = 85;
		break;
	default: return Atk;
		break;
	}

	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//8.胖可丁HP
class pangKeDing :public Pokemon
{
public:
	pangKeDing()
	{
		pokSeq = 8;
		type = HP;
		name = "胖可丁";
		lettername = "pangkeding";
		hp = 140;
		atk = 70;
		df = 45;
		atkt = 22;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK pangKeDing::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 11) moves = 3;
	else if (lv >= 4) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//随机选择招式
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "魅惑之声";
		power = 40;
		break;
	case 2:
		Atk.name = "吸取之吻";
		power = 50;
		break;
	case 3:
		Atk.name = "魔法闪耀";
		power = 80;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//9.喵喵ATKT
class miaoMiao :public Pokemon
{
public:
	miaoMiao()
	{
		pokSeq = 9;
		type = ATKT;
		name = "喵喵";
		lettername = "miaomiao";
		hp = 40;
		atk = 45;
		df = 35;
		atkt = 11;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK miaoMiao::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 9) moves = 3;
	else if (lv >= 4) moves = 2;
	else moves = 1;

	if(choice==0) choice = (rand() % moves) + 1;//随机选择招式
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "抓";
		power = 40;
		break;
	case 2:
		Atk.name = "居合斩";
		power = 50;
		break;
	case 3:
		Atk.name = "切裂";
		power = 70;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//10.火爆猴ATK
class huoBaoHou :public Pokemon
{
public:
	huoBaoHou()
	{
		pokSeq = 10;
		type = ATK;
		name = "火爆猴";
		lettername = "huobaohou";
		hp = 65;
		atk = 105;
		df = 60;
		atkt = 11;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK huoBaoHou::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 12) moves = 4;
	else if (lv >= 8) moves = 3;
	else if (lv >= 5) moves = 2;
	else moves = 1;

	if(choice==0) choice = (rand() % moves) + 1;//随机选择招式   
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "空手劈";
		power = 50;
		break;
	case 2:
		Atk.name = "下盘踢";
		power = 65;
		break;
	case 3:
		Atk.name = "劈瓦";
		power = 75;
		break;
	case 4:
		Atk.name = "十字劈";
		power = 100;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//11.腕力ATK
class wanLi :public Pokemon
{
public:
	wanLi()
	{
		pokSeq = 11;
		type = ATK;
		name = "腕力";
		lettername = "wanli";
		hp = 70;
		atk = 80;
		df = 50;
		atkt = 29;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK wanLi::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 12) moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if(choice==0) choice = (rand() % moves) + 1;//随机选择招式  
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "借力摔";
		power = 70;
		break;
	case 2:
		Atk.name = "爆裂拳";
		power = 100;
		break;
	case 3:
		Atk.name = "蛮力";
		power = 120;
		break;
	default: return Atk;
		break;
	}

	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//12.臭臭泥HP
class chouChouNi:public Pokemon
{
public:
	chouChouNi()
	{
		pokSeq = 12;
		type = HP;
		name = "臭臭泥";
		lettername = "chouchouni";
		hp = 105;
		atk = 105;
		df = 75;
		atkt = 20;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK chouChouNi::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 12) moves = 4;
	 else if (lv >= 10) moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if(choice==0) choice = (rand() % moves) + 1;//随机选择招式   
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "污泥攻击";
		power = 65;
		break;
	case 2:
		Atk.name = "毒击";
		power = 80;
		break;
	case 3:
		Atk.name = "污泥炸弹";
		power = 90;
		break;
	case 4:
		Atk.name = "污泥波";
		power = 95;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//13.大舌头HP
class daSheTou :public Pokemon
{
public:
	daSheTou()
	{
		pokSeq = 13;
		type = HP;
		name = "大舌头";
		lettername = "dashetou";
		hp = 90;
		atk = 55;
		df = 75;
		atkt = 33;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK daSheTou::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv == 15) moves = 5;
	else if (lv >= 13) moves = 4;
	else if (lv >= 8) moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if(choice==0) choice = (rand() % moves) + 1;//随机选择招式  
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "踩踏";
		power = 65;
		break;
	case 2:
		Atk.name = "摔打";
		power = 80;
		break;
	case 3:
		Atk.name = "泰山压顶";
		power = 85;
		break;
	case 4:
		Atk.name = "百万吨重踢";
		power = 120;
		break;
	case 5:
		Atk.name = "终极冲击";
		power = 150;
		break;
	default: return Atk;
		break;
	}

	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//14.菊石兽DF
class juShiShou :public Pokemon
{
public:
	juShiShou()
	{
		pokSeq = 14;
		type = DF;
		name = "菊石兽";
		lettername = "jushishou";
		hp = 35;
		atk = 40;
		df = 100;
		atkt = 29;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK juShiShou::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 9) moves = 3;
	else if (lv >= 3) moves = 2;
	else moves = 1;

	if (choice == 0)
	{
		choice = (rand() % moves) + 1;//随机选择招式  
	}
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "岩石爆击";
		power = 25;
		break;
	case 2:
		Atk.name = "落石";
		power = 50;
		break;
	case 3:
		Atk.name = "原始之力";
		power = 60;
		break;
	default: return Atk;
		break;
	}

	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//15.皮皮HP
class piPi:public Pokemon
{
public:
	piPi()
	{
		pokSeq = 15;
		type = HP;
		name = "皮皮";
		lettername = "pipi";
		hp = 70;
		atk = 45;
		df = 48;
		atkt = 29;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK piPi::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 12) moves = 2;
	else moves = 1;

	if (choice == 0)
	{
		choice = (rand() % moves) + 1;//随机选择招式  
	}
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "月亮之力";
		power = 95;
		break;
	case 2:
		Atk.name = "薄雾炸裂";
		power = 100;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//16.伊布ATKT
class yiBu :public Pokemon
{
public:
	yiBu()
	{
		pokSeq = 16;
		type = ATKT;
		name = "伊布";
		lettername = "yibu";
		hp = 55;
		atk = 55;
		df = 50;
		atkt = 18;
	}
	virtual ATTACK attack(Pokemon& pok,int choice) override;
};

ATTACK yiBu::attack(Pokemon& pok,int choice)
{
	ATTACK Atk;
	int power=0, moves;

	//根据等级来确定招式数
	if (lv >= 12) moves = 4;
	else if (lv > 6) moves = 3;
	else if (lv > 4) moves = 2;
	else moves = 1;

	srand(time(NULL));
	if(choice==0) choice = (rand() % moves) + 1;//随机选择招式   
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "电光一闪";
		power = 40;
		break;
	case 2:
		Atk.name = "气象球";
		power = 50;
		break;
	case 3:
		Atk.name = "高速星星";
		power = 60;
		break;
	case 4:
		Atk.name = "巨声";
		power = 90;
		break;
	default: return Atk;
		return Atk;
	}
	srand(time(NULL));
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; 
	return Atk;
}

Pokemon* Pokemon::newPok(int Pok)//根据编号返回一个创建的精灵指针
{
	Pokemon *pok = nullptr;
	switch (Pok)
	{
	case 1:
		pok = new miaoWaZhongZi(); break;
	case 2:
		pok = new piKaQiu(); break;
	case 3:
		pok = new xiaoHuoLong(); break;
	case 4:
		pok = new jieNiGui(); break;
	case 5:
		pok = new juCaoYe(); break;
	case 6:
		pok = new feiTianTangLang(); break;
	case 7:
		pok = new moHaiMa(); break;
	case 8:
		pok = new pangKeDing(); break;
	case 9:
		pok = new miaoMiao(); break;
	case 10:
		pok = new huoBaoHou(); break;
	case 11:
		pok = new wanLi(); break;
	case 12:
		pok = new chouChouNi(); break;
	case 13:
		pok = new daSheTou(); break;
	case 14:
		pok = new juShiShou(); break;
	case 15:
		pok = new piPi(); break;
	case 16:
		pok = new yiBu(); break;
	}
	return pok;
}

/*
int main()
{
	int Pok;
	Pokemon *pok=nullptr;

	while (true)
	{
		cout << "请选择要查看的精灵：1.妙蛙种子 2.皮卡丘 3.小火龙 4.杰尼龟 5.菊草叶 6.飞天螳螂 7.墨海马 ";
		cout << "8.胖可丁 9.喵喵 10.火爆猴 11.腕力 12.臭臭泥 13.菊石兽 14.皮皮 15.伊布" << endl;
		cin >> Pok;

		pok = pok->newPok(Pok);
		pok->printProperty(*pok);

		cout << "请选择：1.升级 2.查看其他精灵" << endl;
		int c;
		cin >> c;
		while (c == 1)
		{
			pok->upgrade(0.0);
			pok->printProperty(*pok);
			cout << "请选择：1.升级 2.查看其他精灵" << endl;
			int c;
			cin >> c;
		}
	}
	pok.deletePok(pok);
}
*/