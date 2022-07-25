#include "lose.h"
#include"pokemonClient.h"
#include"GUIfight.h"

lose *loseW;//失败窗口

extern GUIfight *fightW;//战斗界面

lose::lose(Pokemon* losePok,player *p,bool type,float remainhp,QWidget *parent)//构造失败结算窗口
	: QWidget(parent)
{
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);//禁止关闭窗口
	pl = p;
	ui.setupUi(this);

	/*加经验值，对方剩余血量越少所加经验值越多*/
	float dexp;
	if (type == 0) dexp = 400 - remainhp;
	else dexp = 600 - remainhp;

	if (dexp < 0) dexp = 0.0;

	/*满1000经验值升一级*/
	if (losePok->exp + dexp > 1000)
		losePok->upgrade(losePok->exp + dexp - 1000);
	else losePok->exp = losePok->exp + dexp;
	stringstream s1;
	s1 << "Exp+" << setprecision(4) << dexp;
	ui.dexp->setText(QString::fromStdString(s1.str()));

	/*升级赛失败，无操作*/
	if (type == 0)
	{
		ui.left->hide();
		ui.center->hide();
		ui.right->hide();
		ui.msg->hide();
	}

	/*决斗赛失败，抛弃一只精灵*/
	else if (type == 1)
	{
		ui.gui->hide();
		ui.fighting->hide();
		
		/*从用户精灵中选三只贴图*/
		srand(time(NULL));
		vector<Pokemon*> Poks = p->poks;
		vector<Pokemon*>::iterator it = Poks.begin();
		int sum = 0;
		QString filename;
		while (sum != 3&&Poks.size()!=0)
		{
			/*遍历用户精灵，每只有一半概率被选中*/
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

lose::~lose()//析构
{
}

void lose::leftSlot()//点击左边的精灵
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

	/*若用户没有精灵则系统随机分配一只*/
	if (pl->pokNum == 0)
	{
		srand(time(NULL));
		int pokSeq = (rand() % POKNUM) + 1;
		Pokemon* p = nullptr;
		p = p->newPok(pokSeq);
		pl->poks.push_back(p);
		pl->pokNum++;
	}
	/*向服务器发送战斗后玩家的状态*/
	fightW->updatePlayer();
	this->hide();
	fightW->returnSlot();
	delete loseW;
}

void lose::centerSlot()//点击中间的精灵
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

	/*若用户没有精灵则系统随机分配一只*/
	if (pl->pokNum == 0)
	{
		srand(time(NULL));
		int pokSeq = (rand() % POKNUM) + 1;
		Pokemon* p = nullptr;
		p = p->newPok(pokSeq);
		pl->poks.push_back(p);
		pl->pokNum++;
	}
	/*向服务器发送战斗后玩家的状态*/
	fightW->updatePlayer();
	this->hide();
	fightW->returnSlot();
	delete loseW;
}

void lose::rightSlot()//点击右边的精灵
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

	/*若用户没有精灵则系统随机分配一只*/
	if (pl->pokNum == 0)
	{
		srand(time(NULL));
		int pokSeq = (rand() % POKNUM) + 1;
		Pokemon* p = nullptr;
		p = p->newPok(pokSeq);
		pl->poks.push_back(p);
		pl->pokNum++;
	}
	/*向服务器发送战斗后玩家的状态*/
	fightW->updatePlayer();
	this->hide();
	fightW->returnSlot();
	delete loseW;
}

void lose::fightingSlot()//点击再接再厉
{
	/*向服务器发送战斗后玩家的状态*/
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