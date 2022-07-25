#include "otherPlayer.h"
#include"pokemonClient.h"

otherPlayer *otherplayerW;//其他玩家信息窗口

otherPlayer::otherPlayer(player p,QWidget *parent)//构造其他玩家信息窗口
	: QWidget(parent)
{
	ui.setupUi(this);

	/*打印胜率*/
	float winrate = 0.0;
	if (p.totalnum != 0) winrate = 100*((float)p.winnum / (float)p.totalnum);
	stringstream ss;
	ss << setiosflags(ios::fixed)<<setprecision(2) << winrate;
	QString s1 = QString::fromLocal8Bit("TA的胜率：") + QString::fromStdString(ss.str())+"%";
	ui.winRate->setText(s1);

	int x = 0,i=0;
	/*打印精灵*/
	for (vector<Pokemon*>::iterator it = p.poks.begin(); it != p.poks.end(); it++, i++)
	{
		/*根据精灵创建label图片*/
		pokImgLabel[i] = new QLabel(ui.scrollPoks);
		pokImgLabel[i]->setGeometry(QRect(80 + x, 60, 300, 300));
		QImage *img = new QImage;
		QString filename;
		filename = ":/pokpic/" + filename.fromStdString((*it)->getLetterName()) + ".png";
		QPixmap *pixm = new QPixmap(filename);
		pixm->scaled(pokImgLabel[i]->size(), Qt::KeepAspectRatio);
		pokImgLabel[i]->setScaledContents(true);
		pokImgLabel[i]->setPixmap(*pixm);
		pokImgLabel[i]->setText("");
		pokImgLabel[i]->show();

		QFont font1;
		font1.setFamily(QString::fromUtf8("\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223"));
		font1.setPointSize(16);
		pokLevLabel[i] = new QLabel(ui.scrollPoks);
		pokLevLabel[i]->setGeometry(QRect(200 + x, 320, 100, 100));
		pokLevLabel[i]->setFont(font1);
		QString lv;
		stringstream s;
		s << "Lv." << (*it)->getLv();
		//property = property.fromStdString(s.str());
		lv = QString::fromLocal8Bit(s.str().c_str());
		pokLevLabel[i]->setText(lv);
		pokLevLabel[i]->show();

		ui.scrollPoks->setGeometry(QRect(0, 0, 929 + x, 559));
		x += 300;
	}
	setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
	ui.scrollArea->setWidget(ui.scrollPoks);
}

otherPlayer::~otherPlayer()//析构
{
}

//int main(int argc, char **argv)
//{
//	QApplication app(argc, argv);
//
//	player p("test");
//	Pokemon *pok1 = nullptr; 
//	pok1=pok1->newPok(4);
//	Pokemon *pok2 = nullptr; 
//	pok2=pok2->newPok(2);
//	p.poks.push_back(pok1);
//	p.poks.push_back(pok2);
//	otherPlayer w(p);
//	w.show();
//	return app.exec();
//}