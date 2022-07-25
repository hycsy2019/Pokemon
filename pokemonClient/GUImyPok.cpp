#include "GUImyPok.h"
#include"pokemonClient.h"
GUImyPok *mypokW;//精灵背包窗口

GUImyPok::GUImyPok(player *p, QWidget *parent)//构造精灵背包窗口
	: QWidget(parent)
{
	ui.setupUi(this);
	setupPoksWidget(this, p);
	setFixedSize(this->width(), this->height());
}

GUImyPok::~GUImyPok()//析构
{
}

void GUImyPok::setupPoksWidget(QWidget *w,player *p)//构造精灵背包窗口
{
	int i = 0,y=0;
	for (vector<Pokemon*>::iterator it = p->poks.begin(); it != p->poks.end(); it++,i++)
	{
		/*根据精灵创建label图片*/
		pokImgLabel[i] = new QLabel(ui.scrollPoks);
		pokImgLabel[i]->setGeometry(QRect(80, 20 + y, 380, 380));
		QString filename;
		filename=":/pokpic/"+filename.fromStdString((*it)->getLetterName())+".png";
		QPixmap *pixm = new QPixmap(filename);
		pixm->scaled(pokImgLabel[i]->size(), Qt::KeepAspectRatio);
		pokImgLabel[i]->setScaledContents(true);
		pokImgLabel[i]->setPixmap(*pixm);
		pokImgLabel[i]->setText("");
		pokImgLabel[i]->show();

		/*打印精灵属性*/
		QFont font1;
		font1.setFamily(QString::fromUtf8("\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223"));
		font1.setPointSize(16);
		pokInfoLabel[i] = new QLabel(ui.scrollPoks);
		pokInfoLabel[i]->setGeometry(QRect(450, 30 + y, 500, 450));
		pokInfoLabel[i]->setFont(font1);
		QString property;
		stringstream s;
		(*it)->printProperty(**it, s);
		//property = property.fromStdString(s.str());
		property = QString::fromLocal8Bit(s.str().c_str());
		pokInfoLabel[i]->setText(property);
		pokInfoLabel[i]->show();

		y +=540;
		ui.scrollPoks->setGeometry(QRect(0, 0, 929, 559 + y));
	}
	setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
	ui.scrollArea->setWidget(ui.scrollPoks);
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
//	GUImyPok w(p);
//	w.show();
//	return app.exec();
//}