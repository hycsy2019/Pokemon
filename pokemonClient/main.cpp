#include "pokemonClient.h"
#include <QtWidgets/QApplication>
#include<direct.h>
#include"pokemonClientGUI.h"

QString runPath;//��ִ���ļ�����·��
extern pcg *loginW;//��¼����

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	char   buffer[MAX_PATH];
    getcwd(buffer, MAX_PATH);
	stringstream s;
	s << *argv;
	runPath = QString::fromLocal8Bit(s.str().c_str());
	runPath = runPath.left(runPath.length() - 21);
	for (int i = 0; i < runPath.length(); i++)
	{
		if (runPath[i] == '\\') runPath[i] = '/';
	}
	loginW = new pcg;
	loginW->show();
	return a.exec();
}
