#include"pokemonClient.h"
#include<time.h>
#include<random>

/*e u�������������*/
std::default_random_engine e;
uniform_real_distribution<float> u(0, 1);

Pokemon* Fight::wholeFight()//ս�����ɣ����ػ�ʤ�ľ���
{
	float hp1 = pok1->getHp(), hp2 = pok2->getHp();//��ʼ����ֵΪ����
	int strikeN1 = 0, strikeN2 = 0;//�ۻ�δ���������Ĵ���
	int i = 0;
	
	while (hp1 != 0.0 && hp2 != 0.0)//��һ��Ѫ��Ϊ0ʱս������
	{
		strikeN1++; strikeN2++;//δ������������
		//��������ȹ����ľ���
		if (first == 1) round(pok1,pok2,hp1, hp2,strikeN1,strikeN2);
		else round(pok2,pok1,hp2, hp1,strikeN2,strikeN1);
	}

	if (hp1 == 0.0) return pok2;//����1��Ѫ��Ϊ0���򷵻ػ�ʤ�ľ���2
	else return pok1;
}

bool Fight::dodge(Pokemon pokAtk,Pokemon pokDf)//pok�Ĺ����ܷ񱻵з����ܳɹ�
{
	float hit = (3*pokAtk.getLv()*pokDf.getAtkt()) / ((pokAtk.getLv() + pokDf.getLv())*pokAtk.getAtkt());//������
	float r = u(e);//0-1�������
	if (r <= hit) return false;
	else return true;
}

bool Fight::strike(int& strikeN)//�ܷ񱩻�
{
	float r = u(e);
	if (r < 0.08*strikeN)//����δ���������ۼӱ�����
	{
		strikeN = 0;
		return true;
	}
	else return false;
}

void Fight::round(Pokemon* pokFirst, Pokemon* pokSecond, 
	float& hpFirst, float& hpSecond,int& strikeFir,int& strikeSec)//ÿ����ս�غ�
{
	ATTACK atkFir, atkSec;

	atkFir = pokFirst->attack(*pokSecond, 0);//�ȹ����ľ���ʹ�õ���ʽ

	if (!dodge(*pokFirst, *pokSecond))//�з�����ʧ��
	{
		if (strike(strikeFir))
		{
			atkFir.damage *= 1.5;//�����ɹ�������1.5���˺�
			atkFir.strike = 1;
		}
	}
	else
	{
		atkFir.dodge = 1;
		atkFir.damage = 0;//���������˺�
	}

	atkFir.hpOppo = hpSecond - atkFir.damage;//������ĵз�Ѫ���浽����rounds��
	hpSecond -= atkFir.damage;//�󹥻��ľ����Ѫ

	if (atkFir.hpOppo < 0)
	{
		atkFir.hpOppo = 0.0;//Ѫ������Ϊ0
		hpSecond =0.0;//�󹥻��ľ����������
	}
	else//�з�Ѫ��δ����0
	{
		atkSec = pokSecond->attack(*pokFirst, 0);

		if (!dodge(*pokSecond, *pokFirst))//�з�����ʧ��
		{
			if (strike(strikeSec))
			{
				atkSec.damage *= 1.5;//�����ɹ�������1.5���˺�
				atkSec.strike = 1;
			}
		}
		else
		{
			atkSec.dodge = 1;
			atkSec.damage = 0;//���������˺�
		}

		atkSec.hpOppo = hpFirst - atkSec.damage;
		hpFirst -= atkSec.damage;
		if (atkSec.hpOppo < 0)
		{
			atkSec.hpOppo = 0.0;
			hpFirst = 0.0;//�ȹ����ľ����������
		}
	}
	atkFir.pok = pokFirst->getName();
	atkSec.pok = pokSecond->getName();
	rounds.push_back(make_pair(atkFir, atkSec));//����roundsβ�������µĻغ�˫��������Ϣ
}

bool Fight::printRounds()//���ÿһ�غϵ�ս��
{
	int round = 1;
	float hp1, hp2;

	cout << "������֣�";
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
		if (it->first.hpOppo != 0.0)//�Է�Ѫ��δ�ﵽ0����������
		{
			cout <<endl<< "��" << round << "�غ�" << endl;
			cout << it->first.pok<< "��" << endl;
			cout << "Ѫ����" <<setprecision(2) << hp1 << endl;
			cout << "ʹ����ʽ��" << it->first.name << endl;
			if (it->first.dodge) cout << "������  " ;
			else cout << "����  " ;
			if (it->first.strike) cout << "����" << endl;
			else cout << "��ͨ����" << endl;
			cout << "����˺���" << setprecision(2) << it->first.damage << endl;
			hp2 = it->first.hpOppo;

			cout << endl << it->second.pok<< "��" << endl;
			cout << "Ѫ����" << setprecision(2) << hp2 << endl;
			cout << "ʹ����ʽ��" << it->second.name << endl;
			if (it->second.dodge) cout << "������  ";
			else cout << "����  ";
			if (it->second.strike) cout << "����" << endl;
			else cout << "��ͨ����" << endl;
			cout << "����˺���" << setprecision(2) << it->second.damage << endl;
			hp1 = it->second.hpOppo;

			if (hp1 >= 0 && hp1<=0)  return true;
		}
		else return true;
	}
	return false;
}

/*int main()
{
	int Pok;
	Pokemon *pok1 = nullptr;
	Pokemon *pok2 = nullptr;

	cout << "����һ����ս���Գ���" << endl;
	while (true)
	{
		cout << "��ѡ���ս����1��1.�������� 2.Ƥ���� 3.С���� 4.����� 5.�ղ�Ҷ 6.������� 7.ī���� ";
		cout << "8.�ֿɶ� 9.���� 10.�𱬺� 11.���� 12.������ 13.��ʯ�� 14.ƤƤ 15.����" << endl;
		cin >> Pok;

		pok1 = pok1->newPok(Pok);
		pok1->printProperty(*pok1);

		cout << "��ѡ��1.���� 2.ѡ�����" << endl;
		int c;
		cin >> c;
		while (c == 1)
		{
			pok1->upgrade(0.0);
			pok1->printProperty(*pok1);
			cout << "��ѡ��1.���� 2.ѡ�����" << endl;
			cin >> c;
		}

		if (c == 2)
		{
			cout << "��ѡ���ս����2��1.�������� 2.Ƥ���� 3.С���� 4.����� 5.�ղ�Ҷ 6.������� 7.ī���� ";
			cout << "8.�ֿɶ� 9.���� 10.�𱬺� 11.���� 12.������ 13.��ʯ�� 14.ƤƤ 15.����" << endl;
			cin >> Pok;

			pok2 = pok2->newPok(Pok);
			pok2->printProperty(*pok2);

			cout << "��ѡ��1.���� 2.��ʼս��" << endl;
			cin >> c;
			while (c == 1)
			{
				pok2->upgrade(0.0);
				pok2->printProperty(*pok2);
				cout << "��ѡ��1.���� 2.��ʼս��" << endl;
				cin >> c;
			}

			if (c == 2)
			{
				Fight F = Fight(pok1,pok2);
				Pokemon* winPok = F.wholeFight();
				F.printRounds();
				cout << winPok->getName() << "��ʤ"<<endl<<endl;
			}
		}
	}
}
*/