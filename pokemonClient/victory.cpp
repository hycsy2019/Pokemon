#include "victory.h"
#include"pokemonClient.h"
#include"GUIfight.h"

victory *victoryW;//ʤ������

extern GUIfight *fightW;//ս������

victory::victory(Pokemon *winPok,Pokemon *losePok,player *P,float remainhp,bool type,QWidget *parent)//������type=0,������type=1.
	: QWidget(parent)
{
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);//��ֹ�رմ���
	pp = P;
	ui.setupUi(this);
	setFixedSize(this->width(), this->height());

	/*��ӡʤ�������ͼƬ*/
	QImage *img = new QImage;
	QString filename;
	filename = ":/pokpic/" + filename.fromStdString(winPok->getLetterName()) + ".png";
	QPixmap *pixm = new QPixmap(filename);
	pixm->scaled(ui.Pok->size(), Qt::KeepAspectRatio);
	ui.Pok->setScaledContents(true);
	ui.Pok->setPixmap(*pixm);
	ui.Pok->show();

	/*�Ӿ���ֵ��ʣ��Ѫ��Խ�����Ӿ���ֵԽ��*/
	float dexp;
	if (type == 0) dexp = 800 - remainhp;
	else dexp = 1000 - remainhp;
	if (dexp < 0) dexp = 0.0;
	
	/*��1000����ֵ��һ��*/
	if (winPok->exp+dexp > 1000)
		winPok->upgrade(winPok->exp + dexp - 1000);
	else winPok->exp = winPok->exp + dexp;
	stringstream s1;
	s1 << "Exp+" << setprecision(4) << dexp;
	ui.dexp->setText(QString::fromStdString(s1.str()));

	/*��ӡ��ս������*/
	QLabel *info;
	QFont font1;
	font1.setFamily(QString::fromUtf8("\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223"));
	font1.setPointSize(16);
	info = new QLabel(this);
	info->setGeometry(QRect(440, 100, 500, 450));
	info->setFont(font1);
	QString property;
	stringstream s;
	winPok->printProperty(*winPok, s);
	//property = property.fromStdString(s.str());
	property = QString::fromLocal8Bit(s.str().c_str());
	info->setText(property);
	info->show();

	/*���Ϊ���������þ���*/
	if (type == 1)
	{
		P->poks.push_back(losePok);
		P->pokNum++;
		ui.acquirePok->setText(QString::fromLocal8Bit(losePok->getName().c_str()));
	}
	else
	{
		ui.acquiremsg->hide();
		ui.acquirePok->hide();
	}
}

victory::~victory()//����
{
}

void victory::continueSlot()//���������Ϸ��ť
{
	/*�����������ս������ҵ�״̬*/
	fightW->updatePlayer();
	this->hide();
	fightW->returnSlot();
	delete victoryW;
}

//int main(int argc, char **argv)
//{
//	QApplication app(argc, argv);
//	Pokemon *pok2 = nullptr;
//	pok2=pok2->newPok(2);
//	player P("test");
//	P.poks.push_back(pok2);
//	victory w(pok2, pok2,&P,58.2, 0);
//	w.show();
//	return app.exec();
//}
