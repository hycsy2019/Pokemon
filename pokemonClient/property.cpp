#include"pokemonClient.h"

ATTACK Pokemon::attack(Pokemon& pok, int choice)//��������
{
	ATTACK atkNull;
	return atkNull;
}//��������

void Pokemon::printProperty(Pokemon pok,stringstream &out)//��ӡ��������
{
	out << name << endl;
	switch (type)
	{
	case ATK:
		out << "������"<<endl;
		break;
	case HP:
		out << "�����" << endl;
		break;
	case DF:
		out << "������" << endl;
		break;
	case ATKT:
		out << "������" << endl;
		break;
	default: 
		break;
	}
	out << "�ȼ�" << lv << endl;
	out << "������" << hp << endl;
	out << "������" << atk << endl;
	out << "������" << df << endl;
	out << "���������" << atkt << endl;
	out << "���飺" << exp << endl;
	out << "��ѧϰ��ʽ��";

	int moves=1;

	ATTACK attackWay = attack(pok, moves);
	while ((attackWay.damage!=0)&&attackWay.learn)
	{
		out << attackWay.name << " ";
		moves++;
		attackWay = attack(pok, moves);
	}
	out << endl;
	if (attackWay.damage != 0) out << "δѧϰ��ʽ��";
	while(attackWay.damage != 0)
	{
		out << attackWay.name << " ";
		moves++;
		attackWay = attack(pok, moves);
	}
	out << endl<<endl;
}

void Pokemon::upgrade(float newExp)//��һ������ֵ�������ӣ���������������Խ϶�
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

//1.��������ATK
class miaoWaZhongZi:public Pokemon
{
public:
	miaoWaZhongZi()
	{
		pokSeq = 1;
		type = ATK;
		name = "��������";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 12)  moves = 3;
	else if (lv >=4) moves = 2;
	else moves = 1;
	
	if(choice==0) choice = (rand() % moves) + 1;//���ѡ����ʽ   
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "�ٱ�";
		power = 45;
		break;
	case 2:
		Atk.name = "��Ҷ�쵶";
		power = 55;
		break;
	case 3:
		Atk.name = "����ը��";
		power = 80;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//2.Ƥ����ATKT
class piKaQiu :public Pokemon
{
public:
	piKaQiu()
	{
		pokSeq = 2;
		type = ATKT;
		name = "Ƥ����";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >=13)  moves = 4;
	else if (lv >= 10) moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//���ѡ����ʽ
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "���";
		power = 40;
		break;
	case 2:
		Atk.name = "���";
		power = 65;
		break;
	case 3:
		Atk.name = "�ŵ�";
		power = 80;
		break;
	case 4:
		Atk.name = "ʮ�����";
		power = 90;
		break;
	default: return Atk;
		break;
	}

	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//3.С����ATKT
class xiaoHuoLong :public Pokemon
{
public:
	xiaoHuoLong()
	{
		pokSeq = 3;
		type = ATKT;
		name = "С����";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 14)  moves = 4;
	else if (lv >=10 ) moves = 3;
	else if (lv >= 2) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//���ѡ����ʽ
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "������";
		power = 15;
		break;
	case 2:
		Atk.name = "��";
		power = 40;
		break;
	case 3:
		Atk.name = "�������";
		power = 95;
		break;
	case 4:
		Atk.name = "ʮ�ֻ�";
		power = 120;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//4.�����DF
class jieNiGui :public Pokemon
{
public:
	jieNiGui()
	{
		pokSeq = 4;
		type = DF;
		name = "�����";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 13)  moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//���ѡ����ʽ
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "����֮��";
		power = 55;
		break;
	case 2:
		Atk.name = "ˮ֮����";
		power = 60;
		break;
	case 3:
		Atk.name = "ˮ��";
		power = 110;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//5.�ղ�ҶDF
class juCaoYe :public Pokemon
{
public:
	juCaoYe()
	{
		pokSeq = 5;
		type = DF;
		name = "�ղ�Ҷ";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 14)  moves = 4;
	else if (lv >=9 ) moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//���ѡ����ʽ
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "ħ��Ҷ";
		power = 60;
		break;
	case 2:
		Atk.name = "��֮��Լ";
		power = 80;
		break;
	case 3:
		Atk.name = "������";
		power = 90;
		break;
	case 4:
		Atk.name = "�չ���";
		power = 120;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//6.�������ATK
class feiTianTangLang:public Pokemon
{
public:
	feiTianTangLang()
	{
		pokSeq = 6;
		type = ATK;
		name = "�������";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 10)  moves = 4;
	else if (lv >= 8) moves = 3;
	else if (lv >= 4) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//���ѡ����ʽ
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "��ն";
		power = 40;
		break;
	case 2:
		Atk.name = "��򹥻�";
		power = 60;
		break;
	case 3:
		Atk.name = "����ն";
		power = 75;
		break;
	case 4:
		Atk.name = "ʮ�ּ�";
		power = 80;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//7.ī����DF
class moHaiMa :public Pokemon
{
public:
	moHaiMa()
	{
		pokSeq = 7;
		type = DF;
		name = "ī����";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 11) moves = 5;
	else if (lv >= 10)  moves = 4;
	else if (lv >= 8) moves = 3;
	else if (lv >= 3) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//���ѡ����ʽ
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "����";
		power = 35;
		break;
	case 2:
		Atk.name = "ˮǹ";
		power = 40;
		break;
	case 3:
		Atk.name = "��ĭ����";
		power = 65;
		break;
	case 4:
		Atk.name = "����";
		power = 80;
		break;
	case 5:
		Atk.name = "ˮ������";
		power = 85;
		break;
	default: return Atk;
		break;
	}

	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//8.�ֿɶ�HP
class pangKeDing :public Pokemon
{
public:
	pangKeDing()
	{
		pokSeq = 8;
		type = HP;
		name = "�ֿɶ�";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 11) moves = 3;
	else if (lv >= 4) moves = 2;
	else moves = 1;

	if (choice == 0) choice = (rand() % moves) + 1;//���ѡ����ʽ
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "�Ȼ�֮��";
		power = 40;
		break;
	case 2:
		Atk.name = "��ȡ֮��";
		power = 50;
		break;
	case 3:
		Atk.name = "ħ����ҫ";
		power = 80;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//9.����ATKT
class miaoMiao :public Pokemon
{
public:
	miaoMiao()
	{
		pokSeq = 9;
		type = ATKT;
		name = "����";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 9) moves = 3;
	else if (lv >= 4) moves = 2;
	else moves = 1;

	if(choice==0) choice = (rand() % moves) + 1;//���ѡ����ʽ
	if (choice <= moves) Atk.learn = 1;

	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "ץ";
		power = 40;
		break;
	case 2:
		Atk.name = "�Ӻ�ն";
		power = 50;
		break;
	case 3:
		Atk.name = "����";
		power = 70;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//10.�𱬺�ATK
class huoBaoHou :public Pokemon
{
public:
	huoBaoHou()
	{
		pokSeq = 10;
		type = ATK;
		name = "�𱬺�";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 12) moves = 4;
	else if (lv >= 8) moves = 3;
	else if (lv >= 5) moves = 2;
	else moves = 1;

	if(choice==0) choice = (rand() % moves) + 1;//���ѡ����ʽ   
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "������";
		power = 50;
		break;
	case 2:
		Atk.name = "������";
		power = 65;
		break;
	case 3:
		Atk.name = "����";
		power = 75;
		break;
	case 4:
		Atk.name = "ʮ����";
		power = 100;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//11.����ATK
class wanLi :public Pokemon
{
public:
	wanLi()
	{
		pokSeq = 11;
		type = ATK;
		name = "����";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 12) moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if(choice==0) choice = (rand() % moves) + 1;//���ѡ����ʽ  
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "����ˤ";
		power = 70;
		break;
	case 2:
		Atk.name = "����ȭ";
		power = 100;
		break;
	case 3:
		Atk.name = "����";
		power = 120;
		break;
	default: return Atk;
		break;
	}

	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//12.������HP
class chouChouNi:public Pokemon
{
public:
	chouChouNi()
	{
		pokSeq = 12;
		type = HP;
		name = "������";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 12) moves = 4;
	 else if (lv >= 10) moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if(choice==0) choice = (rand() % moves) + 1;//���ѡ����ʽ   
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "���๥��";
		power = 65;
		break;
	case 2:
		Atk.name = "����";
		power = 80;
		break;
	case 3:
		Atk.name = "����ը��";
		power = 90;
		break;
	case 4:
		Atk.name = "���ನ";
		power = 95;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//13.����ͷHP
class daSheTou :public Pokemon
{
public:
	daSheTou()
	{
		pokSeq = 13;
		type = HP;
		name = "����ͷ";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv == 15) moves = 5;
	else if (lv >= 13) moves = 4;
	else if (lv >= 8) moves = 3;
	else if (lv >= 6) moves = 2;
	else moves = 1;

	if(choice==0) choice = (rand() % moves) + 1;//���ѡ����ʽ  
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "��̤";
		power = 65;
		break;
	case 2:
		Atk.name = "ˤ��";
		power = 80;
		break;
	case 3:
		Atk.name = "̩ɽѹ��";
		power = 85;
		break;
	case 4:
		Atk.name = "���������";
		power = 120;
		break;
	case 5:
		Atk.name = "�ռ����";
		power = 150;
		break;
	default: return Atk;
		break;
	}

	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//14.��ʯ��DF
class juShiShou :public Pokemon
{
public:
	juShiShou()
	{
		pokSeq = 14;
		type = DF;
		name = "��ʯ��";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 9) moves = 3;
	else if (lv >= 3) moves = 2;
	else moves = 1;

	if (choice == 0)
	{
		choice = (rand() % moves) + 1;//���ѡ����ʽ  
	}
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "��ʯ����";
		power = 25;
		break;
	case 2:
		Atk.name = "��ʯ";
		power = 50;
		break;
	case 3:
		Atk.name = "ԭʼ֮��";
		power = 60;
		break;
	default: return Atk;
		break;
	}

	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//15.ƤƤHP
class piPi:public Pokemon
{
public:
	piPi()
	{
		pokSeq = 15;
		type = HP;
		name = "ƤƤ";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 12) moves = 2;
	else moves = 1;

	if (choice == 0)
	{
		choice = (rand() % moves) + 1;//���ѡ����ʽ  
	}
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "����֮��";
		power = 95;
		break;
	case 2:
		Atk.name = "����ը��";
		power = 100;
		break;
	default: return Atk;
		break;
	}
	Atk.damage = ((lv*(float)0.4 + 2)*power*atk / (pok.getDf() * 50) + 2)*
		(217 + rand() / float(RAND_MAX) * 38) / 255; return Atk;
}

//16.����ATKT
class yiBu :public Pokemon
{
public:
	yiBu()
	{
		pokSeq = 16;
		type = ATKT;
		name = "����";
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

	//���ݵȼ���ȷ����ʽ��
	if (lv >= 12) moves = 4;
	else if (lv > 6) moves = 3;
	else if (lv > 4) moves = 2;
	else moves = 1;

	srand(time(NULL));
	if(choice==0) choice = (rand() % moves) + 1;//���ѡ����ʽ   
	if (choice <= moves) Atk.learn = 1;
	Atk.seq = choice;
	switch (choice)
	{
	case 1:
		Atk.name = "���һ��";
		power = 40;
		break;
	case 2:
		Atk.name = "������";
		power = 50;
		break;
	case 3:
		Atk.name = "��������";
		power = 60;
		break;
	case 4:
		Atk.name = "����";
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

Pokemon* Pokemon::newPok(int Pok)//���ݱ�ŷ���һ�������ľ���ָ��
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
		cout << "��ѡ��Ҫ�鿴�ľ��飺1.�������� 2.Ƥ���� 3.С���� 4.����� 5.�ղ�Ҷ 6.������� 7.ī���� ";
		cout << "8.�ֿɶ� 9.���� 10.�𱬺� 11.���� 12.������ 13.��ʯ�� 14.ƤƤ 15.����" << endl;
		cin >> Pok;

		pok = pok->newPok(Pok);
		pok->printProperty(*pok);

		cout << "��ѡ��1.���� 2.�鿴��������" << endl;
		int c;
		cin >> c;
		while (c == 1)
		{
			pok->upgrade(0.0);
			pok->printProperty(*pok);
			cout << "��ѡ��1.���� 2.�鿴��������" << endl;
			int c;
			cin >> c;
		}
	}
	pok.deletePok(pok);
}
*/