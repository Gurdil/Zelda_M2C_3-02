#include <QApplication>
#include <iostream>

#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QList>
#include <QPixmap>
#include <QRect>


#include "controler.h"



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	a.setOverrideCursor(QCursor(Qt::BlankCursor ));

	ZControler *c = ZControler::getInstance();

	return a.exec();

	std::cout << "Never view" << std::endl;
}
