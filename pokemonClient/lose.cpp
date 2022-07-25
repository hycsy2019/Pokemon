#include "lose.h"
#include"pokemonClient.h"
#include"GUIfight.h"

lose *loseW;//ʧ�ܴ���

extern GUIfight *fightW;//ս������

lose::lose(Pokemon* losePok,player *p,bool type,float remainhp,QWidget *parent)//����ʧ�ܽ��㴰��
	: QWidget(parent)
{
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);//��ֹ�رմ���
	pl = p;
	ui.setupUi(this);

	/*�Ӿ���ֵ���Է�ʣ��Ѫ��Խ�����Ӿ���ֵԽ��*/
	float dexp;
	if (type == 0) dexp = 400 - remainhp;
	else dexp = 600 - remainhp;

	if (dexp < 0) dexp = 0.0;

	/*��1000����ֵ��һ��*/
	if (losePok->exp + dexp > 1000)
		losePok->upgrade(losePok->exp + dexp - 1000);
	else losePok->exp = losePok->exp + dexp;
	stringstream s1;
	s1 << "Exp+" << setprecision(4) << dexp;
	ui.dexp->setText(QString::fromStdString(s1.str()));

	/*������ʧ�ܣ��޲���*/
	if (type == 0)
	{
		ui.left->hide();
		ui.center->hide();
		ui.right->hide();
		ui.msg->hide();
	}

	/*������ʧ�ܣ�����һֻ����*/
	else if (type == 1)
	{
		ui.gui->hide();
		ui.fighting->hide();
		
		/*���û�������ѡ��ֻ��ͼ*/
		srand(time(NULL));
		vector<Pokemon*> Poks = p->poks;
		vector<Pokemon*>::iterator it = Poks.begin();
		int sum = 0;
		QString filename;
		while (sum != 3&&Poks.size()!=0)
		{
			/*�����û����飬ÿֻ��һ����ʱ�ѡ��*/
			if (rand() % 2 == 1)
			{
				if (sum == 0)
				{
					filename = ":/pokpic/" + filename.fromStdString((*it)->getLetterName()) + ".png";
					ui.left->setStyleSheet("border-image:url(" + filename + ")");
					leftPok =*it;
				}
				else if (sum == 1)
				{
					filename = ":/pokpic/" + filename.fromStdString((*it)->getLetterName()) + ".png";
					ui.center->setStyleSheet("border-image:url(" + filename + ")");
					centerPok =*it;
				}
				else if (sum == 2)
				{
					filename = ":/pokpic/" + filename.fromStdString((*it)->getLetterName()) + ".png";
					ui.right->setStyleSheet("border-image:url(" + filename + ")");
					rightPok =*it;
				}
				
				sum++;
				if (it + 1 != Poks.end())
				{
					it = Poks.erase(it);
				}
				else
				{
					it = Poks.begin();
					Poks.pop_back();
				}
			}
			else
			{
				if (it + 1 != Poks.end()) it++;
				else it = Poks.begin();
			}
		}
	}
}

lose::~lose()//����
{
}

void lose::leftSlot()//�����ߵľ���
{
	for (vector<Pokemon*>::iterator it = pl->poks.begin(); it != pl->poks.end(); it++)
	{
		if (leftPok == *it)
		{
			pl->poks.erase(it);
			pl->pokNum--;
			break;
		}
	}

	/*���û�û�о�����ϵͳ�������һֻ*/
	if (pl->pokNum == 0)
	{
		srand(time(NULL));
		int pokSeq = (rand() % POKNUM) + 1;
		Pokemon* p = nullptr;
		p = p->newPok(pokSeq);
		pl->poks.push_back(p);
		pl->pokNum++;
	}
	/*�����������ս������ҵ�״̬*/
	fightW->updatePlayer();
	this->hide();
	fightW->returnSlot();
	delete loseW;
}

void lose::centerSlot()//����м�ľ���
{
	for (vector<Pokemon*>::iterator it = pl->poks.begin(); it != pl->poks.end(); it++)
	{
		if (centerPok == *it)
		{
			pl->poks.erase(it);
			pl->pokNum--;
			break;
		}
	}

	/*���û�û�о�����ϵͳ�������һֻ*/
	if (pl->pokNum == 0)
	{
		srand(time(NULL));
		int pokSeq = (rand() % POKNUM) + 1;
		Pokemon* p = nullptr;
		p = p->newPok(pokSeq);
		pl->poks.push_back(p);
		pl->pokNum++;
	}
	/*�����������ս������ҵ�״̬*/
	fightW->updatePlayer();
	this->hide();
	fightW->returnSlot();
	delete loseW;
}

void lose::rightSlot()//����ұߵľ���
{
	for (vector<Pokemon*>::iterator it = pl->poks.begin(); it != pl->poks.end(); it++)
	{
		if (rightPok == *it)
		{
			pl->poks.erase(it);
			pl->pokNum--;
			break;
		}
	}

	/*���û�û�о�����ϵͳ�������һֻ*/
	if (pl->pokNum == 0)
	{
		srand(time(NULL));
		int pokSeq = (rand() % POKNUM) + 1;
		Pokemon* p = nullptr;
		p = p->newPok(pokSeq);
		pl->poks.push_back(p);
		pl->pokNum++;
	}
	/*�����������ս������ҵ�״̬*/
	fightW->updatePlayer();
	this->hide();
	fightW->returnSlot();
	delete loseW;
}

void lose::fightingSlot()//����ٽ�����
{
	/*�����������ս������ҵ�״̬*/
	fightW->updatePlayer();
	this->hide();
	fightW->returnSlot();
	delete loseW;
}

//int main(int argc, char **argv)
//{
//	QApplication app(argc, argv);
//	player p1("test11111");
//	Pokemon *pok1 = nullptr; 
//	pok1=pok1->newPok(4);
//	Pokemon *pok2 = nullptr; 
//	pok2=pok2->newPok(2);
//	Pokemon *pok3 = nullptr;
//	pok3 = pok3->newPok(10);
//	Pokemon *pok4 = nullptr;
//	pok4 = pok4->newPok(12);
//	p1.poks.push_back(pok1);
//	p1.poks.push_back(pok2);
//	p1.poks.push_back(pok3);
//	p1.poks.push_back(pok4);
//	lose w(&p1,0);
//	w.show();
//	return app.exec();
//}